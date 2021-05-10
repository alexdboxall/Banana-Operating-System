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
#include "thr/elf.hpp"
#include "core/physmgr.hpp"
#include "hw/acpi.hpp"
#include "hw/cpu.hpp"
#include "hw/ports.hpp"
#include "hw/bus/pci.hpp"
#include "hw/bus/isa.hpp"
#include "reg/registry.hpp"
#include "hw/diskctrl/ide.hpp"

uint8_t processorID[MAX_IOAPICS];
uint8_t matchingAPICID[MAX_IOAPICS];
uint8_t processorDiscoveryNumber = 0;
uint32_t ioapicGSIBase[MAX_IOAPICS];

//e.g. 0xFEC..., not 0xFEE... (use cpuGetAPICBase () instead)
uint32_t ioapicAddresses[MAX_IOAPICS];
uint8_t ioapicFoundInMADT[MAX_IOAPICS];		//the IDs of IOAPICs found on the system (using the MADT ACPI table)
uint8_t ioapicDiscoveryNumber = 0;	//ioapicFoundInMADT[ioapicDiscoveryNumber++] = id;
uint8_t legacyIRQRemaps[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
uint16_t legacyIRQFlags[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
uint32_t apicNMIInfo[MAX_IOAPICS];
int nextAPICNMI;

uint8_t* RSDPpointer;
uint8_t* RSDTpointer;
uint8_t* MADTpointer;
bool usingXSDT;

ACPITable acpiTables[64];
int nextACPITable = 0;

uint8_t* findRSDP()
{
	Krnl::setBootMessage("Finding RSDP...");

	if (!computer->features.hasACPI) {
		return 0;
	}

	if (Phys::usablePages < 2048) {
		computer->features.hasACPI = false;
		return 0;
	}
	Krnl::setBootMessage("Actually finding RSDP...");

	uint8_t* ptr = (uint8_t*) (size_t) (VIRT_LOW_MEGS + 0x0);

	for (; ptr < (uint8_t*) (size_t) (VIRT_LOW_MEGS + 0xFFFFF); ptr += 16) {
		if (!memcmp((char*) ptr, "RSD PTR ", 8)) {
			Krnl::setBootMessage("Found RSDP...");

			return ptr;
		}
	}
	Krnl::setBootMessage("Didn't find RSDP...");

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
	Krnl::setBootMessage("Finding RSDP A...");

	if (!computer->features.hasACPI) {
		return 0;
	}
	Krnl::setBootMessage("Finding RSDP B...");

	struct RSDPDescriptor20 a;
	memcpy(&a, ptr, sizeof(a));
	Krnl::setBootMessage("Finding RSDP C...");

	uint8_t rev = a.firstPart.Revision;
	uint8_t* ret = 0;
	Krnl::setBootMessage("Finding RSDP D...");

	struct XSDT* xsdt = (struct XSDT*) a.XsdtAddress;
	struct RSDT* rsdt = (struct RSDT*) a.firstPart.RsdtAddress;

	kprintf("PHYS: RSDT = 0x%X, XSDT = 0x%X\n", rsdt, xsdt);

	xsdt = (struct XSDT*) ((((size_t) xsdt) & 0xFFF) | Virt::getAKernelVAS()->mapRange(((size_t) xsdt) & ~0xFFF, Virt::allocateKernelVirtualPages(2), 2, PAGE_PRESENT | PAGE_SUPERVISOR));
	rsdt = (struct RSDT*) ((((size_t) rsdt) & 0xFFF) | Virt::getAKernelVAS()->mapRange(((size_t) rsdt) & ~0xFFF, Virt::allocateKernelVirtualPages(2), 2, PAGE_PRESENT | PAGE_SUPERVISOR));
	kprintf("VIRT: RSDT = 0x%X, XSDT = 0x%X\n", rsdt, xsdt);

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

	return 0;
}

extern uint32_t sysBootSettings;
void scanMADT()
{
	if (sysBootSettings & 1024) {
		computer->features.hasACPI = false;
	}
	if (!computer->features.hasACPI) {
		return;
	}

	RSDPpointer = findRSDP();
	if (!RSDPpointer) {
		computer->features.hasACPI = false;
		return;
	}
	Krnl::setBootMessage("Finding RSDT...");

	RSDTpointer = findRSDT(RSDPpointer);
	if (!RSDTpointer) {
		computer->features.hasACPI = false;
		return;
	}

	Krnl::setBootMessage("Loading other tables...");
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
			uint16_t flags = a->data[pointingTo] | (a->data[pointingTo + 1] << 8);
			pointingTo += 2;

			legacyIRQRemaps[irqSource] = globalSysInt;
			legacyIRQFlags[irqSource] = flags;

		} else if (type == 4) {
			uint32_t processorID = a->data[pointingTo++];
			uint32_t flags = a->data[pointingTo] | (a->data[pointingTo + 1] << 8);
			pointingTo += 2;
			uint32_t lintNum = a->data[pointingTo++];

			apicNMIInfo[nextAPICNMI++] = processorID | (flags << 8) | (lintNum << 24);

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

	if (nextPCIIRQAssignment == MAC_PCI_IRQ_ASSIGNMENTS) {
		panic("TOO MANY PCI IRQ ASSIGNMENTS");
	}
}

ACPI_STATUS ACPI::setScreenBrightnessLevel(ACPI_HANDLE screenObj, int level)
{
	return 0;
	//return acpicaSetBrightness(screenObj, level);
}

extern "C" size_t manualPCIProbe();

void ACPI::detectPCI()
{
	bool pciDetected = false;
	bool pciAccessMech1 = false;

	if (computer->features.hasACPI) {
		void* table = (void*) findDataTable(RSDTpointer, (char*) "MCFG");
		if (table) {
			pciDetected = true;
			pciAccessMech1 = true;
		}
	}

	uint8_t* biosPCIDetect = (uint8_t*) 0xC5F;
	if (*biosPCIDetect == 1) {
		pciDetected = true;
		pciAccessMech1 = true;

	} else if (*biosPCIDetect == 2) {
		pciDetected = true;
		if (pciAccessMech1) {
			panic("TODO: ASK USER: PCI MECHANSIM CONFLICT");
		}
	}

	if (!pciDetected) {
		size_t detected = manualPCIProbe();
		if (detected == 1) {
			pciDetected = true;
			pciAccessMech1 = true;

		} else if (detected == 2) {
			pciDetected = true;
			if (pciAccessMech1) {
				panic("TODO: ASK USER: PCI MECHANSIM CONFLICT");
			}
		}
	}

	if (pciDetected) {
		Krnl::setBootMessage("Scanning the PCI bus...");

		PCI* pci = new PCI();
		addChild(pci);
		pci->open(pciAccessMech1 ? 1 : 2, 0, nullptr);
	
	} else {
		kprintf("NO PCI...\n");
		Krnl::setBootMessage("Probing ISA ports...");

		IDE* dev = new IDE();
		addChild(dev);
		dev->detectionType = DetectionType::ISAProbe;
		dev->isaprobe.probeBaseA = 0x1F0;
		dev->isaprobe.probeBaseB = 0x170;
		dev->open(0, 0, nullptr);
	}
}

int ACPI::open(int mode, int, void*)
{
	detectPCI();

	Krnl::setBootMessage("Loading kernel symbol table...");
	Thr::loadKernelSymbolTable("C:/Banana/System/KERNEL32.EXE");

	Krnl::setBootMessage("Allocating the swapfile...");
	int megabytes = Reg::readIntWithDefault((char*) "system", (char*) "@memory:swapfile", 12);
	Virt::setupPageSwapping(megabytes);
	
	Krnl::setBootMessage("Loading device drivers...");
	Thr::executeDLL(Thr::loadDLL("C:/Banana/Drivers/bios.sys"), computer);

	//this should be moved to its own function
	{
		LinkedList<Device> driverless = getDevicesOfType(DeviceType::Driverless);
		while (!driverless.isEmpty()) {
			Device* element = driverless.getFirstElement();
			driverless.removeFirst();

			DriverlessDevice* dev = (DriverlessDevice*) element;

			PCIDeviceInfo pciInfo = dev->pci.info;

			char buffer[256];
			char* filename = PCI::pciDetailsToFilepath(pciInfo, buffer);
			if (filename) {
				File* f = new File(filename, kernelProcess);
				if (f->exists()) {
					Thr::executeDLL(Thr::loadDLL(filename), dev);
				}
				delete f;
			}
		}
	}

	Thr::executeDLL(Thr::loadDLL("C:/Banana/Drivers/common.sys"), computer);
	Thr::executeDLL(Thr::loadDLL("C:/Banana/Drivers/legacy.sys"), computer);

	if (computer->features.hasACPI) {
		Krnl::setBootMessage("Loading the ACPICA driver...");
		File* f = new File("C:/Banana/Drivers/acpica.sys", kernelProcess);
		if (f && f->exists()) {
			Thr::executeDLL(Thr::loadDLL("C:/Banana/Drivers/acpica.sys"), this);
		}
		if (f) {
			delete f;
		}

		SimpleBootFlagTable* sbf = (SimpleBootFlagTable*) findDataTable(RSDTpointer, (char*) "BOOT");
		if (sbf) {
			writeSimpleBootFlag(sbf);
		}
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