#include "thr/prcssthr.hpp"
#include "sys/syscalls.hpp"
#include "hal/intctrl.hpp"
#include "fs/vfs.hpp"
#include "hal/timer.hpp"
#include "hal/device.hpp"
#include "hal/vcache.hpp"
#include <thr/alarm.hpp>

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

/// <summary>
/// Sets an alarm, causing SIGALRM to be called after a specified number of millitenths (100 microseconds).
/// </summary>
/// <param name="ebx">The number of millitenths to wait, or zero to cancel the alarm.</param>
/// <returns>Returns in how many millitenths the previous alarm would have gone off, or zero if non was scheduled.</returns>
/// 
uint64_t SysAlarm(regs* r)
{
	kprintf("setting alarm to %d\n", (int) r->ebx);
	return KeAlarm(currentTaskTCB, r->ebx);
}


