#pragma once

#include <drv/device.hpp>
#include <drv/driver.hpp>
#include <drv/bus.hpp>

#define ISA_PNP_DRIVER_NAME		"ISA Plug and Play Bus"

class ISAPnPDriver : public BusDriver
{
private:
	const uint16_t ADDRESS_PORT	= 0x0279;
	const uint16_t WRITE_DATA_PORT = 0x0A79;
	uint16_t READ_DATA_PORT = 0x0203;

	void changeReadPortBase();
	uint64_t isolateCard();

	void writeRegister(uint8_t address, uint8_t value);
	uint8_t readRegister(uint8_t address);

	void resetAllCards();
	void sendInitiationKey();

public:
	ISAPnPDriver()
	{

	}

	void initialise();
	void detect();
	void deinitialise();
	void setPowerState(DevicePowerState state);
	const char* getHumanReadableName();
};
