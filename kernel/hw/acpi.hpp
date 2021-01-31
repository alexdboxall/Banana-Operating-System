
#ifndef _ACPI_HPP_
#define _ACPI_HPP_

#include <stdint.h>
#include "hal/device.hpp"

extern "C" {
#include "acpica/acpi.h"
}

struct MADTHeader
{
	char Signature[4];
	uint32_t Length;
	uint8_t Revision;
	uint8_t Checksum;
	char OEMID[6];
	char OEMTableID[8];
	uint32_t OEMRevision;
	uint32_t CreatorID;
	uint32_t CreatorRevision;
	uint32_t localControllerAddress;
	uint32_t flags;

	uint8_t data[2000];

} __attribute__((packed));


struct RSDPDescriptor
{
	char Signature[8];
	uint8_t Checksum;
	char OEMID[6];
	uint8_t Revision;
	uint32_t RsdtAddress;

} __attribute__((packed));

struct RSDPDescriptor20
{
	struct RSDPDescriptor firstPart;

	uint32_t Length;
	uint64_t XsdtAddress;
	uint8_t ExtendedChecksum;
	uint8_t reserved[3];

} __attribute__((packed));

struct ACPISDTHeader
{
	char Signature[4];
	uint32_t Length;
	uint8_t Revision;
	uint8_t Checksum;
	char OEMID[6];
	char OEMTableID[8];
	uint32_t OEMRevision;
	uint32_t CreatorID;
	uint32_t CreatorRevision;
} __attribute__((packed));

struct RSDT
{
	struct ACPISDTHeader h;
	uint32_t* PointerToOtherSDT;
};

struct XSDT
{
	struct ACPISDTHeader h;
	uint64_t* PointerToOtherSDT;
};

struct ACPITable
{
	char signature[4];
	void* location;
};


struct SimpleBootFlagTable
{
	struct ACPISDTHeader h;
	uint8_t cmosOffset;
	uint8_t reserved1;
	uint8_t reserved2;
	uint8_t reserved3;
};

struct PCIIRQAssignments
{
	uint16_t slot;

	uint8_t pin;			//ONE BASED!
	uint8_t interrupt;
	ACPI_HANDLE rootBus;

};

class ACPI: public Device
{
private:

protected:

public:
	ACPI();

	bool acpi2 = false;

	void writeSimpleBootFlag(SimpleBootFlagTable* table);

	virtual int open(int, int, void*);			//Opens the device (init code).
	virtual int close(int, int, void*);			//Perform other commands
	void sleep();								//Perform other commands

	void registerPCIIRQAssignment(ACPI_HANDLE handle, uint16_t slot, uint8_t pin, uint8_t irq);

	PCIIRQAssignments getPCIIRQAssignment(uint8_t bus, uint16_t slot, uint8_t pin);

	PCIIRQAssignments pciIRQAssignments[1024];

	int nextPCIIRQAssignment = 0;



	struct ScreenControlInfo
	{
		ACPI_HANDLE handle;

		uint8_t mainsBrightnessLevel;
		uint8_t batteryBrightnessLevel;
		uint8_t currentBrightnessLevel;

		uint8_t valid : 1;
		uint8_t hasBrightnessControl : 1;
		uint8_t numBrightnessLevels : 5;

		uint8_t brightnessLevels[24];


	} screenControlInfo[8];

	int nextScreenControl = 0;

	bool pciDetected = false;


	ACPI_STATUS setScreenBrightnessLevel(ACPI_HANDLE screenObj, int level);

};

#define MAX_IOAPICS 32
extern uint8_t processorID[MAX_IOAPICS];
extern uint8_t matchingAPICID[MAX_IOAPICS];
extern uint8_t processorDiscoveryNumber;
extern uint32_t ioapicGSIBase[MAX_IOAPICS];

//e.g. 0xFEC..., not 0xFEE... (use cpuGetAPICBase () instead)
extern uint32_t ioapicAddresses[MAX_IOAPICS];
extern uint8_t ioapicFoundInMADT[MAX_IOAPICS];		//the IDs of IOAPICs found on the system (using the MADT ACPI table)
extern uint8_t ioapicDiscoveryNumber;	//ioapicFoundInMADT[ioapicDiscoveryNumber++] = id;
extern uint8_t legacyIRQRemaps[16];

void scanMADT();

extern void (*systemShutdownFunction)();
extern void (*systemResetFunction)();
extern void (*systemSleepFunction)();

#endif