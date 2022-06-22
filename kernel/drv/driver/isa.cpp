#pragma once

#include <drv/driver/isa.hpp>
#include <drv/driver/uart16550.hpp>
#include <drv/driver/dma8237.hpp>
#include <krnl/hal.hpp>

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

void ISADriver::detectCOMPort(uint16_t base)
{
	// if already assigned, there's probably no serial port there
	if (KeIsPortInUse(base, 8)) {
		return;
	}

	// do a basic initialisation sequence
	outb(base + 0x01, 0x00);	
	outb(base + 0x03, 0x80);
	outb(base + 0x00, 0x03);
	outb(base + 0x01, 0x00);
	outb(base + 0x03, 0x03);
	outb(base + 0x02, 0xC7);
	outb(base + 0x04, 0x0B);
	outb(base + 0x04, 0x1E);

	// test serial chip
	outb(base + 0x00, 0xAE);
	if (inb(base + 0x00) != 0xAE) {
		return;
	}

	// serial chip must be working, so we have a port
	
	// go back to normal operation mode
	outb(base + 0x04, 0x0F);
	
	auto deviceChild = new SerialHardware();
	deviceChild->connectionType = DeviceRootConnectionType::ISAManual;
	deviceChild->isamanual.probeBase[0] = base;
	deviceChild->setDriver(new UART16550());
	hw->addChild(deviceChild);

	++numCOMsFound;
}

void ISADriver::initialise()
{
	// do DMA controller
	auto deviceChild = new LegacyDMAHardware();
	deviceChild->setDriver(new DMA8237());
	hw->addChild(deviceChild);

	
	// do serial ports
	detectCOMPort(0x3F8);
	detectCOMPort(0x2F8);
	detectCOMPort(0x3E8);
	detectCOMPort(0x2E8);

	if (numCOMsFound >= 3) {
		detectCOMPort(0x5F8);
		detectCOMPort(0x4F8);
		detectCOMPort(0x5E8);
		detectCOMPort(0x4E8);
	}
}

void ISADriver::detect()
{

}

void ISADriver::deinitialise()
{

}

void ISADriver::setPowerState(DevicePowerState state)
{

}

const char* ISADriver::getHumanReadableName()
{
	return ISA_DRIVER_NAME;
}