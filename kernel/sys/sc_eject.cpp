#include "thr/prcssthr.hpp"
#include "sys/syscalls.hpp"
#include "hal/intctrl.hpp"
#include "fs/vfs.hpp"
#include "hal/timer.hpp"
#include "hal/device.hpp"
#include "hal/vcache.hpp"

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

namespace Sys
{
	/// <summary>
	/// Ejects a disk such as a CD.
	/// </summary>
	/// <param name="ebx">The drive number.</param>
	/// <returns>Returns 0 on success, or -1 if non-removable disk or a positive non-zero integer if the operation failed.</returns>
	/// 
	uint64_t eject(regs* r)
	{
		return disks[r->ebx - 'A']->eject();
	}
}


