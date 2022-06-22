
#pragma once
#include <stddef.h>
#include <stdint.h>

#include <cpp/vector.hpp>

extern "C" {
#include <acpica/acpi.h>
}

#define HARDWARE_MAX_IRQ_REGISTRATIONS 4
#define CREATE_HARDWARE_SUBCLASS(name) class## ##name##Hardware : public Hardware { protected:##name##Driver* driver;virtual Driver* _getDriver() override{return (Driver*) driver;}HardwareType getType(){return HardwareType::##name##;}};

class Driver;

enum class DeviceRootConnectionType
{
	ISAManual,
	ISAPnP,
	PCI,
	ACPI,
	None,
};

typedef struct DevicePCIConnectionInfo
{
	uint8_t classCode;
	uint8_t subClass;
	uint16_t vendorID;

	uint8_t bus;
	uint8_t slot;
	uint8_t function;
	uint8_t progIF;

	uint32_t bar[6];

	uint8_t interrrupt;
	uint8_t intPIN;

	uint16_t deviceID;

} DevicePCIConnectionInfo;

enum class DevicePowerState
{
	Active,
	Standby,
	Off,
	Hibernate,
	WakeFromHibernate,
};

// please keep in this order, a lookup table requires it
enum class HardwareType
{
	Unknown,
	Bus,
	Keyboard,
	Mouse,
	Root,
	PhysicalDisk,
	SerialPort,
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

	void printRecursively(int level);
	void getHardwareOfTypeAux(HardwareType type, std::vector<Hardware*>& vec);

	friend std::vector<Hardware*> KeGetHardwareOfType(HardwareType type);
	friend void KePrintDeviceTree();

protected:
	std::vector<DeviceMemoryRange> memoryRanges;
	std::vector<DevicePortRange> portRanges;

	int irqs[HARDWARE_MAX_IRQ_REGISTRATIONS];
	uint8_t irqUsageBitflags;

public:
	union
	{
		struct
		{
			DevicePCIConnectionInfo info;
		} pci;

		struct
		{
			ACPI_HANDLE handle;
			char namespaceName[30];
			char pnpID[14];
		} acpi;

		struct
		{
			uint16_t probeBase[8];

		} isamanual;

		struct
		{
			uint8_t csn;
			uint32_t vendorID;
			uint32_t serialNumber;

		} isapnp;
	}; 

	DeviceRootConnectionType connectionType;
	
	std::vector<Hardware*> children;

	void registerIRQ(int irq);
	void deregisterIRQ(int irq);
	void registerMemoryRange(size_t start, size_t length);
	void registerPortRange(uint16_t start, uint8_t length, int width);

	void addChild(Hardware* child);
	void removeChild(Hardware* child);

	virtual const char* getHumanReadableName();

	void detectRecursively();
	void deinitialiseRecursively();
	void setPowerStateRecursively(DevicePowerState level);

	virtual HardwareType getType() = 0;

	virtual ~Hardware();
	Hardware();
};

class RootHardware;
class BusHardware;

std::vector<Hardware*> KeGetHardwareOfType(HardwareType type);
void KeSetupDeviceTree();
void KePrintDeviceTree();
RootHardware* KeGetRootDevice();
BusHardware* KeGetPCIDevice();
BusHardware* KeGetACPIDevice();
BusHardware* KeGetISAPnPDevice();
BusHardware* KeGetISADevice();
bool KeIsPortInUse(uint16_t port, int length);