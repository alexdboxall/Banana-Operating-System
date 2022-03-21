#include <krnl/main.hpp>
#include <krnl/common.hpp>
#include <krnl/powctrl.hpp>
#include <krnl/atexit.hpp>
#include <krnl/hal.hpp>
#include <thr/prcssthr.hpp>
#include <hw/acpi.hpp>

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



// Stores the functions responsible for physically turning off, restarting or putting the computer into sleep mode
// This allows a standard interface for shutdown, etc. even with different hardware implementations
void (*keShutdownFunction)() = nullptr;
void (*keRestartFunction)() = nullptr;
void (*keSleepFunction)() = nullptr;

/// <summary>
/// Performs system deinitialisation. This includes calling atexit handlers and calling destructors for drivers.
/// </summary>
void KePrepareShutdown()
{
	KeExecuteAtexit();
	computer->root->closeAll();
}

/// <summary>
/// The function passed to this function will be called to when we need to turn off the computer.
/// The function passed should immediately turn the computer off, and not do anything else.
/// If the computer does not support shutdown, the function passed may simply do nothing.
/// </summary>
/// <param name="shutdownFunc">A function which can turn off the computer.</param>
void KeRegisterShutdownHandler(void (*shutdownFunc)())
{
	keShutdownFunction = shutdownFunc;
}

/// <summary>
/// The function passed to this function will be called to when we need to restart the computer.
/// The function passed should immediately restart the computer, and not do anything else. This function
/// must succeed in restarting the computer, otherwise it should panic.
/// </summary>
/// <param name="restartFunc">A function which can restart the computer.</param>
void KeRegisterRestartHandler(void (*restartFunc)())
{
	keRestartFunction = restartFunc;
}

/// <summary>
/// The function passed to this function will be called to when we need to put the computer to sleep.
/// The function passed should immediately put the computer to sleep. It should also completely get the
/// computer out of sleep before it returns.
/// If the computer does not support sleep, the function passed may simply do nothing.
/// </summary>
/// <param name="restartFunc">A function which can restart the computer.</param>
void KeRegisterSleepHandler(void (*sleepFunc)())
{
	keSleepFunction = sleepFunc;
}

/// <summary>
/// Performs system deinitialisation, and then turns the computer off.
/// This function will never return, even if the computer does not support being turned off.
/// </summary>
void KeShutdown()
{
	KePrepareShutdown();

	if (keShutdownFunction) {
		keShutdownFunction();
	} else {
		KePanic("NO SHUTDOWN FUNCTION IMPLEMENTED");
	}

	KePanic("You may now turn off your computer.");
}

/// <summary>
/// Puts the computer into sleep mode if it is supported. The function will return after
/// the computer has been woken up.
/// </summary>
void KeSleep()
{
	if (keSleepFunction) {
		keSleepFunction();
	}
}

/// <summary>
/// Performs systems deinitialisation, and then reboots the computer.
/// This function will never return.
/// </summary>
void KeRestart()
{
	KePrepareShutdown();

	if (keRestartFunction) {
		keRestartFunction();

	}

	KePanic("RESTART FAILED");
}
