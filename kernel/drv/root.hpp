#pragma once

#include <drv/device.hpp>
#include <drv/driver.hpp>

class RootDriver : public Driver
{
private:
	bool hasACPI();
	bool hasPCI();
	bool hasISAPnP();

public:
	void initialise();
	void detect();
	void deinitialise();
	void setPowerState(DevicePowerState state);
	const char* getHumanReadableName();

	void detectLegacyISA();
};

class RootHardware : public Hardware
{
protected:
	virtual Driver* _getDriver() override
	{
		return (Driver*) driver;
	}

	HardwareType getType()
	{
		return HardwareType::Root;
	}

public:
	RootDriver* driver;

	RootHardware()
	{
		driver = new RootDriver();
	}
};