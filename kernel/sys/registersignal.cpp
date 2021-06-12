#include <thr/prcssthr.hpp>
#include <krnl/signal.hpp>
#include <sys/syscalls.hpp>
#include <hal/intctrl.hpp>

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

/// <summary>
/// Sets a signal handler for the current process.
/// </summary>
/// <param name="ebx">The signal number.</param>
/// <param name="edx">The signal handler, which is either a pointer to a user function, or SIG_DFL for default handling, or SIG_IGN for no handling.</param>
/// <returns>Returns zero on success, and non-zero on failure.</returns>
uint64_t SysRegisterSignal(regs* r)
{
	return KeRegisterSignalHandler(&currentTaskTCB->processRelatedTo->signals, r->ebx, (sig_handler_bna_t) handler, 0, 0);
}
