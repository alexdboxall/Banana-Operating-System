#include "krnl/idle.hpp"
#include "thr/prcssthr.hpp"
#include "krnl/computer.hpp"
#include "krnl/hal.hpp"
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
	
	while (1) {
		HalSystemIdle();
		idleCommon();
	}
}