#pragma once

#include <drv/device.hpp>
#include <drv/driver.hpp>

class BusDriver : public Driver
{
public:
	BusDriver()  {

	}
};

class BusHardware : public Hardware
{
protected:
	virtual Driver* _getDriver() override
	{
		return (Driver*) driver;
	}

	HardwareType getType()
	{
		return HardwareType::Bus;
	}
	
public:
	BusDriver* driver;

	BusHardware() : Hardware()
	{
		driver = nullptr;
	}

	void setDriver(BusDriver* _driver)
	{
		driver = _driver;
		driver->hw = this;
		driver->initialise();
	}
};
