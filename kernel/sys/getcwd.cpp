#include "thr/prcssthr.hpp"
#include "sys/syscalls.hpp"
#include "hal/intctrl.hpp"
#include "fs/vfs.hpp"
#include "hal/timer.hpp"

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")


/// <summary>
/// Sets the current working directory for the process.
/// </summary>
/// <param name="ebx">A pointer to where the current working directory should be stored.</param>
/// <param name="ecx">The maximum number of bytes to copy to the buffer.</param>
/// <returns>Returns the return code.</returns>
/// 
uint64_t SysGetCwd(regs* r)
{
	return Fs::getcwd(currentTaskTCB->processRelatedTo, (char*) r->ebx, r->ecx);
}
