#include "core/virtmgr.hpp"
#include "hw/cpu.hpp"
#include "thr/prcssthr.hpp"

extern "C" CPU* _ZN3CPU7currentEv()		//	CPU::current()
{
	return CPU::current();
}

extern "C" void* _Znwm(size_t size)		//	operator new(size_t)
{
	return malloc(size);
}

extern "C" void _ZdlPv(void* p)			//	operator delete(void*)
{
	rfree(p);
}

extern "C" void _Z11disableIRQsv()
{
	disableIRQs();
}

extern "C" void _Z10enableIRQsv()
{
	enableIRQs();
}

extern "C" void _Z13lockSchedulerv()
{
	lockScheduler();
}

extern "C" void _Z15unlockSchedulerv()
{
	unlockScheduler();
}

extern "C" void _Z9lockStuffv()
{
	lockStuff();
}

extern "C" void _Z11unlockStuffv()
{
	unlockStuff();
}

extern "C" VAS* _ZN4Virt13getAKernelVASEv() {
	return Virt::getAKernelVAS();
}