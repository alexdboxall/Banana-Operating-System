#include <thr/prcssthr.hpp>

extern "C" void CUnlockScheduler()
{
	unlockScheduler();
}

extern "C" void CLockScheduler()
{
	lockScheduler();
}

extern "C" void CPrintf(const char* x, ...)
{
	kprintf("%s", x);
}