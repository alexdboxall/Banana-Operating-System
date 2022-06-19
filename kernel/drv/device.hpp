
#pragma once
#include <stddef.h>
#include <stdint.h>

#include <cpp/vector.hpp>

#define HARDWARE_MAX_IRQ_REGISTRATIONS 4
#define CREATE_HARDWARE_SUBCLASS(name) class## ##name##Hardware : public Hardware { protected:##name##Driver* driver;virtual Driver* _getDriver() override{return (Driver*) driver;}HardwareType getType(){return HardwareType::##name##;}};

class Driver;

enum class DeviceRootConnectionType
{
	Manual,
	ISA,
	PCI,
	ACPI
};

enum class DevicePowerState
{
	Active,
	Standby,
	Off,
	Hibernate,
	WakeFromHibernate,
};

enum class HardwareType
{
	Unknown,
	Bus,
	Keyboard,
	Mouse,
};

enum class BuiltinDriver
{
	PCI,
	ATA,
	ATAPI,
	IDE,
	SATA,
	SATAPI,
	ACPI,
	ISA,
};

struct DeviceMemoryRange
{
	size_t start;
	size_t length;
};

struct DevicePortRange
{
	uint16_t start;
	uint8_t length;
	uint8_t alignment : 6;	//used by Windows, no idea what it does
	uint8_t width : 2;		//in bytes: e.g 0 = 1, 1 = 2, 2 = 4, 3 = 8
};

class Hardware
{
private:
	
	// only used to allow the '...Recursively' functions work
	virtual Driver* _getDriver() = 0;

protected:
	std::vector<Hardware*> children;
	std::vector<DeviceMemoryRange> memoryRanges;
	std::vector<DevicePortRange> portRanges;

	int irqs[HARDWARE_MAX_IRQ_REGISTRATIONS];
	uint8_t irqUsageBitflags;
	char name[128];

	void registerIRQ(int irq);
	void deregisterIRQ(int irq);
	void registerMemoryRange(size_t start, size_t length);
	void registerPortRange(uint16_t start, uint8_t length, int width);

	void addChild(Hardware* child);
	void removeChild(Hardware* child);

	void setHumanReadableName(const char* name);

	void detectRecursively();
	void deinitialiseRecursively();
	void setPowerStateRecursively(DevicePowerState level);

	virtual HardwareType getType() = 0;

public:
	virtual ~Hardware();

	Hardware();
	Hardware(BuiltinDriver driver);
	Hardware(const char* driverPath);
};