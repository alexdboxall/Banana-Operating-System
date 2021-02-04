#include "core/prcssthr.hpp"
#include "core/syscalls.hpp"
#include "hal/intctrl.hpp"

//#pragma GCC optimize ("Os")

/// <summary>
/// Yields the currently running thread's timeslice.
/// </summary>
/// <returns>Always returns zero.</returns>
/// 
uint64_t sysCallYield(regs* r)
{
	lockScheduler();
	schedule();
	unlockScheduler();

	return 0;
}

