#pragma once

#include <drv/device.hpp>
#include <drv/driver.hpp>
#include <drv/bus.hpp>

#define PCI_DRIVER_NAME "PCI Bus"

class PCIDriver : public BusDriver
{
private:

public:
	void initialise();
	void enumerateDevices();

	void detect();
	void deinitialise();
	void setPowerState(DevicePowerState state);
	const char* getHumanReadableName();

	void checkBus(uint8_t bus);
	void checkDevice(uint8_t bus, uint8_t device);
	void registerDevice(uint8_t bus, uint8_t slot, uint8_t function);

	uint16_t getVendorID(uint8_t bus, uint8_t slot, uint8_t function);
	uint16_t getHeaderType(uint8_t bus, uint8_t slot, uint8_t function);
	uint16_t getClassCode(uint8_t bus, uint8_t slot, uint8_t function);
	uint8_t getProgIF(uint8_t bus, uint8_t slot, uint8_t function);
	uint8_t getRevisionID(uint8_t bus, uint8_t slot, uint8_t function);
	uint8_t getInterruptNumber(uint8_t bus, uint8_t slot, uint8_t function);
	uint32_t getBARAddress(uint8_t barNo, uint8_t bus, uint8_t slot, uint8_t function);
	uint8_t getSecondaryBus(uint8_t bus, uint8_t slot, uint8_t function);

	void writeWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset, uint16_t word);
	uint16_t readWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);

	uint8_t readBAR8(uint32_t addr, int offset = 0);
	uint16_t readBAR16(uint32_t addr, int offset = 0);
	uint32_t readBAR32(uint32_t addr, int offset = 0);

	void writeBAR8(uint32_t addr, uint8_t val, int offset = 0);
	void writeBAR16(uint32_t addr, uint16_t val, int offset = 0);
	void writeBAR32(uint32_t addr, uint32_t val, int offset = 0);

	static const char* lookupDeviceName(DevicePCIConnectionInfo info);
};
