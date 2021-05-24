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

	uint32_t a = (uint32_t) v;

	int hertz = a & 0xFFFF;
	int milli = a >> 16;
	
	Hal::makeBeep(hertz);
	milliTenthSleep(milli * 10);
	Hal::stopBeep();

	blockTask(TaskState::Terminated);
}

namespace Krnl
{
	void beep(int hertz, int millisecs, bool blocking)
	{
		start(hertz);
		if (blocking) {
			milliTenthSleep(10 * millisecs);
			stop();
		} else {
			uint32_t a = hertz;
			a |= millisecs << 16;
			kernelProcess->createThread(beepThread, a, 230);
		}
	}

	void stop()
	{
		start(0);
	}
}