#pragma once

#include <drv/device.hpp>
#include <drv/driver.hpp>
#include <drv/bus.hpp>

#define ACPI_DRIVER_NAME "ACPI"

class ACPIDriver : public BusDriver
{
private:

protected:
	void initialise();
	void detect();
	void deinitialise();
	void setPowerState(DevicePowerState state);
	const char* getHumanReadableName();
};
