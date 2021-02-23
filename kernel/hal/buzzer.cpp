#include "core/main.hpp"
#include "hal/device.hpp"
#include "hal/buzzer.hpp"
#include "thr/prcssthr.hpp"

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

Buzzer* systemBuzzer = nullptr;

Buzzer::Buzzer(const char* name) : Device(name)
{
	deviceType = DeviceType::Buzzer;
}

Buzzer::~Buzzer()
{

}

void beepThread(void* v)
{
	unlockScheduler();
	
	Buzzer* buzzer = (Buzzer*) v;
	nanoSleep(1000ULL * 1000ULL * (uint64_t) buzzer->timeToSleepInThread);
	buzzer->stop();

	blockTask(TaskState::Terminated);
}

void Buzzer::beep(int hertz, int millisecs, bool blocking)
{
	start(hertz);
	if (blocking) {
		nanoSleep(1000 * 1000 * millisecs);
		stop();
	} else {
		timeToSleepInThread = millisecs;
		kernelProcess->createThread(beepThread, this, 230);
	}
}

void Buzzer::stop()
{
	start(0);
}