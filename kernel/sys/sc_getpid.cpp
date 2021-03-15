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
	/// Returns the process ID of the calling process.
	/// </summary>
	/// <returns>Returns the process ID.</returns>
	/// 
	uint64_t sysCallGetPID(regs* r)
	{
		return currentTaskTCB->processRelatedTo->pid;
	}
}


