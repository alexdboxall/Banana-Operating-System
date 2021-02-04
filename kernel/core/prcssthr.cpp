#include "core/prcssthr.hpp"
#include "core/common.hpp"
#include "core/terminal.hpp"
#include "libk/string.h"
#include "hw/cpu.hpp"
#include "core/kheap.hpp"
#include "core/physmgr.hpp"
#include "core/elf.hpp"

//#pragma GCC optimize ("O2")

#define STACK_LEEWAY 32

Process* kernelProcess = nullptr;
LinkedList<volatile ThreadControlBlock> taskList;
LinkedList<volatile ThreadControlBlock> sleepingTaskList;
LinkedList<volatile ThreadControlBlock> terminatedTaskList;

int irqDisableCounter = 0;
int postponeTaskSwitchesCounter = 0;
int taskSwitchesPostponedFlag = 0;

extern "C" void switchToThreadASM(ThreadControlBlock * nextThreadToRun);
extern "C" void switchToThreadASMFirstTime(ThreadControlBlock * nextThreadToRun);

extern "C" void changeTSS()
{
	thisCPU()->tss.setESP(VIRT_APP_STACK_KRNL_TOP - SIZE_APP_STACK_TOTAL * currentTaskTCB->rtid);
}

void switchToThread(ThreadControlBlock* nextThreadToRun)
{
	if (postponeTaskSwitchesCounter != 0) {
		taskSwitchesPostponedFlag = 1;
		return;
	}

	if (nextThreadToRun->priority == 255) {
		nextThreadToRun->timeSliceRemaining = 0;
	} else {
		//70 ms - 0.13ms/priority

		//RANGE:
		//Priority 0  : 58ms
		//Priority 128: 51ms
		//Priority 254: 42ms
		nextThreadToRun->timeSliceRemaining += (900 - nextThreadToRun->priority) << 16;
	}
	//nextThreadToRun->timeSliceRemaining = 50000000;

	updateTimeUsed();
	switchToThreadASM(nextThreadToRun);
}

ThreadControlBlock* Process::createUserThread()
{
	return createThread(userModeEntryPoint);
}

ThreadControlBlock* Process::createThread(void (*where)(void*), void* context, int pri)
{
	int threadNo = 0;
	auto tu = threadUsage;
	bool found = false;
	while (threadNo < 16) {
		if ((tu & 1) == 0) {
			found = true;
			break;
		}
		++threadNo;
		tu >>= 1;
	}

	if (!found) {
		return nullptr;
	}

	threadUsage |= (1 << threadNo);
	threads[threadNo].cr3 = vas->pageDirectoryBasePhysical;
	threads[threadNo].startContext = context;
	threads[threadNo].esp = VIRT_APP_STACK_USER_TOP - SIZE_APP_STACK_TOTAL * threadNo - STACK_LEEWAY;
	threads[threadNo].priority = pri;
	threads[threadNo].rtid = threadNo;
	threads[threadNo].processRelatedTo = this;
	threads[threadNo].state = TaskState::ReadyToRun;
	threads[threadNo].firstTimeEIP = (size_t) where;
	threads[threadNo].timeKeeping = 0;

	taskList.addElement(&threads[threadNo]);

	return &threads[threadNo];
}

void Process::addArgs(char** _argv)
{
	argc = 0;

	if (_argv == nullptr) {
		return;
	}

	for (int i = 0; _argv[i]; ++i) {
		if (i == 255) {
			kprintf("TOO MANY ARGUMENTS GIVEN TO A PROCESS!\n");
			return;
		}
		argv[i] = (char*) malloc(strlen(_argv[i]) + 1);
		strcpy(argv[i], _argv[i]);
		argc++;
	}
}

void setupMultitasking(void (*where)())
{
	while (!taskList.isEmpty()) taskList.removeFirst();

	Process* p = new Process(true, "System", nullptr, nullptr);
	kernelProcess = p;
	kprintf("setupMultitasking. Setting active terminal to 0x%X\n", p->terminal);
	setActiveTerminal(p->terminal);

	p->threadUsage |= 1;
	p->threads[0].cr3 = p->vas->pageDirectoryBasePhysical;
	p->threads[0].esp = VIRT_APP_STACK_USER_TOP - STACK_LEEWAY;
	p->threads[0].rtid = 0;
	p->threads[0].state = TaskState::Running;
	p->threads[0].firstTimeEIP = (size_t) where;
	p->threads[0].timeKeeping = 0;
	p->threads[0].processRelatedTo = p;
	p->threads[0].timeSliceRemaining = 50000000;

	currentTaskTCB = &p->threads[0];

	strcpy(p->cwd, "C:/");

	p->threads[0].priority = 128;

	//we do NOT add it to the task list, because we've set it to 'running', and this list only
	//has the non-running processes. If we add it here, it will end up on there twice, and our
	//linked list implementation doesn't cope very well with that.
		//taskList.addElement(&p->threads[0]);

	switchToThreadASMFirstTime(&p->threads[0]);
}

int nextPID = 1;

Process::Process(const char* _filepath, Process* _parent, char** _argv)
{
	threadUsage = 0;
	pid = nextPID++;
	vas = new VAS(false);
	argc = 0;
	parent = _parent;

	if (parent) {
		terminal = parent->terminal;
		strcpy(cwd, parent->cwd);

	} else {
		terminal = new VgaText(_filepath);
		addToTerminalCycle(terminal);
		strcpy(cwd, "C:/");
	}

	strcpy(taskname, _filepath);
	addArgs(_argv);

	bool f = loadProgramIntoMemory(this, _filepath);
	failedToLoadProgram = !f;
	kprintf("LOAD PROGRAM INTO MEMORY RETURNED %d\n", f);
}

Process::Process(bool _kernel, const char* _name, Process* _parent, char** _argv)
{
	threadUsage = 0;
	pid = nextPID++;
	vas = new VAS(_kernel);
	argc = 0;
	parent = _parent;

	if (parent) {
		terminal = parent->terminal;
		strcpy(cwd, parent->cwd);

	} else {
		terminal = new VgaText(_name);
		addToTerminalCycle(terminal);
		strcpy(cwd, "C:/");
	}

	strcpy(taskname, _name);
	addArgs(_argv);
}

int forkProcess(regs* r) {
	if (currentTaskTCB->processRelatedTo->threadUsage != 1) {
		kprintf("fork() called on a multithreaded process!\n");
		return -1;
	}

	lockStuff();

	Process* p = new Process(false, currentTaskTCB->processRelatedTo->taskname, currentTaskTCB->processRelatedTo, nullptr);
	delete p->vas;

	p->threadUsage = 1;
	p->usermodeEntryPoint = currentTaskTCB->processRelatedTo->usermodeEntryPoint;

	//magic happens here
	p->vas = new VAS(currentTaskTCB->processRelatedTo->vas);

	p->threads[0].cr3 = p->vas->pageDirectoryBasePhysical;
	p->threads[0].timeSliceRemaining = currentTaskTCB->timeSliceRemaining;
	p->threads[0].startContext = p->threads[0].startContext;
	p->threads[0].esp = currentTaskTCB->esp;
	p->threads[0].priority = currentTaskTCB->priority;
	p->threads[0].rtid = 0;
	p->threads[0].processRelatedTo = p;
	p->threads[0].state = currentTaskTCB->state;
	p->threads[0].firstTimeEIP = 1;		//magic value, meaning this process came off a fork
	p->threads[0].timeKeeping = 0;
	p->threads[0].forkret = 0;
	p->threads[0].magicForkyParentSavePoint = currentTaskTCB->magicForkyParentSavePoint;

	currentTaskTCB->forkret = p->pid;

	taskList.addElement(&p->threads[0]);

	unlockStuff();

	return currentTaskTCB->forkret;
}

int execveProcess(const char* pathname, char* const argv[], char* const envp[])
{
	//here at Banana we encourage you NOT to use fork/exec if possible 
	//Reason:
	//		fork copies a process
	//		exec deletes (not overwrites) the process you just copied, and spawns a new one

	lockStuff();

	VgaText* vtext = currentTaskTCB->processRelatedTo->terminal;
	Process* p = new Process(pathname, currentTaskTCB->processRelatedTo->parent, (char**) argv);
	if (!p) {
		unlockStuff();
		return -1;
	}
	p->pid = currentTaskTCB->processRelatedTo->pid;
	if (vtext) {
		p->terminal = vtext;
	}

	p->createUserThread();

	blockTask(TaskState::Terminated);		//bye-bye process you just created through fork()
	unlockStuff();

	lockScheduler();
	schedule();
	unlockScheduler();

	return -1;
}


size_t schedulerLock;
size_t lockStuffLock;
size_t retValSchedLock;
size_t retValLockStuff;

extern "C" unsigned long asmAcquireLock(size_t*);
extern "C" void asmReleaseLock(size_t*, size_t);

extern bool displayCliSti;

void disableIRQs()
{
	asm volatile ("cli");
	irqDisableCounter++;
}

int getIRQNestingLevel()
{
	return irqDisableCounter;
}

void enableIRQs()
{
	irqDisableCounter--;
	if (irqDisableCounter == 0) {
		asm volatile ("sti");
	}
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wframe-address"

void lockScheduler(void)
{
#ifndef SMP
	disableIRQs();
#endif
	//kprintf("LCK %d->%d 0x%X 0x%X\n", getIRQNestingLevel() - 1, getIRQNestingLevel(), __builtin_return_address(0), 0/* __builtin_return_address(1)*/);
}

int xxxx = 0;
void unlockScheduler(void)
{
	//kprintf("ULK %d->%d 0x%X 0x%X\n", getIRQNestingLevel(), getIRQNestingLevel() - 1, __builtin_return_address(0), 0/* __builtin_return_address(1)*/);
#ifndef SMP
	enableIRQs();
#endif
}
#pragma GCC diagnostic pop

void lockStuff(void)
{
#ifndef SMP
	disableIRQs();
	postponeTaskSwitchesCounter++;
#endif
}

void unlockStuff(void)
{
#ifndef SMP
	postponeTaskSwitchesCounter--;
	if (postponeTaskSwitchesCounter == 0) {
		if (taskSwitchesPostponedFlag != 0) {
			taskSwitchesPostponedFlag = 0;
			schedule();
		}
	}

	enableIRQs();
#endif

}

extern "C" void goToUsermode(size_t loc);
void userModeEntryPoint(void* context)
{
	unlockScheduler();
	asm("sti");
	goToUsermode(currentTaskTCB->processRelatedTo->usermodeEntryPoint);
}

extern "C" size_t taskStartupFunction()
{
	//Called every time a new task is ran
	//This function was jumped to, with a return address to the
	//actual task pushed before we did the jump. That means when
	//we reach the end of the function, it will go to the start 
	//of the task.

	return (size_t) currentTaskTCB->startContext;
}

void schedule()
{
	//caller is responsible for locking the scheduler before calling	
	if (postponeTaskSwitchesCounter != 0) {
		taskSwitchesPostponedFlag = 1;
		return;
	}

	//if there is another task to move onto
	if (!taskList.isEmpty()) {
		//put the first one back if we need to
		if (currentTaskTCB->state == TaskState::Running) {
			currentTaskTCB->state = TaskState::ReadyToRun;
			taskList.addElement(currentTaskTCB);
		}

		//select a new task
		ThreadControlBlock* task = (ThreadControlBlock*) taskList.getFirstElement();

		//remove it from the list
		taskList.removeFirst();

		//set to running
		task->state = TaskState::Running;

		//start it 
		switchToThread(task);
	}
}

void updateTimeUsed()
{
	if (!thisCPU()->features.hasTSC) return;

	static uint64_t currentCount = 0;
	static uint64_t elapsed = 0;
	static uint64_t lastCount = 0;

	asm volatile ("rdtsc" : "=A"(currentCount));
	elapsed = currentCount - lastCount;
	lastCount = currentCount;

	currentTaskTCB->timeKeeping += elapsed;
}

void cleanupTerminatedTask(ThreadControlBlock* task)
{
	for (int i = 0; i < task->processRelatedTo->argc; ++i) {
		free(task->processRelatedTo->argv[i]);
	}

	task->processRelatedTo->argc = 0;

	//clear our thread bit
	task->processRelatedTo->threadUsage &= ~(1 << task->rtid);

	//check if all threads have finished
	if (task->processRelatedTo->threadUsage == 0) {

		int returnCode = task->returnCodeForUseOnTerminationList;

		// handle 'waitpid'
		if (task->processRelatedTo->parent) {
			for (int i = 0; i < 16; ++i) {
				if (task->processRelatedTo->parent->threadUsage & (1 << i)) {
					if (task->processRelatedTo->parent->threads[i].state == TaskState::WaitPID) {
						if (task->processRelatedTo->parent->threads[i].waitingPID < -1) {
							panic("We don't currently support waitpid() with PID < -1");

						} else if (task->processRelatedTo->parent->threads[i].waitingPID == -1) {
							task->processRelatedTo->parent->threads[i].waitingPID = task->processRelatedTo->pid;
							task->processRelatedTo->parent->threads[i].waitingThreadReturnCode = returnCode;
							unblockTask(&task->processRelatedTo->parent->threads[i]);

						} else if (task->processRelatedTo->parent->threads[i].waitingPID == 0) {
							panic("We don't currently support waitpid() with PID == 0");

						} else if (task->processRelatedTo->parent->threads[i].waitingPID == task->processRelatedTo->pid) {
							task->processRelatedTo->parent->threads[i].waitingPID = task->processRelatedTo->pid;
							task->processRelatedTo->parent->threads[i].waitingThreadReturnCode = returnCode;
							unblockTask(&task->processRelatedTo->parent->threads[i]);
						}
					}
				}
			}
		}

		if (task->processRelatedTo->terminal != nullptr && task->processRelatedTo->parent->terminal != task->processRelatedTo->terminal) {

			//next check for any threads using our terminal
			ThreadControlBlock* first = (ThreadControlBlock*) taskList.getFirstElement();
			if (!taskList.isEmpty()) {
				do {
					ThreadControlBlock* curr = (ThreadControlBlock*) taskList.getFirstElement();
					taskList.removeFirst();
					//we have to get rid of children using our terminal
					if (curr != task && curr->processRelatedTo->parent == task->processRelatedTo && curr->processRelatedTo->terminal == task->processRelatedTo->terminal) {
						kprintf("Terminating a child using our terminal!");
						blockTask(TaskState::Terminated);
					}
					taskList.addElement(curr);

				} while (taskList.getFirstElement() != first);
			}

			delete task->processRelatedTo->terminal;
			task->processRelatedTo->terminal = nullptr;
		}

		delete task->processRelatedTo->vas;
		kprintf("Deleted VAS.\n");
	}

	delete task;
}

int waitTask(int pid, int* wstatus, int options)
{
	currentTaskTCB->waitingPID = pid;
	currentTaskTCB->wstatus = wstatus;

	blockTask(TaskState::WaitPID);

	if (currentTaskTCB->wstatus) {
		*currentTaskTCB->wstatus = currentTaskTCB->waitingThreadReturnCode;
	}

	return currentTaskTCB->waitingPID;
}

bool weNeedTheCleanerToNotBlock = false;

void cleanerTaskFunction(void* context)
{
	unlockScheduler();

	ThreadControlBlock* task;

	while (1) {
		/*lockScheduler();
		schedule();
		unlockScheduler();

		continue;*/

		//pause until we get unblocked

		//this ugly flag prevents an even uglier race condition where the cleaner task is unblocked
		//while it is still running, so nothing happens, and then we reach here and block, and the we
		//doesn't wake up because the unblock request was already sent, and tasks wait()ing on the terminated
		//task (e.g. the system task waiting for the VGA thread) never wake up, causing the system to grind to a halt
		lockScheduler();
		if (!weNeedTheCleanerToNotBlock) {
			blockTaskWithSchedulerLockAlreadyHeld(TaskState::Paused);
		} else {
			unlockScheduler();
		}
		weNeedTheCleanerToNotBlock = false;

		//then clean up
		lockStuff();
		lockScheduler();
		while (!terminatedTaskList.isEmpty()) {
			task = (ThreadControlBlock*) terminatedTaskList.getFirstElement();
			terminatedTaskList.removeFirst();
			cleanupTerminatedTask(task);
		}
		unlockScheduler();
		unlockStuff();
	}
}

void terminateTask(int returnCode)
{
	extern int irqDisableCounter;
	extern int postponeTaskSwitchesCounter;
	extern int taskSwitchesPostponedFlag;

	// Note: Can do any harmless stuff here (close files, free memory in user-space, ...) but there's none of that yet

	// Put this task on the terminated task list
	lockStuff();
	lockScheduler();

	currentTaskTCB->returnCodeForUseOnTerminationList = returnCode;
	currentTaskTCB->next;
	terminatedTaskList.addElement(currentTaskTCB);
	currentTaskTCB->state = TaskState::Terminated;

	// Block this task (note: task switch will be postponed until scheduler lock is released)

	if (cleanerThread) {
		// Make sure the cleaner task isn't paused
		weNeedTheCleanerToNotBlock = true;
		unblockTask(cleanerThread);

	} else {
		kprintf("CLEANER CALLED BEFORE STARTED");
	}

	unlockScheduler();
	unlockStuff();

	while (1) {
		lockScheduler();
		schedule();
		unlockScheduler();
	}
}

//required to avoid some nasty race conditions
void blockTaskWithSchedulerLockAlreadyHeld(enum TaskState reason)
{
	kprintf("blockTaskWithSchedulerLockAlreadyHeld in  -> %d\n", getIRQNestingLevel());
	currentTaskTCB->state = reason;
	schedule();
	unlockScheduler();
	kprintf("blockTaskWithSchedulerLockAlreadyHeld out -> %d\n", getIRQNestingLevel());
}

void blockTask(enum TaskState reason)
{
	lockScheduler();
	currentTaskTCB->state = reason;
	schedule();
	unlockScheduler();
}

void unblockTask(ThreadControlBlock* task)
{
	lockScheduler();

	if (task->state == TaskState::ReadyToRun) {
		kprintf("Trying to unblock task, but it wasn't blocked. State was ReadyToRun\n");
		kprintf("Could cause quite catastrophic errors (e.g. this task goes missing), especially if\nthe task is just about to block.");

	} else if (task->state == TaskState::Running) {
		kprintf("Trying to unblock task, but it wasn't blocked. State is Running\n");
		kprintf("Could cause quite catastrophic errors (e.g. this task goes missing), especially if\nthe task is just about to block.");

	} else {
		ThreadControlBlock* f = (ThreadControlBlock*) taskList.getFirstElement();
		bool onlyOneTask = f == nullptr;
		while (f) {
			if (f == task) {
				unlockScheduler();
				return;
			}
			f = (ThreadControlBlock*) taskList.getNext(f);
		}
		if (0 && onlyOneTask) {
			switchToThread(task);
		} else {
			taskList.addElement(task);
		}
	}

	unlockScheduler();
}

void nanoSleepUntil(uint64_t when)
{
	if (when < nanoSinceBoot) {
		return;
	}

	lockStuff();

	currentTaskTCB->sleepExpiry = when;
	sleepingTaskList.addElement(currentTaskTCB);
	blockTask(TaskState::Sleeping);
	unlockStuff();
}


void nanoSleep(uint64_t nanoseconds)
{
	nanoSleepUntil(nanoSinceBoot + nanoseconds);
}

void sleep(uint64_t seconds)
{
	nanoSleep(seconds * 1000000000ULL);
}

extern "C" void taskReturned()
{
	kprintf("A task returned. Name = %s\n", currentTaskTCB->processRelatedTo->taskname);

	//panic("TASK RETURNED. ENSURE IT LOOPS AT END.\n");
	while (1) {
		blockTask(TaskState::Paused);
		lockScheduler();
		schedule();
		unlockScheduler();
	}
}

ThreadControlBlock* cleanerThread = nullptr;

Semaphore::Semaphore(int max)
{
	maxCount = max;
	currentCount = 0;
	firstWaitingTask = nullptr;
	lastWaitingTask = nullptr;
}

bool Semaphore::tryAcquire()
{
	lockStuff();

	if (currentCount < maxCount) {
		//we can aquire now
		++currentCount;
		unlockStuff();
		return true;
	}

	//we didn't acquire
	unlockStuff();
	return false;
}

void Semaphore::assertLocked(const char* msg)
{
	lockStuff();

	if (currentCount < maxCount) {
		panic(msg);
	}

	unlockStuff();
}

void Semaphore::acquire()
{
	lockStuff();

	if (currentCount < maxCount) {
		//we can aquire now
		++currentCount;

	} else {
		//we have to wait
		currentTaskTCB->next = nullptr;

		if (firstWaitingTask == nullptr) {
			firstWaitingTask = (ThreadControlBlock*) currentTaskTCB;
		} else {
			lastWaitingTask->next = (ThreadControlBlock*) currentTaskTCB;
		}
		lastWaitingTask = (ThreadControlBlock*) currentTaskTCB;

		blockTask(TaskState::WaitingForLock);
	}

	unlockStuff();
}

void Semaphore::release()
{
	lockStuff();

	if (firstWaitingTask != nullptr) {
		// We need to wake up the first task that was waiting for the semaphore
		// Note: "semaphore->current_count" remains the same (this task leaves and another task enters)

		ThreadControlBlock* task = (ThreadControlBlock*) firstWaitingTask;
		firstWaitingTask = (ThreadControlBlock*) task->next;
		unblockTask(task);

	} else {
		// No tasks are waiting
		currentCount--;
	}

	unlockStuff();
}

Mutex::Mutex() : Semaphore(1)
{

}