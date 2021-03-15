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
	/// Sets the current working directory for the current process.
	/// </summary>
	/// <param name="ebx">The directory name to switch to.</param>
	/// <returns>Returns the return code.</returns>
	/// 
	uint64_t sysCallSetCwd(regs* r)
	{
		return setcwd(currentTaskTCB->processRelatedTo, (char*) r->ebx);
	}
}


