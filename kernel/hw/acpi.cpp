/*
Parts of this are based on Minux:

1
2 License
3
4 Copyright (c) 1987, 1997, 2006, Vrije Universiteit, Amsterdam,
5 The Netherlands All rights reserved. Redistribution and use of the MINIX 3
6 operating system in source and binary forms, with or without
7 modification, are permitted provided that the following conditions are
8 met:
9
10     * Redistributions of source code must retain the above copyright
11     notice, this list of conditions and the following disclaimer.
12
13     * Redistributions in binary form must reproduce the above copyright
14     notice, this list of conditions and the following disclaimer in the
15     documentation and/or other materials provided with the distribution.
16
17     * Neither the name of the Vrije Universiteit nor the names of the
18     software authors or contributors may be used to endorse or promote
19     products derived from this software without specific prior written
20     permission.
21
22     * Any deviations from these conditions require written permission
23     from the copyright holder in advance
24
25
26 Disclaimer
27
28  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS, AUTHORS, AND
29  CONTRIBUTORS ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
30  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
31  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
32  NO EVENT SHALL PRENTICE HALL OR ANY AUTHORS OR CONTRIBUTORS BE LIABLE
33  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
34  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
35  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
36  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
37  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
38  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
39  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
40
41
42 Aggregated Software
43
44 In addition to MINIX 3 itself, the distribution CD-ROM and this Website
45 contain additional software that is not part of MINIX 3 and is not
46 covered by this license. The licensing conditions for this additional
47 software are stated in the various packages. In particular, some of the
48 additional software falls under the GPL, and you must take care to
49 observe the conditions of the GPL with respect to this software. As
50 clearly stated in Article 2 of the GPL, when GPL and nonGPL software are
51 distributed together on the same medium, this aggregation does not cause
52 the license of either part to apply to the other part.
53
54
55 Acknowledgements
56
57 This product includes software developed by the University of
58 California, Berkeley and its contributors.
59
60 This product includes software developed by Softweyr LLC, the
61 University of California, Berkeley, and its contributors.
62 
*/

#include "core/common.hpp"
#include "core/virtmgr.hpp"
#include "core/elf.hpp"
#include "core/physmgr.hpp"
#include "hw/acpi.hpp"
#include "hw/cpu.hpp"
#include "hw/ports.hpp"
#include "hw/bus/pci.hpp"
#include "hw/bus/isa.hpp"

uint8_t processorID[MAX_IOAPICS];
uint8_t matchingAPICID[MAX_IOAPICS];
uint8_t processorDiscoveryNumber = 0;
uint32_t ioapicGSIBase[MAX_IOAPICS];

//e.g. 0xFEC..., not 0xFEE... (use cpuGetAPICBase () instead)
uint32_t ioapicAddresses[MAX_IOAPICS];
uint8_t ioapicFoundInMADT[MAX_IOAPICS];		//the IDs of IOAPICs found on the system (using the MADT ACPI table)
uint8_t ioapicDiscoveryNumber = 0;	//ioapicFoundInMADT[ioapicDiscoveryNumber++] = id;
uint8_t legacyIRQRemaps[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };

uint8_t* RSDPpointer;
uint8_t* RSDTpointer;
uint8_t* MADTpointer;
bool usingXSDT;

ACPITable acpiTables[64];
int nextACPITable = 0;

uint8_t* findRSDP()
{
	if (!computer->features.hasACPI) {
		return 0;
	}

	if (Phys::usablePages < 2048) {
		computer->features.hasACPI = false;
		return 0;
	}

	uint8_t* ptr = (uint8_t*) (size_t) (VIRT_LOW_MEGS + 0x0);

	for (; ptr < (uint8_t*) (size_t) (VIRT_LOW_MEGS + 0xFFFFF); ptr += 16) {
		if (!memcmp((char*) ptr, "RSD PTR ", 8)) {
			return ptr;
		}
	}

	return 0;
}

void loadACPITables(uint8_t* ptr)
{
	if (!computer->features.hasACPI) return;

	if (usingXSDT) {
		struct XSDT* xsdt = (struct XSDT*) ptr;
		int entries = (xsdt->h.Length - sizeof(xsdt->h)) / 8;

		for (int i = 0; i < entries; i++) {
			uint8_t* nptr = ptr + sizeof(struct ACPISDTHeader);
			uint64_t* wptr = (uint64_t*) nptr;
			wptr += i;

			acpiTables[nextACPITable++].location = (void*) (size_t) (*wptr);
		}

	} else {
		struct RSDT* rsdt = (struct RSDT*) ptr;
		int entries = (rsdt->h.Length - sizeof(rsdt->h)) / 4;

		for (int i = 0; i < entries; i++) {
			uint8_t* nptr = ptr + sizeof(struct ACPISDTHeader);
			uint32_t* wptr = (uint32_t*) nptr;
			wptr += i;

			acpiTables[nextACPITable++].location = (void*) (size_t) (*wptr);
		}
	}

	for (int i = 0; i < nextACPITable; ++i) {
		uint32_t* location = (uint32_t*) acpiTables[i].location;
		uint32_t* originalLocation = location;
		location = (uint32_t*) ((((size_t) location) & 0xFFF) | Virt::getAKernelVAS()->mapRange(((size_t) originalLocation) & ~0xFFF, Virt::allocateKernelVirtualPages(1), 1, PAGE_PRESENT | PAGE_SUPERVISOR));		

		memcpy((void*) acpiTables[i].signature, (const void*) location, 4);

		uint32_t len = location[1];

		int pages = (len + 4096) / 4096;
		uint32_t* oldLocation = location;
		location = (uint32_t*) ((((size_t) location) & 0xFFF) | Virt::getAKernelVAS()->mapRange(((size_t) originalLocation) & ~0xFFF, Virt::allocateKernelVirtualPages(pages), pages, PAGE_PRESENT | PAGE_SUPERVISOR));

		Virt::freeKernelVirtualPages((size_t) oldLocation);

		acpiTables[i].location = location;
	}
}

uint8_t* findRSDT(uint8_t* ptr)
{
	if (!computer->features.hasACPI) {
		return 0;
	}

	struct RSDPDescriptor20 a;
	memcpy(&a, ptr, sizeof(a));

	uint8_t rev = a.firstPart.Revision;
	uint8_t* ret = 0;

	struct XSDT* xsdt = (struct XSDT*) a.XsdtAddress;
	struct RSDT* rsdt = (struct RSDT*) a.firstPart.RsdtAddress;

	xsdt = (struct XSDT*) ((((size_t) xsdt) & 0xFFF) | Virt::getAKernelVAS()->mapRange(((size_t) xsdt) & ~0xFFF, Virt::allocateKernelVirtualPages(2), 2, PAGE_PRESENT | PAGE_SUPERVISOR));
	rsdt = (struct RSDT*) ((((size_t) rsdt) & 0xFFF) | Virt::getAKernelVAS()->mapRange(((size_t) rsdt) & ~0xFFF, Virt::allocateKernelVirtualPages(2), 2, PAGE_PRESENT | PAGE_SUPERVISOR));

	if (rev == 0) {
		usingXSDT = 0;
		ret = (uint8_t*) (size_t) rsdt;

	} else if (rev == 2) {
		usingXSDT = 1;
		ret = (uint8_t*) (size_t) xsdt;

	} else {
		return 0;
	}

	return ret;
}

uint8_t* findDataTable(uint8_t* ptr, char name[])
{
	if (!computer->features.hasACPI) return 0;

	for (int i = 0; i < nextACPITable; ++i) {
		if (!memcmp(acpiTables[i].signature, name, 4)) {
			return (uint8_t*) acpiTables[i].location;
		}
	}

	kprintf("NO DATA TABLE FOUND NAMED %s. %cSDT TABLE USED\n", name, usingXSDT ? 'X' : 'R');
	return 0;
}

void scanMADT()
{
	if (!computer->features.hasACPI) {
		return;
	}

	RSDPpointer = findRSDP();
	if (!RSDPpointer) {
		computer->features.hasACPI = false;
		return;
	}

	RSDTpointer = findRSDT(RSDPpointer);
	if (!RSDTpointer) {
		computer->features.hasACPI = false;
		return;
	}

	loadACPITables(RSDTpointer);

	struct MADTHeader* a = (struct MADTHeader*) findDataTable(RSDTpointer, (char*) "APIC");
	if (!a) {
		computer->features.hasAPIC = false;
		return;
	}

	unsigned pointingTo = 0;
	while (pointingTo <= a->Length && pointingTo < 500) {
		int original = pointingTo;
		uint8_t type = a->data[pointingTo++];
		uint8_t length = a->data[pointingTo++];

		if (length < 3) {
			break;
		}

		if (type == 0) {
			processorID[processorDiscoveryNumber] = a->data[pointingTo++];
			matchingAPICID[processorDiscoveryNumber++] = a->data[pointingTo++];
			pointingTo += 4;

		} else if (type == 1) {
			ioapicFoundInMADT[ioapicDiscoveryNumber] = a->data[pointingTo++];
			pointingTo++;
			ioapicAddresses[ioapicDiscoveryNumber] = a->data[pointingTo] | a->data[pointingTo + 1] << 8 | a->data[pointingTo + 2] << 16 | a->data[pointingTo + 3] << 24;
			pointingTo += 4;
			ioapicGSIBase[ioapicDiscoveryNumber] = a->data[pointingTo] | a->data[pointingTo + 1] << 8 | a->data[pointingTo + 2] << 16 | a->data[pointingTo + 3] << 24;
			pointingTo += 4;
			ioapicDiscoveryNumber++;

		} else if (type == 2) {
			uint8_t busSource = a->data[pointingTo++];
			uint8_t irqSource = a->data[pointingTo++];
			uint32_t globalSysInt = a->data[pointingTo] | a->data[pointingTo + 1] << 8 | a->data[pointingTo + 2] << 16 | a->data[pointingTo + 3] << 24;
			pointingTo += 4;
			pointingTo += 2;

			legacyIRQRemaps[irqSource] = globalSysInt;

		} else if (type == 4) {
			pointingTo += 4;

		} else if (type == 5) {
			pointingTo += 10;

		} else {

		}

		pointingTo = original + length;
	}
}

ACPI::ACPI(): Device("ACPI")
{
	scanMADT();
}

#ifndef JUMPER32
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

#endif

 
PCIIRQAssignments ACPI::getPCIIRQAssignment(uint8_t bus, uint16_t slot, uint8_t pin)
{
	PCIIRQAssignments result;
	bool gotRes = false;
	for (int i = 0; i < nextPCIIRQAssignment; ++i) {
		if (pciIRQAssignments[i].slot == slot && pciIRQAssignments[i].pin == pin) {
			if (gotRes) {
				if (pciIRQAssignments[i].rootBus != result.rootBus) {
					panic("MULTIPLE PCI BUSES, CANNOT GET IRQ ASSIGNMENT");
				}
				panic("ACPI IS SCREWY");
			}
			result = pciIRQAssignments[i];
			gotRes = true;
		}
	}

	return result;
}

void ACPI::registerPCIIRQAssignment(ACPI_HANDLE handle, uint16_t slot, uint8_t pin, uint8_t irq)
{
	pciIRQAssignments[nextPCIIRQAssignment].interrupt = irq;
	pciIRQAssignments[nextPCIIRQAssignment].slot = slot;
	pciIRQAssignments[nextPCIIRQAssignment].pin = pin + 1;
	pciIRQAssignments[nextPCIIRQAssignment].rootBus = handle;
	++nextPCIIRQAssignment;

	if (nextPCIIRQAssignment == 2048) {
		panic("TOO MANY PCI IRQ ASSIGNMENTS");
	}
}

ACPI_STATUS ACPI::setScreenBrightnessLevel(ACPI_HANDLE screenObj, int level)
{
	return acpicaSetBrightness(screenObj, level);
}




int ACPI::open(int mode, int, void*)
{
	if (!pciDetected) {
		pciDetected = true;
		/*outl(0xCF8, 0x80000000U);
		if (inl(0xCF8) == 0x80000000U) {
			pciDetected = true;
		}*/
	}

	if (pciDetected) {
		PCI* pci = new PCI();
		addChild(pci);
		pci->open(0, 0, nullptr);
		kprintf("PCI DONE.\n");
	}

	loadKernelSymbolTable("C:/Banana/System/KERNEL32.EXE");

	executeDLL(loadDLL("C:/Banana/Drivers/legacy.sys"), computer);


	if (computer->features.hasACPI) {
		kprintf("ACPICA init.\n");
		systemSleepFunction = acpicaSleep;
		systemResetFunction = acpicaReset;
		systemShutdownFunction = acpicaShutdown;

		acpi2 = true;

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

		void* ret;
		status = AcpiGetDevices(nullptr, (ACPI_WALK_CALLBACK) acpiWalkCallback, (void*) this, &ret);
		if (ACPI_FAILURE(status)) {
			panic("NAMESPACE COULD NOT BE WALKED FOR PCI DEVICES");
		}

		void* retVal;
		status = AcpiWalkNamespace(ACPI_TYPE_ANY, ACPI_ROOT_OBJECT, 8, (ACPI_WALK_CALLBACK) acpiWalkDescendingCallback, (ACPI_WALK_CALLBACK) acpiWalkAscendingCallback, (void*) this, &retVal);
	}

	SimpleBootFlagTable* sbf = (SimpleBootFlagTable*) findDataTable(RSDTpointer, (char*) "BOOT");
	if (sbf) {
		writeSimpleBootFlag(sbf);
	}

	return 0;
}

void ACPI::writeSimpleBootFlag(SimpleBootFlagTable* sbf)
{
	uint8_t offset = sbf->cmosOffset;
	uint8_t existing = computer->readCMOS(offset);
	computer->writeCMOS(offset, 0x1);					//plug-n-play, last boot completed properly, don't run diagnostics
}

void (*systemShutdownFunction)();
void (*systemResetFunction)();
void (*systemSleepFunction)();

void ACPI::sleep()
{
	if (systemSleepFunction) {
		systemSleepFunction();
	}
}

int ACPI::close(int mode, int b, void* c)
{
	if (b != 9999) {
		return 0;
	}

	if (mode == 0) {
		kprintf("ACPI::close\n");
		if (systemShutdownFunction) {
			systemShutdownFunction();
		}
		panic("You may now turn off your computer.");

		return -1;

	} else if (mode == 1) {
		if (systemResetFunction) {
			systemResetFunction();
		}
		uint8_t good = 0x02;
		while (good & 0x02) good = inb(0x64);
		outb(0x64, 0xFE);
	}

	return -1;
}