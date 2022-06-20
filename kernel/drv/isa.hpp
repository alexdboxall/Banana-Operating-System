#pragma once

#include <drv/bus.hpp>

class ISADriver : public BusDriver
{
public:
	ISADriver()
	{

	}

	void initialise();
	void detect();
	void deinitialise();
	void setPowerState(DevicePowerState state);
	const char* getHumanReadableName();
};
