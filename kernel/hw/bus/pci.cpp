#include "core/common.hpp"
#include "fs/vfs.hpp"
#include "krnl/hal.hpp"
#include "hw/acpi.hpp"
#include "hw/bus/pci.hpp"
#include "hw/diskctrl/ide.hpp"
#include "hw/diskctrl/satabus.hpp"
#include <stdint.h>
#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

PCI* thePCI = nullptr;

PCI::PCI() : Bus("PCI Bus")
{
	thePCI = this;

	ports[noPorts].rangeStart = 0xCF8;
	ports[noPorts].rangeLength = 8;
	ports[noPorts++].width = 3;
}

int PCI::open(int _mechanism, int, void*)
{
	mechanism = _mechanism;
	detect();
	return 0;
}

uint8_t PCI::readBAR8(uint32_t addr, int offset)
{
	if (addr & 1) {
		return inb((addr & ~3) + offset);
	} else {
		uint8_t* ptr = (uint8_t*) ((addr & ~0xF) + offset);
		return *ptr;
	}
}

uint16_t PCI::readBAR16(uint32_t addr, int offset)
{
	if (addr & 1) {
		return inw((addr & ~3) + offset);
	} else {
		uint16_t* ptr = (uint16_t*) ((addr & ~0xF) + offset);
		return *ptr;
	}
}

uint32_t PCI::readBAR32(uint32_t addr, int offset)
{
	if (addr & 1) {
		return inl((addr & ~3) + offset);
	} else {
		uint32_t* ptr = (uint32_t*) ((addr & ~0xF) + offset);
		return *ptr;
	}
}

void PCI::writeBAR8(uint32_t addr, uint8_t val, int offset)
{
	if (addr & 1) {
		outb((addr & ~3) + offset, val);
	} else {
		uint8_t* ptr = (uint8_t*) ((addr & ~0xF) + offset);
		*ptr = val;
	}
}

void PCI::writeBAR16(uint32_t addr, uint16_t val, int offset)
{
	if (addr & 1) {
		outw((addr & ~3) + offset, val);
	} else {
		uint16_t* ptr = (uint16_t*) ((addr & ~0xF) + offset);
		*ptr = val;
	}
}

void PCI::writeBAR32(uint32_t addr, uint32_t val, int offset)
{
	if (addr & 1) {
		outl((addr & ~3) + offset, val);
	} else {
		uint32_t* ptr = (uint32_t*) ((addr & ~0xF) + offset);
		*ptr = val;
	}
}

uint16_t PCI::getVendorID(uint8_t bus, uint8_t slot, uint8_t function)
{
	return pciReadWord(bus, slot, function, 0);
}

uint16_t PCI::getHeaderType(uint8_t bus, uint8_t slot, uint8_t function)
{
	return pciReadWord(bus, slot, function, 14) & 0xFF;			//if not 15, try 8
}

uint16_t PCI::getClassCode(uint8_t bus, uint8_t slot, uint8_t function)
{
	uint8_t subClass = pciReadWord(bus, slot, function, 10) & 0xFF;
	uint8_t classCode = pciReadWord(bus, slot, function, 10) >> 8;

	return subClass | (classCode << 8);
}

uint8_t PCI::getProgIF(uint8_t bus, uint8_t slot, uint8_t function)
{
	return pciReadWord(bus, slot, function, 8) >> 8;
}

uint8_t PCI::getRevisionID(uint8_t bus, uint8_t slot, uint8_t function)
{
	return pciReadWord(bus, slot, function, 8) & 0xFF;
}

uint8_t PCI::getInterruptNumber(uint8_t bus, uint8_t slot, uint8_t function)
{
	return pciReadWord(bus, slot, function, 0x3C) & 0xFF;
}

uint8_t PCI::getSecondaryBus(uint8_t bus, uint8_t slot, uint8_t function)
{
	return pciReadWord(bus, slot, function, 0x18) >> 8;
}

uint32_t PCI::getBARAddress(uint8_t barNo, uint8_t bus, uint8_t slot, uint8_t function)
{
	return (pciReadWord(bus, slot, function, 0x12 + barNo * 4) << 16) | pciReadWord(bus, slot, function, 0x10 + barNo * 4);
}

uint16_t PCI::legacyMechanism(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset)
{
	if (func >= 8)	panic("TODO: HANDLE BETTER. PCI MECHANSIM #2 FAILURE 1");
	if (slot >= 16) panic("TODO: HANDLE BETTER. PCI MECHANSIM #2 FAILURE 2");

	//enable and specify function number
	outb(0xCF8, 0xF0 | (func << 1));

	//set the forwarding register
	outb(0xCFA, bus);

	return 0xC000 | (slot << 8) | (offset & ~3);
}

uint16_t PCI::pciReadWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset)
{
	if (mechanism == 1) {
		uint32_t address;
		uint32_t lbus = bus;
		uint32_t lslot = slot;
		uint32_t lfunc = func;

		address = (uint32_t) ((lbus << 16) | (lslot << 11) |
							  (lfunc << 8) | (offset & 0xfc) | ((uint32_t) 0x80000000));

		outl(0xCF8, address);
		return (uint16_t) ((inl(0xCFC) >> ((offset & 2) * 8)) & 0xFFFF);
	
	} else if (mechanism == 2) {
		uint16_t port = legacyMechanism(bus, slot, func, offset);
		return (uint16_t) ((inl(port) >> ((offset & 2) * 8)) & 0xFFFF);

	} else {
		panic("WTF?!");
		return 0;
	}
}

void PCI::pciWriteWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset, uint16_t word)
{
	if (mechanism == 1) {
		uint32_t address;
		uint32_t lbus = bus;
		uint32_t lslot = slot;
		uint32_t lfunc = func;

		address = (uint32_t) ((lbus << 16) | (lslot << 11) |
							  (lfunc << 8) | (offset & 0xfc) | ((uint32_t) 0x80000000));

		outl(0xCF8, address);
		uint32_t dword = inl(0xCFC);
		if (offset & 0b10) {
			dword &= 0xFFFF;
			dword |= ((uint32_t) word) << 16;
		} else {
			dword &= 0xFFFF0000;
			dword |= word;
		}

		outl(0xCF8, address);
		outl(0xCFC, dword);

	} else if (mechanism == 2) {
		uint16_t port = legacyMechanism(bus, slot, func, offset);
		uint32_t dword = inl(port);

		if (port & 0b10) {
			dword &= 0xFFFF;
			dword |= ((uint32_t) word) << 16;
		} else {
			dword &= 0xFFFF0000;
			dword |= word;
		}

		outl(port, dword);

	} else {
		panic("WTF?!");
	}
}

int PCI::close(int a, int b, void* c)
{
	return 0;
}


extern "C" uint32_t hexStrToInt(const char* string);
//extern "C" uint8_t hexCharToInt(char ch);

static inline __attribute__((always_inline)) uint8_t hexCharToInt(char c)
{
	asm volatile("aam $64; aad $57" : "=a" (c) : "a" (c));
	return c - 0x30;
}

char* PCI::pciDetailsToFilepath(PCIDeviceInfo pciInfo, char* outbuffer)
{
	KDEBUG_PAUSE("PCI::pciDetailsToFilepath");

	static bool loadedLookupFile = false;
	static char* lookupData = nullptr;
	static int lookupSize = 0;

	if (!loadedLookupFile) {
		KDEBUG_PAUSE("!loadedLookupFile");

		File* f = new File("C:/Banana/System/PCI.LST", kernelProcess);
		f->open(FileOpenMode::Read);

		uint64_t siz;
		bool dir;
		int br;

		f->stat(&siz, &dir);

		lookupData = (char*) malloc(siz + 1);
		lookupData[siz] = 0;
		f->read(siz, lookupData, &br);
		f->close();

		lookupSize = siz;
	}
	KDEBUG_PAUSE("ABCD");

	uint8_t classCode = 0;
	uint8_t subClass = 0;
	uint16_t vendor = 0;
	uint16_t device = 0;
	bool hasVendor = false;
	bool hasDevice = false;
	int i = 0;
	int j = 0;
	char current[256];
	KDEBUG_PAUSE("ABC123");

	while (i < lookupSize) {
		KDEBUG_PAUSE("ABC1234");

		classCode = hexCharToInt(lookupData[i++]);
		KDEBUG_PAUSE("ABC12345");

		classCode <<= 4;
		classCode |= hexCharToInt(lookupData[i++]);
		++i;

		subClass = hexCharToInt(lookupData[i++]);
		subClass <<= 4;
		subClass |= hexCharToInt(lookupData[i++]);
		++i;

		hasVendor = lookupData[i] != 'V';
		if (!hasVendor) {
			i += 4;
		} else {
			vendor = hexCharToInt(lookupData[i++]);
			vendor <<= 4;
			vendor |= hexCharToInt(lookupData[i++]);
			vendor <<= 4;
			vendor |= hexCharToInt(lookupData[i++]);
			vendor <<= 4;
			vendor |= hexCharToInt(lookupData[i++]);
		}
		++i;

		hasDevice = lookupData[i] != 'D';
		if (!hasDevice) {
			i += 4;
		} else {
			device = hexCharToInt(lookupData[i++]);
			device <<= 4;
			device |= hexCharToInt(lookupData[i++]);
			device <<= 4;
			device |= hexCharToInt(lookupData[i++]);
			device <<= 4;
			device |= hexCharToInt(lookupData[i++]);
		}
		++i;

		j = 0;
		while (1) {
			if (lookupData[i] == '\n' || i == lookupSize) {
				i += lookupData[i] == '\n';
				break;
			}

			current[j++] = lookupData[i++];
			current[j] = 0;
		}

		if (!hasVendor || vendor == pciInfo.vendorID) {
			if (!hasDevice || device == pciInfo.deviceID) {
				if (classCode == pciInfo.classCode && subClass == pciInfo.subClass) {
					strcpy(outbuffer, current);
					return outbuffer;
				}
			}
		}
	}
	
	*outbuffer = 0;
	return nullptr;
}

void PCI::foundDevice(PCIDeviceInfo info)
{
	if (info.vendorID == 0xFFFF) return;
	KDEBUG_PAUSE("FOUND A DEVICE!");

	if ((info.classCode == 0x06) && (info.subClass == 0x04)) {
		uint8_t secondaryBus = getSecondaryBus(info.bus, info.slot, info.function);
		checkBus(secondaryBus);
		return;
	}
	
	DeviceNode* n = this->children;
	while (n) {
		if (n->child && n->child->pci.info.vendorID == info.vendorID && n->child->pci.info.classCode == info.classCode && n->child->pci.info.bar[0] == info.bar[0] && n->child->pci.info.interrrupt == info.interrrupt) return;		//already done
		n = n->next;
	}

	//hardcode the boot related things in first
	if (info.classCode == 1 && info.subClass == 6) {
		KDEBUG_PAUSE("SATA?");
		SATABus* dev = new SATABus();
		KDEBUG_PAUSE("SATA? A");
		addChild(dev);
		KDEBUG_PAUSE("SATA? B");
		dev->preOpenPCI(info);
		KDEBUG_PAUSE("SATA? C");
		dev->open(0, 0, nullptr);
		KDEBUG_PAUSE("SATA? D");


	} else if (info.classCode == 1 && info.subClass == 1) {
		KDEBUG_PAUSE("IDE? A");
		IDE* dev = new IDE();
		KDEBUG_PAUSE("IDE? B");
		addChild(dev);
		KDEBUG_PAUSE("IDE? C");
		dev->preOpenPCI(info);
		KDEBUG_PAUSE("IDE? D");
		dev->open(0, 0, nullptr);
		KDEBUG_PAUSE("IDE? E");

	} else {
		//NOTE: It will be set up as a DriverlessDevice for now
		//		When we load a driver, we need to REMOVE THE DRIVELESS DEVICE from the tree
		//		and replace it with the drivered device
		DriverlessDevice* dev = new DriverlessDevice("PCI device without driver");
		addChild(dev);
		dev->preOpenPCI(info);
	}
}

void PCI::getDeviceData(uint8_t bus, uint8_t slot, uint8_t function)
{
	char q[32];
	strcpy(q, "000 00 00 GET DEVICE DATA.");
	q[0] = (bus / 100) % 10 + '0';
	q[1] = (bus / 10) % 10 + '0';
	q[2] = (bus / 1) % 10 + '0';
	q[4] = (slot / 10) % 10 + '0';
	q[5] = (slot / 1) % 10 + '0';
	q[7] = (function / 10) % 10 + '0';
	q[8] = (function / 1) % 10 + '0';
	KDEBUG_PAUSE(q);
		
	uint32_t headerType = pciReadWord(bus, slot, function, 0xC);
	headerType >>= 16;
	headerType &= 0xFF;

	if (headerType != 0) {
		return;
	}

	uint16_t classCode = getClassCode(bus, slot, function);
	uint8_t intno = getInterruptNumber(bus, slot, function);

	PCIDeviceInfo info;

	uint32_t intPIN = pciReadWord(bus, slot, function, 0x3C);
	intPIN >>= 8;
	intPIN &= 0xFF;

	info.intPIN = intPIN;

	if (computer->root->nextPCIIRQAssignment) {
		for (int i = 0; i < computer->root->nextPCIIRQAssignment; ++i) {

			char q[32];
			strcpy(q, "000 00 00 00 GET DEVICE DATA - IRQ ASSIGNMENT.");
			q[0] = (bus / 100) % 10 + '0';
			q[1] = (bus / 10) % 10 + '0';
			q[2] = (bus / 1) % 10 + '0';
			q[4] = (slot / 10) % 10 + '0';
			q[5] = (slot / 1) % 10 + '0';
			q[7] = (function / 10) % 10 + '0';
			q[8] = (function / 1) % 10 + '0';
			q[10] = (i / 10) % 10 + '0';
			q[11] = (i / 1) % 10 + '0';
			KDEBUG_PAUSE(q);

			if (slot == computer->root->pciIRQAssignments[i].slot && intPIN == computer->root->pciIRQAssignments[i].pin) {
				kprintf("TODO: PIC::getDeviceData check bus!\n");
				intno = computer->root->pciIRQAssignments[i].interrupt;
				kprintf("Slot %d, Pin %d -> IRQ %d\n", slot, intPIN, intno);
			}
		}
	}

	for (int i = 0; i < 6; ++i) {
		info.bar[i] = getBARAddress(i, bus, slot, function);
	}
	info.bus = bus;
	info.slot = slot;
	info.function = function;
	info.classCode = (classCode >> 8);
	info.subClass = (classCode & 0xFF);
	info.deviceID = pciReadWord(info.bus, info.slot, info.function, 2);
	info.progIF = getProgIF(bus, slot, function);
	info.vendorID = getVendorID(bus, slot, function);
	info.interrrupt = intno;

	foundDevice(info);
}

void PCI::checkDevice(uint8_t bus, uint8_t device)
{
	uint8_t function = 0;
	uint16_t vendorID = getVendorID(bus, device, function);
	getDeviceData(bus, device, function);

	uint8_t headerType = getHeaderType(bus, device, function);

	if ((headerType & 0x80) != 0) {
		/* It is a multi-function device, so check remaining functions */
		for (function = 1; function < 8; function++) {
			if (getVendorID(bus, device, function) != 0xFFFF) {
				getDeviceData(bus, device, function);
			}
		}
	}
}

void PCI::checkBus(uint8_t bus)
{
	for (uint8_t device = 0; device < 32; device++) {
		checkDevice(bus, device);
	}
}

void PCI::detect()
{
	uint8_t function;
	uint8_t bus;


	uint16_t headerType = getHeaderType(0, 0, 0);

	if ((headerType & 0x80) == 0) {
		// Single PCI host controller
		checkBus(0);
	} else {
		// Multiple PCI host controllers
		for (function = 0; function < 8; function++) {
			if (getVendorID(0, 0, function) != 0xFFFF) break;
			bus = function;
			checkBus(bus);
		}
	}
}