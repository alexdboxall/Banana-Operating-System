#include "thr/prcssthr.hpp"
#include "core/common.hpp"
#include "core/terminal.hpp"
#include "libk/string.h"
#include "hw/cpu.hpp"
#include "core/kheap.hpp"
#include "krnl/hal.hpp"
#include "core/physmgr.hpp"
#include "thr/elf.hpp"

#pragma GCC optimize ("O2")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

#define STACK_LEEWAY 32

namespace Thr
{
	int nextPID = 1;
};

Process* kernelProcess = nullptr;
LinkedList<volatile ThreadControlBlock> taskList;
LinkedList<volatile ThreadControlBlock> sleepingTaskList;
LinkedList<volatile ThreadControlBlock> terminatedTaskList;

int irqDisableCounter = 0;
int postponeTaskSwitchesCounter = 0;
int taskSwitchesPostponedFlag = 0;

extern "C" void switchToThreadASM(ThreadControlBlock* nextThreadToRun);
extern "C" void switchToThreadASMFirstTime(ThreadControlBlock* nextThreadToRun);

extern "C" void changeTSS()
{
	CPU::current()->tss.setESP(VIRT_APP_STACK_KRNL_TOP - SIZE_APP_STACK_TOTAL * currentTaskTCB->rtid);
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
		//51 ms - 0.05ms/priority

		//RANGE:
		//Priority 0  : 51ms	(old was 58ms)
		//Priority 128: 45ms	(old was 51ms)
		//Priority 254: 38ms	(old was 42ms)
		nextThreadToRun->timeSliceRemaining += (1024 - nextThreadToRun->priority) >> 1;
	}


	static uint64_t currentCount = 0;
	static uint64_t elapsed = 0;
	static uint64_t lastCount = 0;

	currentCount = HalQueryPerformanceCounter();
	elapsed = currentCount - lastCount;
	lastCount = currentCount;

	currentTaskTCB->timeKeeping += elapsed;

	HalSaveCoprocessor(currentTaskTCB->fpuState);
	switchToThreadASM(nextThreadToRun);
	HalLoadCoprocessor(currentTaskTCB->fpuState);
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
	if (!threads[threadNo].vm86Task) {
		threads[threadNo].fpuState = HalAllocateCoprocessorState();
	}
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
	setActiveTerminal(p->terminal);

	p->threadUsage |= 1;
	p->threads[0].fpuState = HalAllocateCoprocessorState();
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

Process::Process(const char* _filepath, Process* _parent, char** _argv)
{
	env = Krnl::newProcessEnv(this);
	threadUsage = 0;
	pid = Thr::nextPID++;
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

	bool f = Thr::loadProgramIntoMemory(this, _filepath);
	failedToLoadProgram = !f;
	kprintf("LOAD PROGRAM INTO MEMORY RETURNED %d\n", f);
}

Process::Process(bool _kernel, const char* _name, Process* _parent, char** _argv)
{
	env = Krnl::newProcessEnv(this);
	threadUsage = 0;
	pid = Thr::nextPID++;
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

size_t schedulerLock;
size_t lockStuffLock;
size_t retValSchedLock;
size_t retValLockStuff;

extern "C" unsigned long asmAcquireLock(size_t*);
extern "C" void asmReleaseLock(size_t*, size_t);

extern bool displayCliSti;

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

		delete task->processRelatedTo->env;

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
	}

	if (!task->vm86Task) {
		//delete task;
	}
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
	currentTaskTCB->state = reason;
	schedule();
	unlockScheduler();
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
		kprintf("THIS MIGHT BE BAD (A)\n");

	} else if (task->state == TaskState::Running) {
		kprintf("THIS MIGHT BE BAD (B)\n");

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
		taskList.addElement(task);
	}

	unlockScheduler();
}

void milliTenthSleepUntil(uint32_t when)
{
	if (when < milliTenthsSinceBoot) {
		return;
	}

	lockStuff();

	currentTaskTCB->sleepExpiry = when;
	sleepingTaskList.addElement(currentTaskTCB);
	blockTask(TaskState::Sleeping);
	unlockStuff();
}


void milliTenthSleep(uint32_t mtens)
{
	milliTenthSleepUntil(milliTenthsSinceBoot + mtens);
}

void sleep(uint32_t seconds)
{
	milliTenthSleep(seconds * 10000);
}

extern "C" void taskReturned()
{	
	panic("TASK RETURNED. CHECK KERNEL TASKS AND ALL DRIVERS.\n");

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

		kprintf("blocking on Semaphore::acquire");
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

namespace Thr
{
	void terminateFromIRQ(int returnCode)
	{
		terminateTask(returnCode);
	}

	Process* processFromPID(int pid)
	{
		lockScheduler();
		auto first = taskList.getFirstElement();

		while (1) {
			auto tcb = taskList.getFirstElement();
			taskList.removeFirst();
			taskList.addElement(tcb);

			if (tcb->processRelatedTo->pid == pid) {
				unlockScheduler();
				return tcb->processRelatedTo;
			}

			if (taskList.getFirstElement() == first) {
				break;
			}
		}

		unlockScheduler();

		return nullptr;

		//taskList;
		//LinkedList<volatile ThreadControlBlock> sleepingTaskList;
	}
}