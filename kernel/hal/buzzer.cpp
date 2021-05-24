#include "core/main.hpp"
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

void beepThread(void* v)
{
	unlockScheduler();

	milliTenthSleep(((int) v) * 10);
	Hal::stopBeep();

	blockTask(TaskState::Terminated);
}

namespace Krnl
{
	void beep(int hertz, int millisecs, bool blocking)
	{
		Hal::makeBeep(hertz);

		if (blocking) {
			milliTenthSleep(10 * millisecs);
			Hal::stopBeep();

		} else {
			kernelProcess->createThread(beepThread, (void*) millisecs, 230);
		}
	}
}