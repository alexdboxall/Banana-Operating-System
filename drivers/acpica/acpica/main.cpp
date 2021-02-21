#include <stdint.h>

#include "main.hpp"

#include "core/main.hpp"
#include "core/terminal.hpp"
#include "core/physmgr.hpp"
#include "hal/intctrl.hpp"
#include "hw/ports.hpp"
#include "hw/acpi.hpp"
#include "core/prcssthr.hpp"
#include "registry/registry.hpp"
#include "fs/vfs.hpp"
#include "core/common.hpp"
#include "core/virtmgr.hpp"
#include "core/elf.hpp"
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
UINT32 acpiWalkDescendingCallback23456789(ACPI_HANDLE object, UINT32 nestingLevel, void* context, void** returnValue)
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
	ACPIDynamicIRQCallbackContext* ctxt = (ACPIDynamicIRQCallbackContext*) context;

	ACPI* acpi = ctxt->acpi;
	ACPI_HANDLE pciRootBus = ctxt->pciRootBus;
	ACPI_PCI_ROUTING_TABLE* table = ctxt->table;

	if (resource->Type == ACPI_RESOURCE_TYPE_IRQ) {
		ACPI_RESOURCE_IRQ* irq = &resource->Data.Irq;
		acpi->registerPCIIRQAssignment(pciRootBus, table->Address >> 16, table->Pin, irq->Interrupts[table->SourceIndex]);

	} else if (resource->Type == ACPI_RESOURCE_TYPE_EXTENDED_IRQ) {
		ACPI_RESOURCE_EXTENDED_IRQ* xirq = &resource->Data.ExtendedIrq;
		acpi->registerPCIIRQAssignment(pciRootBus, table->Address >> 16, table->Pin, xirq->Interrupts[table->SourceIndex]);
	}

	return AE_OK;
}

//http://cinnabar.sosdg.org/~qiyong/qxr/minix3/source/minix/drivers/power/acpi/pci.c#L147

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
				acpi->registerPCIIRQAssignment(object, table->Address >> 16, table->Pin + 1, table->SourceIndex);

			} else {
				ACPI_HANDLE link;
				status = AcpiGetHandle(object, table->Source, &link);
				if (ACPI_FAILURE(status)) {
					panic("[acpiWalkCallback] AcpiGetHandle");
				}

				ACPIDynamicIRQCallbackContext ctxt;
				ctxt.acpi = acpi;
				ctxt.pciRootBus = object;
				ctxt.table = table;

				status = AcpiWalkResources(link, (char*) "_CRS", acpiDynamicIrqCallback, (void*) &ctxt);
				if (ACPI_FAILURE(status)) {
					panic("[acpiWalkCallback] AcpiWalkResources");
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
		ACPI_OBJECT arg[1];

		params.Count = 1;
		params.Pointer = arg;

		arg[0].Type = ACPI_TYPE_INTEGER;
		arg[0].Integer.Value = thisCPU()->intCtrl->getName()[0] == 'A';

		status = AcpiEvaluateObject(NULL, (ACPI_STRING) "\\_PIC", &params, NULL);
		if (ACPI_FAILURE(status) && status != AE_NOT_FOUND) {
			kprintf("status = 0x%X\n", status);
			panic("ACPI failure AcpiEvaluateObject(_PIC)");
		}
	}


	AcpiWriteBitRegister(ACPI_BITREG_SCI_ENABLE, 1);

	a = AcpiInstallGlobalEventHandler(acpiGlobalEventHandler, nullptr);
	if (a != AE_OK) panic("FAILURE AcpiInstallGlobalEventHandler");

	a = AcpiEnableEvent(ACPI_EVENT_SLEEP_BUTTON, 0);
	a = AcpiEnableEvent(ACPI_EVENT_POWER_BUTTON, 0);

	return;

	/*void* ret;
	status = AcpiGetDevices(nullptr, (ACPI_WALK_CALLBACK) acpiWalkCallback, (void*) ths, &ret);
	if (ACPI_FAILURE(status)) {
		panic("NAMESPACE COULD NOT BE WALKED FOR PCI DEVICES");
	}

	void* retVal;
	status = AcpiWalkNamespace(ACPI_TYPE_ANY, ACPI_ROOT_OBJECT, 8, (ACPI_WALK_CALLBACK) acpiWalkDescendingCallback, (ACPI_WALK_CALLBACK) acpiWalkAscendingCallback, (void*) ths, &retVal);*/
}
