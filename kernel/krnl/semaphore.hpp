#pragma once

struct ThreadControlBlock;

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
	int acquire(int milliseconds);
	void acquire();
	bool tryAcquire();
	void release();

	void assertLocked(const char* msg = "SEMAPHORE SHOULD BE LOCKED");
};
