#pragma once

#include <drv/device.hpp>
#include <drv/driver.hpp>

class LegacyDMADriver : public Driver
{
public:
	LegacyDMADriver()  {

	}
};

class LegacyDMAHardware : public Hardware
{
protected:
	virtual Driver* _getDriver() override
	{
		return (Driver*) driver;
	}

	HardwareType getType()
	{
		return HardwareType::LegacyDMA;
	}
	
public:
	LegacyDMADriver* driver;

	LegacyDMAHardware() : Hardware()
	{
		driver = nullptr;
	}

	void setDriver(LegacyDMADriver* _driver)
	{
		driver = _driver;
		driver->hw = this;
		driver->initialise();
	}
};
