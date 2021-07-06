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

/// <summary>
/// Sends a signal to another process. Blame POSIX for the misleading name.
/// </summary>
/// <param name="ebx">The signal number to send. A negative value sends the signal to all possible processes.</param>
/// <param name="ecx">The process ID to send the signal to.</param>
/// <returns>Returns 0 on success, or non-zero on failure.</returns>
/// 
uint64_t SysKill(regs* r)
{
	return 1;
}


