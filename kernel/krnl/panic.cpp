#include "dbg/kconsole.hpp"
#include "krnl/common.hpp"
#include "thr/prcssthr.hpp"
#include "thr/elf.hpp"
#include "hw/cpu.hpp"
#include "krnl/hal.hpp"
#pragma GCC optimize ("O2")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")
#include "krnl/terminal.hpp"

bool keKernelPanicHappening = false;

/// <summary>
/// Returns whether or not KePanic has been called. Only in akward circumstances can this be called,
/// as the caller must be able to run even after KePanic has started executing (ie. either an interrupt handler,
/// the GUI panic hook, or something in HalPanic).
/// </summary>
/// <returns>Returns true if a call to KePanic has started (ie. it will return true in the GUI panic hook), and false if it hasn't.</returns>
bool KeIsKernelInPanic()
{
	return keKernelPanicHappening;
}

/// <summary>
/// To be called when the kernel reaches an unrecoverable error state. This will immediately 
/// hang the system with a fullscreen error message without calling any cleanup.
/// 
/// This function does not return.
/// </summary>
/// <param name="message"></param>
void KePanic(const char* message)
{
	keKernelPanicHappening = true;
	HalPanic(message);
}