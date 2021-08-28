#pragma once

struct struct ThreadControlBlock;

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
