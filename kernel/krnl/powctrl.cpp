#include "krnl/main.hpp"
#include "krnl/common.hpp"
#include "thr/prcssthr.hpp"
#include "krnl/powctrl.hpp"

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

int secondsSinceLastUserIO;
PowerSettings currentPowerSettings;
bool powCtrlOnBattery;

void KeChangePowerSettings(PowerSettings settings)
{
	currentPowerSettings = settings;
}

void KePowerThread(void* context)
{
	unlockScheduler();

	while (1) {
		powCtrlOnBattery = false;

		int displayOffThreshold = powCtrlOnBattery ? currentPowerSettings.batterySecsBeforeDisplayOff : currentPowerSettings.poweredSecsBeforeDisplayOff;
		int diskOffThreshold = powCtrlOnBattery ? currentPowerSettings.batterySecsBeforeDiskOff : currentPowerSettings.poweredSecsBeforeDiskOff;
		int sleepThreshold = powCtrlOnBattery ? currentPowerSettings.batterySecsBeforeSleep : currentPowerSettings.poweredSecsBeforeSleep;

		sleep(10);
		secondsSinceLastUserIO += 10;

		if (secondsSinceLastUserIO > displayOffThreshold && displayOffThreshold) {
			//turn the display off
		}

		if (secondsSinceLastUserIO > diskOffThreshold && diskOffThreshold) {
			//turn the disk drives off
		}

		if (secondsSinceLastUserIO > sleepThreshold && sleepThreshold) {
			//go to sleep
			//KeSleep();
		}
	}
}

void KeUserIOReceived()
{
	secondsSinceLastUserIO = 0;
}

void KeHandlePowerButton()
{
	if (currentPowerSettings.powerButton == PowerButtonOption::Shutdown) {
		KeShutdown();

	} else if (currentPowerSettings.powerButton == PowerButtonOption::Sleep) {
		KeSleep();
	}
}

void KeHandleSleepButton()
{
	if (currentPowerSettings.sleepButton == PowerButtonOption::Shutdown) {
		KeShutdown();

	} else if (currentPowerSettings.sleepButton == PowerButtonOption::Sleep) {
		KeSleep();
	}
}

void KeSetupPowerManager()
{
	secondsSinceLastUserIO = 0;
	powCtrlOnBattery = false;

	kernelProcess->createThread(KePowerThread, nullptr, 240);

	currentPowerSettings.powerButton = PowerButtonOption::Shutdown;
	currentPowerSettings.sleepButton = PowerButtonOption::Sleep;
	currentPowerSettings.lidClosed = PowerButtonOption::DisplayOff;

	currentPowerSettings.poweredSecsBeforeDisplayOff = 0;		//none
	currentPowerSettings.batterySecsBeforeDisplayOff = 0;		//none

	currentPowerSettings.poweredSecsBeforeDiskOff = 0;			//none
	currentPowerSettings.batterySecsBeforeDiskOff = 0;			//none

	currentPowerSettings.poweredSecsBeforeSleep = 60;			//none
	currentPowerSettings.batterySecsBeforeSleep = 60;			//none
}