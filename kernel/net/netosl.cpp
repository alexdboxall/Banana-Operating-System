
#include <net/netosl.hpp>
#include <krnl/semaphore.hpp>
#include <thr/prcssthr.hpp>

extern "C" void KeNetCreateSemaphore(size_t* mutex, int count)
{
	Semaphore* sem = new Semaphore(count);
	*mutex = (size_t) sem;
}

extern "C" void KeNetFreeSemaphore(size_t* mutex)
{
	delete ((Semaphore*) (*mutex));
}

extern "C" void KeNetSignalSemaphore(size_t* mutex)
{
	((Semaphore*) (*mutex))->release();
}

extern "C" int KeNetWaitSemaphore(size_t* mutex, int millisecs)
{
	return ((Semaphore*) (*mutex))->acquire(millisecs);
}

extern "C" void KeNetCreateThread(void (*thread)(void*), void* arg)
{
	kernelProcess->createThread(thread, arg, 128);
}