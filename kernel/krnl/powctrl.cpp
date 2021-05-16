#include "core/main.hpp"
#include "core/common.hpp"
#include "thr/prcssthr.hpp"
#include "krnl/powctrl.hpp"

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

namespace Krnl
{
	void changePowerSettings(PowerSettings settings)
	{
		currentPowerSettings = settings;
	}

	void powerThread(void* context)
	{
		unlockScheduler();

		while (1) {
			powCtrlOnBattery = false;

			int displayOffThreshold = powCtrlOnBattery ? batterySecsBeforeDisplayOff : poweredSecsBeforeDisplayOff;
			int diskOffThreshold = powCtrlOnBattery ? batterySecsBeforeDiskOff : poweredSecsBeforeDiskOff;
			int sleepOffThreshold = powCtrlOnBattery ? batterySecsBeforeSleep : poweredSecsBeforeSleep;

			sleep(10);
			secondsSinceLastUserIO += 10;

			if (secondsSinceLastUserIO > displayOffThreshold && displayOffThreshold) {
				//turn the display off
			}

			if (secondsSinceLastUserIO > diskOffThreshold && diskOffThreshold) {
				//turn the disk drives off
			}

			if (secondsSinceLastUserIO > sleepOffThreshold && sleepOffThreshold) {
				//go to sleep
				computer->sleep();
			}
		}
	}

	void userIOReceived()
	{
		secondsSinceLastUserIO = 0;
	}

	void setupPowerManager()
	{
		secondsSinceLastUserIO = 0;
		powCtrlOnBattery = false;

		kernelProcess->createThread(powerThread, nullptr, 240);

		currentPowerSettings.poweredSecsBeforeDisplayOff = 0;		//none
		currentPowerSettings.batterySecsBeforeDisplayOff = 0;		//none

		currentPowerSettings.poweredSecsBeforeDiskOff = 0;			//none
		currentPowerSettings.batterySecsBeforeDiskOff = 0;			//none

		currentPowerSettings.poweredSecsBeforeSleep = 60;			//none
		currentPowerSettings.batterySecsBeforeSleep = 60;			//none
	}
}