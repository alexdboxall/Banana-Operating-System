#include "krnl/main.hpp"
#include "hal/device.hpp"
#include "hal/buzzer.hpp"
#include "thr/prcssthr.hpp"
#include "krnl/hal.hpp"

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

void KeBeepThread(void* v)
{
	unlockScheduler();

	milliTenthSleep(((int) v) * 10);
	HalMakeBeep(0);

	blockTask(TaskState::Terminated);
}

void KeBeep(int hertz, int millisecs, bool blocking)
{
	HalMakeBeep(hertz);

	if (blocking) {
		milliTenthSleep(10 * millisecs);
		HalMakeBeep(0);

	} else {
		kernelProcess->createThread(KeBeepThread, (void*) millisecs, 230);
	}
}