#include "core/prcssthr.hpp"
#include "core/syscalls.hpp"
#include "hal/intctrl.hpp"

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
	/// <returns>Always returns zero.</returns>
	/// 
	uint64_t yield(regs* r)
	{
		lockScheduler();
		schedule();
		unlockScheduler();

		return 0;
	}
}


