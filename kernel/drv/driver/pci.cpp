#pragma once

#include <drv/driver/pci.hpp>
#include <drv/unknown.hpp>
#include <krnl/hal.hpp>
#include <krnl/computer.hpp>
#include <hw/acpi.hpp>			// computer->root->nextPCIIRQAssignment

void PCIDriver::initialise()
{
	hw->registerPortRange(0xCF8, 8, 4);
	enumerateDevices();
	detect();
}

void PCIDriver::enumerateDevices()
{
	uint16_t headerType = getHeaderType(0, 0, 0);

	if ((headerType & 0x80) == 0) {
		// Single PCI host controller
		checkBus(0);
	} else {
		// Multiple PCI host controllers
		for (uint8_t function = 0; function < 8; function++) {
			if (getVendorID(0, 0, function) != 0xFFFF) break;
			checkBus(function);
		}
	}
}
	
void PCIDriver::detect()
{

}

void PCIDriver::deinitialise()
{

}

void PCIDriver::setPowerState(DevicePowerState state)
{

}

const char* PCIDriver::getHumanReadableName()
{
	return "PCI Bus";
}

uint8_t PCIDriver::readBAR8(uint32_t addr, int offset)
{
	if (addr & 1) {
		return inb((addr & ~3) + offset);
	} else {
		uint8_t* ptr = (uint8_t*) ((addr & ~0xF) + offset);
		return *ptr;
	}
}

uint16_t PCIDriver::readBAR16(uint32_t addr, int offset)
{
	if (addr & 1) {
		return inw((addr & ~3) + offset);
	} else {
		uint16_t* ptr = (uint16_t*) ((addr & ~0xF) + offset);
		return *ptr;
	}
}

uint32_t PCIDriver::readBAR32(uint32_t addr, int offset)
{
	if (addr & 1) {
		return inl((addr & ~3) + offset);
	} else {
		uint32_t* ptr = (uint32_t*) ((addr & ~0xF) + offset);
		return *ptr;
	}
}

void PCIDriver::writeBAR8(uint32_t addr, uint8_t val, int offset)
{
	if (addr & 1) {
		outb((addr & ~3) + offset, val);
	} else {
		uint8_t* ptr = (uint8_t*) ((addr & ~0xF) + offset);
		*ptr = val;
	}
}

void PCIDriver::writeBAR16(uint32_t addr, uint16_t val, int offset)
{
	if (addr & 1) {
		outw((addr & ~3) + offset, val);
	} else {
		uint16_t* ptr = (uint16_t*) ((addr & ~0xF) + offset);
		*ptr = val;
	}
}

void PCIDriver::writeBAR32(uint32_t addr, uint32_t val, int offset)
{
	if (addr & 1) {
		outl((addr & ~3) + offset, val);
	} else {
		uint32_t* ptr = (uint32_t*) ((addr & ~0xF) + offset);
		*ptr = val;
	}
}

uint16_t PCIDriver::readWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset)
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

void PCIDriver::writeWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset, uint16_t word)
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
		dword &= 0xFFFF;
		dword |= ((uint32_t) word) << 16;
	} else {
		dword &= 0xFFFF0000;
		dword |= word;
	}

	outl(0xCF8, address);
	outl(0xCFC, dword);
}

uint16_t PCIDriver::getVendorID(uint8_t bus, uint8_t slot, uint8_t function)
{
	return readWord(bus, slot, function, 0);
}

uint16_t PCIDriver::getHeaderType(uint8_t bus, uint8_t slot, uint8_t function)
{
	return readWord(bus, slot, function, 14) & 0xFF;			//if not 15, try 8
}

uint16_t PCIDriver::getClassCode(uint8_t bus, uint8_t slot, uint8_t function)
{
	uint8_t subClass = readWord(bus, slot, function, 10) & 0xFF;
	uint8_t classCode = readWord(bus, slot, function, 10) >> 8;

	return subClass | (classCode << 8);
}

uint8_t PCIDriver::getProgIF(uint8_t bus, uint8_t slot, uint8_t function)
{
	return readWord(bus, slot, function, 8) >> 8;
}

uint8_t PCIDriver::getRevisionID(uint8_t bus, uint8_t slot, uint8_t function)
{
	return readWord(bus, slot, function, 8) & 0xFF;
}

uint8_t PCIDriver::getInterruptNumber(uint8_t bus, uint8_t slot, uint8_t function)
{
	return readWord(bus, slot, function, 0x3C) & 0xFF;
}

uint8_t PCIDriver::getSecondaryBus(uint8_t bus, uint8_t slot, uint8_t function)
{
	return readWord(bus, slot, function, 0x18) >> 8;
}

uint32_t PCIDriver::getBARAddress(uint8_t barNo, uint8_t bus, uint8_t slot, uint8_t function)
{
	return (readWord(bus, slot, function, 0x12 + barNo * 4) << 16) | readWord(bus, slot, function, 0x10 + barNo * 4);
}

void PCIDriver::checkDevice(uint8_t bus, uint8_t device)
{
	uint8_t function = 0;
	uint16_t vendorID = getVendorID(bus, device, function);
	registerDevice(bus, device, function);

	uint8_t headerType = getHeaderType(bus, device, function);

	if ((headerType & 0x80) != 0) {
		/* It is a multi-function device, so check remaining functions */
		for (function = 1; function < 8; function++) {
			if (getVendorID(bus, device, function) != 0xFFFF) {
				registerDevice(bus, device, function);
			}
		}
	}
}

void PCIDriver::checkBus(uint8_t bus)
{
	for (uint8_t device = 0; device < 32; device++) {
		checkDevice(bus, device);
	}
}

void PCIDriver::registerDevice(uint8_t bus, uint8_t slot, uint8_t function)
{
	uint32_t headerType = (readWord(bus, slot, function, 0xC) >> 16) & 0xFF;

	if (headerType != 0) {
		return;
	}

	uint16_t classCode = getClassCode(bus, slot, function);
	uint8_t intno = getInterruptNumber(bus, slot, function);

	DevicePCIConnectionInfo info;

	uint32_t intPIN = readWord(bus, slot, function, 0x3C);
	intPIN >>= 8;
	intPIN &= 0xFF;

	info.intPIN = intPIN;

	if (computer->root->nextPCIIRQAssignment) {
		for (int i = 0; i < computer->root->nextPCIIRQAssignment; ++i) {
			if (slot == computer->root->pciIRQAssignments[i].slot && intPIN == computer->root->pciIRQAssignments[i].pin) {
				intno = computer->root->pciIRQAssignments[i].interrupt;
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
	info.deviceID = readWord(info.bus, info.slot, info.function, 2);
	info.progIF = getProgIF(bus, slot, function);
	info.vendorID = getVendorID(bus, slot, function);
	info.interrrupt = intno;

	UnknownHardware* deviceChild = new UnknownHardware(info);
	hw->addChild(deviceChild);
}


const char* PCI::lookupDeviceName(DevicePCIConnectionInfo info)
{
	return "PCI Device";
}
