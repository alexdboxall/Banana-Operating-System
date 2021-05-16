#ifndef _POWCTRL_HPP_
#define _POWCTRL_HPP_

#include <stdint.h>
#include <stddef.h>
#include "hal/device.hpp"

namespace Krnl
{
	enum class PowerButtonOption : int
	{
		Nothing,
		Sleep,
		Shutdown,
		TurnOffDisplay,
	};

	struct PowerSettings
	{
		PowerButtonOption powerButton;
		PowerButtonOption sleepButton;
		PowerButtonOption lidClosed;

		int poweredSecsBeforeDisplayOff;
		int poweredSecsBeforeDiskOff;
		int poweredSecsBeforeSleep;

		int batterySecsBeforeDisplayOff;
		int batterySecsBeforeDiskOff;
		int batterySecsBeforeSleep;
	};

	int secondsSinceLastUserIO;
	PowerSettings currentPowerSettings;
	bool powCtrlOnBattery;

	void changePowerSettings(PowerSettings settings);
	void setupPowerManager();
	void userIOReceived();
	void powCtrlSetPowerState(bool battery);
}

#endif