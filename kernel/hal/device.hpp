#ifndef _HAL_DEVICE_HPP
#define _HAL_DEVICE_HPP

#include <stdint.h>
#include <coreobjs/linkedlist.hpp>
class InterruptController;
extern "C" {
#include "acpica/acpi.h"
}

enum class PowerSavingLevel
{
	Active,
	Standby,
	Sleep
};

enum class DetectionType
{
	Manual,
	ISAProbe,
	PCI,
	ACPI,
	USB
};

struct PortRange
{
	uint16_t rangeStart;
	uint8_t rangeLength;	//0 = not used
	uint8_t alignment : 6;	//used by Windows, no idea what it does
	uint8_t width : 2;		//in bytes: e.g 0 = 1, 1 = 2, 2 = 4, 3 = 8
};

struct MemoryRange
{
	uint64_t rangeStart  : 40;
	uint64_t rangeLength : 24;
};

class Device;
struct DeviceNode
{
	DeviceNode* next;
	Device* child;
};

enum class DeviceType
{
	Bus,
	Clock,
	PhysicalDisk,
	LogicalDisk,
	HardDiskController,
	Joystick,
	Keyboard,
	Printer,
	Port,
	Audio,
	Screen,
	Mouse,
	Buzzer,
	NIC,

	Intctrl,
	Timer,
	FPU,
	CPU,
	SystemDevice,

	Driverless,

	Unknown,
};

struct regs;

typedef struct PCIDeviceInfo
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

} PCIDeviceInfo;

class Device
{
private:

protected:
	PortRange ports[16];
	MemoryRange memory[16];
	uint8_t noPorts;
	uint8_t noMems;

	Device* parent;
	DeviceNode* children;

	char humanName[64];
	DeviceType deviceType;

public:
	void preOpenPCI(PCIDeviceInfo info);
	void preOpenACPI(ACPI_HANDLE h, char* namespaceName, char* pnpID);

	DetectionType detectionType = DetectionType::Manual;
	union
	{
		struct
		{
			PCIDeviceInfo info;
		} pci;

		struct
		{
			ACPI_HANDLE handle;
			char namespaceName[30];
			char pnpID[14];
		} acpi;

		struct
		{
			uint16_t probeBaseA;
			uint16_t probeBaseB;

		} isaprobe;
	};

	Device* next;		//used for linked list enumeration

	Device(const char* name = "Unknown Hardware");
	virtual ~Device();

	Device* getParent();

	void addChild(Device* child);					//Called to add a new child
	void removeAllChildren();

	virtual int open(int, int, void*) = 0;		//Opens the device (init code).
	virtual int close(int, int, void*) = 0;		//Perform other commands

	//These only need to worry about themselves
	virtual void hibernate();					//Get into hibernate state
	virtual void wake();						//Get out of hibernate state
	virtual void detect();						//Detect any children
	virtual void disableLegacy();				//Disable anything legacy
	virtual void powerSaving(PowerSavingLevel level);
	
	void findAndLoadDriver();

	//These call the functions above on all children
	//should not be overriden
	void loadDriversForAll();
	void hibernateAll();
	void wakeAll();
	void closeAll();
	void detectAll();
	void disableLegacyAll();
	void powerSavingAll(PowerSavingLevel level);

	int dmaChannel = -1;
	int interrupt = -1;
	int interrupt2 = -1;

	void setName(const char* name);
	char* getName();

	void addToLinkedList(LinkedList<Device>& list, DeviceType devType);

	int addIRQHandler(int num, void (*handler)(regs*, void*), bool legacy, void* context = nullptr);
	void removeIRQHandler(int num, void (*handler)(regs*, void*), bool legacy);
};

LinkedList<Device> getDevicesOfType(DeviceType devType);

class DriverlessDevice: public Device
{
public:
	DriverlessDevice(const char* name = "Unknown Hardware");
	virtual int open(int, int, void*);			//Opens the device (init code).
	virtual int close(int, int, void*);			//Perform other commands
	virtual void detect();						//Detect any children
};

#endif