#include "thr/prcssthr.hpp"
#include "sys/syscalls.hpp"
#include "hal/intctrl.hpp"

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

/// <summary>
/// Terminates the currently running thread. If this is the last running thread, the entire process will be terminated.
/// </summary>
/// <param name="ebx">The exit code for the thread.</param>
/// <returns>This system call should not return. If it does, it will return -1.</returns>
/// 
uint64_t SysExit(regs* r)
{
	terminateTask(r->ebx);
	return -1;
}