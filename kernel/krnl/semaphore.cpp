#include <krnl/semaphore.hpp>
#include <thr/prcssthr.hpp>

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
		KePanic(msg);
	}

	unlockStuff();
}

int Semaphore::acquire(int milliseconds)
{
	if (milliseconds) {
		int time = 0;
		bool waited = true;
		while (waited) {
			waited = !tryAcquire();
			if (!waited) break;

			if (milliseconds <= 40) {
				milliTenthSleep(milliseconds * 10);
				time += milliseconds;
				milliseconds = 0;
			} else {
				milliTenthSleep(40 * 10);
				time += 40;
				milliseconds -= 40;
			}
		}
		return time;

	} else {
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
		return 0;
	}
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