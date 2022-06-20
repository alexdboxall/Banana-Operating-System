
#pragma once

#include <drv/device.hpp>

class Driver
{
public:
	Hardware* hw;

	Driver()
	{

	}

	virtual const char* getHumanReadableName() = 0;
	virtual void initialise() = 0;
	virtual void detect() = 0;
	virtual void deinitialise() = 0;
	virtual void setPowerState(DevicePowerState state) = 0;
};