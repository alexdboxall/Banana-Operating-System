#include "core/idle.hpp"
#include "core/prcssthr.hpp"
#include "core/computer.hpp"
#include "hw/cpu.hpp"
//#pragma GCC optimize ("Os")

inline void idleCommon()
{
	//TODO: do stuff here...

	lockScheduler();
	schedule();
	unlockScheduler();
}

extern "C" void doTPAUSE();

void idleFunction(void* context)
{
	unlockScheduler();

	if (thisCPU()->features.hasTPAUSE && computer->features.hasMSR) {
		//set mode, no timeout and 
		uint64_t msr = computer->rdmsr(0xE1);
		computer->wrmsr(0xE1, msr & 2);	//only keep bit 1 as it is reserved
		while (1) {
			doTPAUSE();
			idleCommon();
		}

	} else {
		while (1) {
			asm volatile("sti; hlt");
			idleCommon();
		}
	}
}