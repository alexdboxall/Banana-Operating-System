#include "core/common.hpp"
#include "hw/ports.hpp"
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

PCI::PCI() : Bus("PCI Bus")
{
	ports[noPorts].rangeStart = 0xCF8;
	ports[noPorts].rangeLength = 8;
	ports[noPorts++].width = 3;
}

int PCI::open(int a, int, void*)
{
	detect();
	return 0;
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

uint16_t PCI::pciReadWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset)
{
	uint32_t address;
	uint32_t lbus = bus;
	uint32_t lslot = slot;
	uint32_t lfunc = func;

	address = (uint32_t) ((lbus << 16) | (lslot << 11) |
		(lfunc << 8) | (offset & 0xfc) | ((uint32_t) 0x80000000));

	outl(0xCF8, address);
	return (uint16_t) ((inl(0xCFC) >> ((offset & 2) * 8)) & 0xFFFF);
}

void PCI::pciWriteWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset, uint16_t word)
{
	uint32_t address;
	uint32_t lbus = bus;
	uint32_t lslot = slot;
	uint32_t lfunc = func;

	address = (uint32_t) ((lbus << 16) | (lslot << 11) |
		(lfunc << 8) | (offset & 0xfc) | ((uint32_t) 0x80000000));

	outl(0xCF8, address);
	uint32_t dword = inl(0xCFC);
	if (offset & 0b10) {
		dword &= 0x00FFFF;
		dword |= ((uint32_t) word) << 16;
	} else {
		dword &= 0xFFFF0000;
		dword |= word;
	}

	outl(0xCF8, address);
	outl(0xCFC, dword);
}

int PCI::close(int a, int b, void* c)
{
	return 0;
}

void PCI::foundDevice(PCIDeviceInfo info)
{
	if (info.vendorID == 0xFFFF) return;

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
		SATABus* dev = new SATABus();
		addChild(dev);
		dev->preOpenPCI(info);
		dev->open(0, 0, nullptr);

	} else if (info.classCode == 1 && info.subClass == 1) {
		IDE* dev = new IDE();
		addChild(dev);
		dev->preOpenPCI(info);
		dev->open(0, 0, nullptr);
		
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