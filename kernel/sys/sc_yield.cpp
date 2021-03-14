#include "thr/prcssthr.hpp"
#include "sys/syscalls.hpp"
#include "hal/intctrl.hpp"
#include "hal/timer.hpp"

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

namespace Sys
{
	/// <summary>
	/// Yields the currently running thread's timeslice.
	/// </summary>
	/// <returns>Returns a random value based on the system timer.</returns>
	/// 
	uint64_t yield(regs* r)
	{
		lockScheduler();
		schedule();
		unlockScheduler();

		return nanoSinceBoot >> 24;
	}
}


