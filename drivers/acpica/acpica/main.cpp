#include <stdint.h>

#include "main.hpp"

#include "core/main.hpp"
#include "core/terminal.hpp"
#include "core/physmgr.hpp"
#include "hal/intctrl.hpp"
#include "hw/ports.hpp"
#include "hw/acpi.hpp"
#include "thr/prcssthr.hpp"
#include "reg/registry.hpp"
#include "fs/vfs.hpp"
#include "core/common.hpp"
#include "core/virtmgr.hpp"
#include "thr/elf.hpp"
#include "core/physmgr.hpp"
#include "hw/acpi.hpp"
#include "hw/cpu.hpp"
#include "hw/ports.hpp"
#include "hw/bus/pci.hpp"
#include "hw/bus/isa.hpp"

extern "C" {
	#include "libk/string.h"
}

void start(void* s);
void begin(void* s)
{
	kprintf("begin ACPICA.\n");
	start(s);
}

void acpiGlobalEventHandler(uint32_t type, ACPI_HANDLE device, uint32_t number, void* context)
{
	if (type == ACPI_EVENT_TYPE_FIXED && number == ACPI_EVENT_POWER_BUTTON) {
		computer->close(0, 0, nullptr);
		//handleShutdownButton();
	}
	if (type == ACPI_EVENT_TYPE_FIXED && number == ACPI_EVENT_SLEEP_BUTTON) {

		//handleSleepButton();
	}
}


char currentACPIWalkPath[256];

int wait = 0;
UINT32 acpiWalkDescendingCallback(ACPI_HANDLE object, UINT32 nestingLevel, void* context, void** returnValue)
{
	ACPI* acpi = (ACPI*) context;

	ACPI_OBJECT_TYPE type;
	AcpiGetType(object, &type);
	if (type == ACPI_TYPE_METHOD) {
		char name[7];
		memset(name, 0, 7);
		ACPI_BUFFER nameBuffer;
		nameBuffer.Length = ACPI_ALLOCATE_BUFFER;
		nameBuffer.Pointer = nullptr;

		AcpiGetName(object, ACPI_SINGLE_NAME, &nameBuffer);

		strcpy(name, (const char*) nameBuffer.Pointer);

		if (!strcmp(name, "_BCL")) {
			ACPI_HANDLE parent;
			AcpiGetParent(object, &parent);
			ACPI_OBJECT_TYPE ptype;
			AcpiGetType(parent, &ptype);

			if (ptype == ACPI_TYPE_DEVICE) {
				ACPI_OBJECT_LIST params;
				ACPI_STATUS status;
				ACPI_BUFFER retVal;
				retVal.Length = ACPI_ALLOCATE_BUFFER;
				retVal.Pointer = nullptr;

				params.Count = 0;
				params.Pointer = nullptr;

				status = AcpiEvaluateObject(parent, (ACPI_STRING) "_BCL", &params, &retVal);
				if (ACPI_SUCCESS(status)) {

					acpi->screenControlInfo[acpi->nextScreenControl].valid = true;
					acpi->screenControlInfo[acpi->nextScreenControl].hasBrightnessControl = true;
					acpi->screenControlInfo[acpi->nextScreenControl].numBrightnessLevels = 0;
					acpi->screenControlInfo[acpi->nextScreenControl].handle = parent;

					for (int i = 0; i < retVal.Length / (acpi->acpi2 ? 8 : 4); ++i) {
						uint64_t val = acpi->acpi2 ? *(((uint64_t*) retVal.Pointer) + i) : *(((uint32_t*) retVal.Pointer) + i);
						if (val >= 5 && val <= 100) {
							acpi->screenControlInfo[acpi->nextScreenControl].brightnessLevels[acpi->screenControlInfo[acpi->nextScreenControl].numBrightnessLevels++] = val;
						}
					}

					acpi->screenControlInfo[acpi->nextScreenControl].mainsBrightnessLevel = acpi->screenControlInfo[acpi->nextScreenControl].brightnessLevels[0];
					acpi->screenControlInfo[acpi->nextScreenControl].currentBrightnessLevel = acpi->screenControlInfo[acpi->nextScreenControl].mainsBrightnessLevel;
					acpi->screenControlInfo[acpi->nextScreenControl].batteryBrightnessLevel = acpi->screenControlInfo[acpi->nextScreenControl].brightnessLevels[1];

					ACPI_STATUS st = acpi->setScreenBrightnessLevel(parent, acpi->screenControlInfo[acpi->nextScreenControl].mainsBrightnessLevel);
					acpi->nextScreenControl++;
					if (acpi->nextScreenControl == 8) {
						panic("ACPI TOO MANY SCREENS!");
					}
				}

				return AE_OK;
			}
		}
		return AE_OK;

	} else if (type != ACPI_TYPE_DEVICE) {
		return AE_OK;

	}

	ACPI_BUFFER nameBuffer;
	nameBuffer.Length = ACPI_ALLOCATE_BUFFER;
	nameBuffer.Pointer = nullptr;
	AcpiGetName(object, ACPI_FULL_PATHNAME, &nameBuffer);
	memset(currentACPIWalkPath, 0, 256);
	memcpy(currentACPIWalkPath, (const void*) nameBuffer.Pointer, nameBuffer.Length);

	ACPI_DEVICE_INFO* deviceInfo;
	ACPI_STATUS status = AcpiGetObjectInfo(object, &deviceInfo);

	if (ACPI_FAILURE(status)) {
		return status;
	}

	//ACPI_PNP_DEVICE_ID hwId = deviceInfo->HardwareId;

	if (1) {
		kprintf("Getting current resources...\n");
		ACPI_BUFFER buffer;
		buffer.Length = ACPI_ALLOCATE_BUFFER;
		buffer.Pointer = nullptr;
		status = AcpiGetCurrentResources(object, &buffer);
		if (ACPI_SUCCESS(status)) {
			kprintf("Found resources...\n");
			ACPI_RESOURCE* resources = (ACPI_RESOURCE*) buffer.Pointer;
			for (;; resources = (ACPI_RESOURCE*) (((uint8_t*) resources) + resources->Length)) {
				kprintf("RSC (Type 0x%X, len = 0x%X)\n", resources->Type, resources->Length);
				if (resources->Type == ACPI_RESOURCE_TYPE_END_TAG) {
					kprintf("End tag.\n");
					break;

				} else if (resources->Type == ACPI_RESOURCE_TYPE_IO) {
					ACPI_RESOURCE_IO* io = (ACPI_RESOURCE_IO*) &resources->Data.Io;
					kprintf("IO PORT RANGE FOR %s\n", currentACPIWalkPath);
					kprintf("0x%X -> 0x%X. Align 0x%X, length 0x%X\n", io->Minimum, io->Maximum, io->Alignment, io->AddressLength);

				} else if (resources->Type == ACPI_RESOURCE_TYPE_FIXED_IO) {
					ACPI_RESOURCE_FIXED_IO* io = (ACPI_RESOURCE_FIXED_IO*) &resources->Data.FixedIo;
					kprintf("FIXED IO PORT RANGE FOR %s\n", currentACPIWalkPath);
					kprintf("0x%X. len 0x%X\n", io->Address, io->AddressLength);

				} else if (resources->Type == ACPI_RESOURCE_TYPE_MEMORY32) {
					kprintf("mem32\n");

				} else if (resources->Type == ACPI_RESOURCE_TYPE_FIXED_MEMORY32) {
					kprintf("fixed mem32\n");

				} else if (resources->Type == ACPI_RESOURCE_TYPE_MEMORY24) {
					kprintf("mem24\n");

				} else if (resources->Type == ACPI_RESOURCE_TYPE_ADDRESS16) {
					kprintf("addr16\n");

				} else if (resources->Type == ACPI_RESOURCE_TYPE_ADDRESS32) {
					kprintf("addr32\n");

				} else if (resources->Type == ACPI_RESOURCE_TYPE_ADDRESS64) {
					kprintf("addr64\n");

				} else if (resources->Type == ACPI_RESOURCE_TYPE_EXTENDED_ADDRESS64) {
					kprintf("ext. addr64\n");

				} else if (resources->Type == ACPI_RESOURCE_TYPE_DMA) {
					kprintf("DMA!\n");

				} else if (resources->Type == ACPI_RESOURCE_TYPE_FIXED_DMA) {
					kprintf("FIXED DMA!\n");

				}
			}
		} else {
			kprintf("Failure: %d\n", status);

		}
	}

	return AE_OK;
}

UINT32 acpiWalkAscendingCallback(ACPI_HANDLE object, UINT32 nestingLevel, void* context, void** returnValue)
{
	return AE_OK;
}

struct ACPIDynamicIRQCallbackContext
{
	ACPI* acpi;
	ACPI_HANDLE pciRootBus;
	ACPI_PCI_ROUTING_TABLE* table;
};

UINT32 acpiDynamicIrqCallback(ACPI_RESOURCE* resource, void* context)
{
	kprintf("dynamic callback.\n");

	ACPIDynamicIRQCallbackContext* ctxt = (ACPIDynamicIRQCallbackContext*) context;

	ACPI* acpi = ctxt->acpi;
	ACPI_HANDLE pciRootBus = ctxt->pciRootBus;
	ACPI_PCI_ROUTING_TABLE* table = ctxt->table;

	if (resource->Type == ACPI_RESOURCE_TYPE_IRQ) {
		ACPI_RESOURCE_IRQ* irq = &resource->Data.Irq;
		//panic("DEBUG. acpica.sys acpiDynamicIrqCallback");
		//lockScheduler();
		acpi->registerPCIIRQAssignment(pciRootBus, table->Address >> 16, table->Pin, irq->Interrupts[table->SourceIndex]);
		//unlockScheduler();

	} else if (resource->Type == ACPI_RESOURCE_TYPE_EXTENDED_IRQ) {
		ACPI_RESOURCE_EXTENDED_IRQ* xirq = &resource->Data.ExtendedIrq;

		auto a = pciRootBus;
		auto b = table->Address >> 16;
		auto c = table->Pin;
		auto d = xirq->Interrupts[table->SourceIndex];
		acpi->registerPCIIRQAssignment(a, b, c, d);
	}

	return AE_OK;
}

// http://cinnabar.sosdg.org/~qiyong/qxr/minix3/source/minix/drivers/power/acpi/pci.c#L147

/*
The process is essentially:

1) Initialize the namespace (\\_SB_._INI) followed by all devices whose _STA method reports they are present and/or functional.

2) Execute \\_PIC(1) to inform ACPI that you are using the IOAPIC (this is required otherwise it will probably give you the wrong IRQ routing tables).

3) Find the PCI root bridge (_HID = EisaId(PNP0A03))

4) Execute its _PRT method. This will return a Package object (which is ACPI-speak for an array) containing many other package objects. Iterate through each of them and the first entry is the PCI device number in the format (dev_num << 16) | 0xffff. The second is the PCI pin number (1 = INTA#, 2 = INTB#, 3 = INTC#, 4 = INTD#). You then need to match them up with what you found during PCI enumeration (e.g. if device 5 has the interrupt pin entry of its PCI configuration space being 3, you'd look for an entry in the _PRT response with the first item being 0x0005ffff and the second being 0x3). Look up the _PRT method in the spec for further info.

5) Once you've found the correct method, then examine the third entry of the _PRT response for that device:
5a) If it is an Integer with value Zero, then the 4th entry is an Integer whose value is the Global System Interrupt that device uses. Once you know this, you find which IOAPIC it points to and the pin on that IOAPIC. To do this, iterate through the MADT table looking for an IOAPIC with its gsibase field being less than and within 24 of the value you're looking for. Typically you have only one IOAPIC with gsibase being zero. Thus a GSI of 16 means pin 16 on IOAPIC 1.

5b) If it is a string, it is the name of another object in the namespace (a PCI IRQ Link object, e.g. \\_SB_\LNKA). You need to execute the _CRS method of this object to find out what interrupt it uses. You will want to read the spec to see the layout of the response. This will typically give you an ISA IRQ to use, and you will have to parse MADT again looking for InterruptSourceOverride structures that will convert this ISA IRQ to a GSI. If there is none, then GSI = ISA IRQ.

6) Choose a free interrupt vector in a particular CPU's IDT and program the handler into it.

7) Program the appropriate pin on the appropriate IOAPIC to route to the particular vector on the particular processor.
*/

UINT32 acpiWalkCallback(ACPI_HANDLE object, UINT32 nestingLevel, void* context, void** returnValue)
{
	ACPI* acpi = (ACPI*) context;

	ACPI_DEVICE_INFO* info;
	ACPI_STATUS status = AcpiGetObjectInfo(object, &info);

	if (ACPI_FAILURE(status)) {
		kprintf("[acpiWalkCallback] AcpiGetObjectInfo 0x%X\n", status);
		return AE_OK;

		panic("[acpiWalkCallback] AcpiGetObjectInfo");
	}

	char name[5];
	memcpy((void*) name, &info->Name, 4);
	name[4] = 0;
	kprintf("acpiWalkCallback name = %s\n", name);

	if ((info->Flags & ACPI_PCI_ROOT_BRIDGE) && name[0] == 'P') {
		acpi->pciDetected = true;
		
		ACPI_BUFFER prtbuf;
		prtbuf.Length = ACPI_ALLOCATE_BUFFER;
		prtbuf.Pointer = nullptr;

		status = AcpiGetIrqRoutingTable(object, &prtbuf);

		if (ACPI_FAILURE(status)) {
			kprintf("[acpiWalkCallback] AcpiGetIrqRoutingTable 0x%X\n", status);
			while (1);
			return AE_OK;

			panic("[acpiWalkCallback] AcpiGetIrqRoutingTable");
		}

		kprintf("Got PCI routing table!\n");

		ACPI_PCI_ROUTING_TABLE* table = (ACPI_PCI_ROUTING_TABLE*) prtbuf.Pointer;
		for (; table->Length; table = (ACPI_PCI_ROUTING_TABLE*) (((uint8_t*) table) + table->Length)) {
			if (table->Source[0] == 0) {
				kprintf("table->Source[0] == 0\n");
				acpi->registerPCIIRQAssignment(object, table->Address >> 16, table->Pin + 1, table->SourceIndex);

			} else {
				kprintf("table = 0x%X, table->Source = 0x%X\n", table, table->Source);
				kprintf("table->Source = %s\n", table->Source);

				ACPI_HANDLE link;
				status = AcpiGetHandle(object, table->Source, &link);
				if (ACPI_FAILURE(status)) {
					panic("[acpiWalkCallback] AcpiGetHandle");
				}

				kprintf("link = 0x%X\n", link);

				ACPIDynamicIRQCallbackContext ctxt;
				ctxt.acpi = acpi;
				ctxt.pciRootBus = object;
				ctxt.table = table;

				status = AcpiWalkResources(link, (char*) "_CRS", acpiDynamicIrqCallback, (void*) &ctxt);
				if (ACPI_FAILURE(status)) {
					kprintf("[acpiWalkCallback] AcpiWalkResources (status = 0x%X)\n", (int) status);
				} else {
					kprintf("Not a failure!\n");
				}
			}
		}
	}

	return AE_OK;
}

ACPI_STATUS acpicaSetBrightness(ACPI_HANDLE screenObj, int level)
{

	ACPI_STATUS status;
	ACPI_OBJECT_LIST params;
	ACPI_OBJECT arg[1];

	params.Count = 1;
	params.Pointer = arg;

	arg[0].Type = ACPI_TYPE_INTEGER;
	arg[0].Integer.Value = level;

	status = AcpiEvaluateObject(screenObj, (ACPI_STRING) "_BCM", &params, NULL);

	return status;
}

void acpicaSleep()
{
	//go to sleep
	AcpiEnterSleepStatePrep(2);
	AcpiEnterSleepState(2);

	//the computer sleeps here (execution stops here until awoken)
	AcpiLeaveSleepStatePrep(2);
	AcpiLeaveSleepState(2);
}

void acpicaShutdown()
{
	ACPI_STATUS a = AcpiEnterSleepStatePrep(5);
	if (a != AE_OK) {
		return;
	}
	asm volatile ("cli");
	a = AcpiEnterSleepState(5);
}

void acpicaReset()
{
	AcpiReset();
}

void start(void* xxa)
{
	ACPI* ths = (ACPI*) xxa;

	kprintf("ACPICA init.\n");
	systemSleepFunction = acpicaSleep;
	systemResetFunction = acpicaReset;
	systemShutdownFunction = acpicaShutdown;

	ths->acpi2 = true;
	ths->nextPCIIRQAssignment = 0;
	ths->nextScreenControl = 0;

	ACPI_STATUS a = AcpiInitializeSubsystem();
	if (ACPI_FAILURE(a)) panic("FAILURE AcpiInitializeSubsystem");

	a = AcpiInitializeTables(nullptr, 16, true);
	if (ACPI_FAILURE(a)) panic("FAILURE AcpiInitializeTables");

	a = AcpiInstallAddressSpaceHandler(ACPI_ROOT_OBJECT,
									   ACPI_ADR_SPACE_SYSTEM_MEMORY, ACPI_DEFAULT_HANDLER, NULL, NULL);
	if (ACPI_FAILURE(a)) panic("FAILURE AcpiInstallAddressSpaceHandler ACPI_ADR_SPACE_SYSTEM_MEMORY");

	a = AcpiInstallAddressSpaceHandler(ACPI_ROOT_OBJECT,
									   ACPI_ADR_SPACE_SYSTEM_IO, ACPI_DEFAULT_HANDLER, NULL, NULL);
	if (ACPI_FAILURE(a)) panic("FAILURE AcpiInstallAddressSpaceHandler ACPI_ADR_SPACE_SYSTEM_IO");

	a = AcpiInstallAddressSpaceHandler(ACPI_ROOT_OBJECT,
									   ACPI_ADR_SPACE_PCI_CONFIG, ACPI_DEFAULT_HANDLER, NULL, NULL);
	if (ACPI_FAILURE(a)) panic("FAILURE AcpiInstallAddressSpaceHandler ACPI_ADR_SPACE_PCI_CONFIG");

	a = AcpiLoadTables();
	if (ACPI_FAILURE(a)) panic("FAILURE AcpiLoadTables");

	a = AcpiEnableSubsystem(ACPI_FULL_INITIALIZATION);
	if (ACPI_FAILURE(a)) panic("FAILURE AcpiEnableSubsystem");

	a = AcpiInitializeObjects(ACPI_FULL_INITIALIZATION);
	if (ACPI_FAILURE(a)) panic("FAILURE AcpiInitializeObjects");

	ACPI_STATUS status;
	if (computer->features.hasAPIC) {
		ACPI_OBJECT_LIST params;
		ACPI_OBJECT arg;

		params.Count = 1;
		params.Pointer = &arg;

		arg.Type = ACPI_TYPE_INTEGER;
		arg.Integer.Value = CPU::current()->intCtrl->getName()[0] == 'A';
		kprintf("value = %d\n", arg.Integer.Value);

		status = AcpiEvaluateObject(NULL, (ACPI_STRING) "\\_PIC", &params, NULL);
		if (ACPI_FAILURE(status) && status != AE_NOT_FOUND) {
			kprintf("status = 0x%X\n", status);
			panic("ACPI failure AcpiEvaluateObject(_PIC)");

		} else if (status == AE_NOT_FOUND) {
			kprintf("_PIC method not found.\n");

		} else {
			kprintf("_PIC method success.\n");
		}
	} else {
		kprintf("Computer not using APIC.\n");
	}

	AcpiWriteBitRegister(ACPI_BITREG_SCI_ENABLE, 1);

	a = AcpiInstallGlobalEventHandler(acpiGlobalEventHandler, nullptr);
	if (a != AE_OK) panic("FAILURE AcpiInstallGlobalEventHandler");

	a = AcpiEnableEvent(ACPI_EVENT_SLEEP_BUTTON, 0);
	a = AcpiEnableEvent(ACPI_EVENT_POWER_BUTTON, 0);

	void* ret;
	status = AcpiGetDevices(nullptr, (ACPI_WALK_CALLBACK) acpiWalkCallback, (void*) ths, &ret);
	if (ACPI_FAILURE(status)) {
		panic("NAMESPACE COULD NOT BE WALKED FOR PCI DEVICES");
	}

	void* retVal;
	status = AcpiWalkNamespace(ACPI_TYPE_ANY, ACPI_ROOT_OBJECT, 8, (ACPI_WALK_CALLBACK) acpiWalkDescendingCallback, (ACPI_WALK_CALLBACK) acpiWalkAscendingCallback, (void*) ths, &retVal);
}
