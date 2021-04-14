
#ifndef _PRCSSTHR_HPP_
#define _PRCSSTHR_HPP_

#include <stdint.h>
#include <stddef.h>
#include "coreobjs/linkedlist.hpp"
#include "core/main.hpp"
#include "core/pipe.hpp"
#include "core/virtmgr.hpp"
#include "krnl/env.hpp"

struct Process;

enum class TaskState: size_t
{
	ReadyToRun = 0,
	Running = 1,
	Paused = 2,
	Sleeping = 3,
	Terminated = 4,
	WaitingForLock = 5,
	WaitingForKeyboard = 6,
	WaitPID = 7,
};

#pragma pack(push,1)
struct ThreadControlBlock
{
	volatile size_t cr3;					//MUST BE AT OFFSET 0x0			INTO THE STRUCT
	volatile size_t esp;					//MUST BE AT OFFSET 0x4/0x8		INTO THE STRUCT
	volatile size_t krnlStack;				//MUST BE AT OFFSET 0x8/0x10	INTO THE STRUCT		(USELESS)
	volatile size_t firstTimeEIP;			//MUST BE AT OFFSET 0xC/0x18	INTO THE STRUCT
	volatile uint64_t timeKeeping;			//MUST BE AT OFFSET 0x10/0x20	INTO THE STRUCT
	volatile enum TaskState state;			//MUST BE AT OFFSET 0x18/0x28	INTO THE STRUCT

	volatile size_t magicForkyParentSavePoint;			//MUST BE AT OFFSET 0x1C/0x30	INTO THE STRUCT

	volatile ThreadControlBlock* volatile next = nullptr;
	volatile ThreadControlBlock* volatile prev = nullptr;
	volatile ThreadControlBlock* volatile nextForNonSchedulingThings = nullptr;

	volatile uint64_t sleepExpiry;
	int forkret;

	size_t timeSliceRemaining;

	int rtid;		//relative thread ID to the process (e.g. thread 0, thread 1, etc.)
	Process* processRelatedTo = nullptr;

	uint8_t priority;

	void* startContext;

	int waitingPID;						//as specified here: http://man7.org/linux/man-pages/man2/waitid.2.html
	int* wstatus;						//same link, we're not using it at the moment
	int waitingThreadReturnCode;

	int returnCodeForUseOnTerminationList;

	uint16_t vm86IP;
	uint16_t vm86CS;
	uint16_t vm86SP;
	uint16_t vm86SS;
	bool vm86VIE = false;
	bool vm86Task = false;

	//uint8_t* fpuState = nullptr;
};

struct Process
{
	int pid;

	size_t* pointersToDelete;
	int nextDeletablePointer;

	char taskname[256];
	char cwd[256];

	ThreadControlBlock threads[8];
	uint16_t threadUsage;			//one bit per thread

	VgaText* terminal;

	Process* parent;

	size_t usermodeEntryPoint;

	VAS* vas;

	int argc;
	char* argv[128];

	EnvVarContainer* env;

	bool failedToLoadProgram = false;

	void addArgs(char** _argv);
	Process(bool kernel, const char* name, Process* parent = nullptr, char** argv = nullptr);
	Process(const char* filepath, Process* parent = nullptr, char** argv = nullptr);

	ThreadControlBlock* createThread(void (*where)(void*), void* context = nullptr, int pri = 128);
	ThreadControlBlock* createUserThread();
};

void userModeEntryPoint(void* ignored);

#pragma pack(pop)

class Semaphore
{
private:

protected:
	int maxCount;
	ThreadControlBlock* firstWaitingTask;
	ThreadControlBlock* lastWaitingTask;

public:
	int currentCount;

	Semaphore(int maxCount);
	void acquire();
	void release();
	bool tryAcquire();

	void assertLocked(const char* msg = "SEMAPHORE SHOULD BE LOCKED");
};

class Mutex: public Semaphore
{
private:

protected:

public:
	Mutex();
};


//JUST FOR NOW	- NEEDS TO BE UPDATED IN hardware.asm IF THIS IS CHANGED
#define currentTaskTCB (*((ThreadControlBlock**) 0xC2002000))		

extern "C" size_t taskStartupFunction();
extern "C" void taskReturned();

void switchToThread(ThreadControlBlock* nextThreadToRun);
void setupMultitasking(void (*where)());
void schedule();
void lockScheduler(void);
void unlockScheduler(void);
void blockTask(enum TaskState reason);
void blockTaskWithSchedulerLockAlreadyHeld(enum TaskState reason);
void unblockTask(ThreadControlBlock* task);
void unlockStuff(void);
void lockStuff(void);
void sleep(uint64_t seconds);
void nanoSleep(uint64_t nanoseconds);
void updateTimeUsed();
void cleanerTaskFunction(void* context);
int waitTask(int pid, int* wstatus, int options);
void disableIRQs();
void enableIRQs();
int getIRQNestingLevel();

extern Process* kernelProcess;
extern ThreadControlBlock* cleanerThread;
extern LinkedList<volatile ThreadControlBlock> sleepingTaskList;

extern void terminateTask(int returnCode = 0);

namespace Thr
{
	void terminateFromIRQ(int returnCode = 0);
}

#endif