#pragma once

#include <drv/device.hpp>
#include <drv/driver.hpp>

class KeyboardDriver : public Driver
{
private:
	bool capsLock;
	bool scrollLock;
	bool numLock;

protected:
	virtual void setRepeatRate(int t) = 0;
	virtual void setRepeatDelay(int t) = 0;
};

class KeyboardHardware : public Hardware
{
protected:
	KeyboardDriver* driver;

	virtual Driver* _getDriver() override
	{
		return (Driver*) driver;
	}

	HardwareType getType()
	{
		return HardwareType::Keyboard;
	}
};