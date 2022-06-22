#pragma once

#include <drv/driver/pci.hpp>
#include <drv/unknown.hpp>
#include <krnl/hal.hpp>
#include <krnl/computer.hpp>
#include <hw/acpi.hpp>			// computer->root->nextPCIIRQAssignment
#include <dbg/kconsole.hpp>

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
	for (const auto& child : hw->children) {
		
	}
}

void PCIDriver::deinitialise()
{

}

void PCIDriver::setPowerState(DevicePowerState state)
{

}

const char* PCIDriver::getHumanReadableName()
{
	return PCI_DRIVER_NAME;
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

	uint16_t vendorID = getVendorID(bus, slot, function);
	if (vendorID == 0xFFFF) {
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
	info.vendorID = vendorID;
	info.interrrupt = intno;

	UnknownHardware* deviceChild = new UnknownHardware(info);
	hw->addChild(deviceChild);
}


const char* PCIDriver::lookupDeviceName(DevicePCIConnectionInfo info)
{
	switch (info.classCode) {
	case 0x0:
	{
		switch (info.subClass) {
		case 0x1: return "PCI VGA-Compatible Video Device";
		default: return "PCI Video Device";
		}
	}
	case 0x1:
	{
		switch (info.subClass) {
		case 0x0:
		case 0x7: 
			return "PCI SCSI Controller";
		case 0x1: return "PCI IDE Controller";
		case 0x2: return "PCI Floppy Disk Controller";
		case 0x3: return "PCI IPI Bus Controller";
		case 0x4: return "PCI RAID Controller";
		case 0x5: return "PCI ATA Controller";
		case 0x6: return "PCI SATA Controller";
		case 0x8: return "PCI Non-Volatile Memory Controller";
		default: return "PCI Mass Storage Device";
		}
	}
	case 0x2:
	{
		switch (info.subClass) {
		case 0x0: return "PCI Ethernet Controller";
		default: return "PCI Network Controller";
		}
	}
	case 0x3:
	{
		switch (info.subClass) {
		case 0x0: return "PCI VGA-Compatible Video Controller";
		case 0x1: return "PCI XGA Controller";
		case 0x2: return "PCI 3D Controller";
		default: return "PCI Display Controller";
		}
	}
	case 0x4:
	{
		switch (info.subClass) {
		case 0x0: return "PCI Video Controller";
		case 0x1: return "PCI Audio Controller";
		case 0x2: return "PCI Telephony Device";
		case 0x3: return "PCI Audio Device";
		default: return "PCI Multimedia Controller";
		}
	}
	case 0x5:
	{
		switch (info.subClass) {
		case 0x0: return "PCI RAM Controller";
		case 0x1: return "PCI Flash Memory Controller";
		default: return "PCI Memory Controller";
		}
	}
	case 0x6:
	{
		switch (info.subClass) {
		case 0x0: return "PCI Host Bridge";
		case 0x1: return "PCI ISA Bridge";
		case 0x2: return "PCI EISA Bridge";
		case 0x3: return "PCI MCA Bridge";
		case 0x4:
		case 0x9:
			return "PCI-to-PCI Bridge";
		case 0x5: return "PCMCIA Bridge";
		case 0x6: return "NuBus Bridge";
		case 0x7: return "CardBus Bridge";
		case 0x8: return "RACEway Bridge";
		case 0xA: return "InfiniBand-to-PCI Host Bridge";
		default: return "Other PCI Bridge";
		}
	}
	case 0x7:
	{
		switch (info.subClass) {
		case 0x0: return "PCI Serial Controller";
		case 0x1: return "PCI Parallel Controller";
		case 0x2: return "PCI Multiport Serial Controller";
		case 0x3: return "PCI Modem";
		case 0x4: return "PCI IEEE 488 Controller";
		case 0x5: return "PCI Smart Card Controller";
		default: return "PCI Communication Controller";
		}
	}
	case 0x8:
	{
		switch (info.subClass) {
		case 0x0: return "PCI Programmable Interrupt Controller";
		case 0x1: return "PCI DMA Controller";
		case 0x2: return "PCI Timer";
		case 0x3: return "PCI Real Time Clock Controller";
		case 0x4: return "PCI Hot-Plug Controller";
		case 0x5: return "PCI SD Host Controller";
		case 0x6: return "PCI IOMMU";
		default: return "PCI System Peripheral";
		}
	}
	case 0x9:
	{
		switch (info.subClass) {
		case 0x0: return "PCI Keyboard Controller";
		case 0x1: return "PCI Digitizer Pen";
		case 0x2: return "PCI Mouse Controller";
		case 0x3: return "PCI Scanners Controller";
		case 0x4: return "PCI Gameports Controller";
		default: return "PCI Input Device Controller";
		}
	}
	case 0xA:
		return "PCI Docking Station";
	case 0xB:
	{
		switch (info.subClass) {
		case 0x0: return "i386 Processor";
		case 0x1: return "i486 Processor";
		case 0x2: return "Pentium Processor";
		case 0x3: return "Pentium Pro Processor";
		case 0x10: return "Alpha Processor";
		case 0x20: return "PowerPC Processor";
		case 0x30: return "MIPS Processor";
		case 0x40: return "Co-Processor";
		default: return "Other Processor";
		}
	}
	case 0xC:
	{
		switch (info.subClass) {
		case 0x0: return "PCI FireWire Controller";
		case 0x1: return "PCI ACCESS Bus Controller";
		case 0x2: return "PCI SSA";
		case 0x3: return "PCI USB Controller";
		case 0x4: return "PCI Fibre Controller";
		case 0x5: return "PCI SMBus Controller";
		case 0x6: return "PCI InfiniBand Controller";
		case 0x7: return "PCI IPMI Interface";
		case 0x8: return "PCI SERCOS Interface";
		case 0x9: return "PCI CANbus Interface";
		default: return "PCI Serial Bus Controller";
		}
	}
	case 0xD:
	{
		switch (info.subClass) {
		case 0x0: return "PCI iRDA Compatible Controller";
		case 0x1: return "PCI IR Controller";
		case 0x10: return "PCI RF Controller";
		case 0x11: return "PCI Bluetooth Controller";
		case 0x12: return "PCI Broadband Controller";
		case 0x20: return "PCI Ethernet 802.1a Controller";
		case 0x21: return "PCI Ethernet 802.2a Controller";
		default: return "PCI Wireless Controller";
		}
	}
	case 0xE:
		return "PCI Intelligent Controller";
	case 0xF:
		return "PCI Satellite Communication Controller";
	case 0x10:
		return "PCI Encryption Controller";
	case 0x11:
		return "PCI Signal Processing Controller";
	case 0x12:
		return "PCI Processing Accelerator";
	case 0x13:
		return "PCI Non-Essential Instrumentation";
	case 0x40:
		return "Co-Processor";
	default:
		kprintf("Unknown PCI device: %d, %d, %d\n", info.classCode, info.subClass, info.progIF);
		return "PCI Device";
	}
}
