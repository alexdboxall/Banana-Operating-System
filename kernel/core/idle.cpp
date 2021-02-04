#include "core/idle.hpp"
#include "core/prcssthr.hpp"
#include "core/computer.hpp"
#include "hw/cpu.hpp"
#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

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