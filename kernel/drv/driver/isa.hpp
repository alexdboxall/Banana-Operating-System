#pragma once

#include <drv/device.hpp>
#include <drv/driver.hpp>
#include <drv/bus.hpp>

#define ISA_DRIVER_NAME "ISA Bus"

class ISADriver : public Driver
{
private:
	int numCOMsFound = 0;
	void detectCOMPort(uint16_t base);

protected:
	void initialise();
	void detect();
	void deinitialise();
	void setPowerState(DevicePowerState state);
	const char* getHumanReadableName();
};
