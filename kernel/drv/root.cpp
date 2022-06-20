#pragma once

#include <drv/root.hpp>
#include <drv/bus.hpp>
#include <drv/driver/isa.hpp>
#include <drv/driver/pci.hpp>
#include <drv/driver/acpi.hpp>

bool RootDriver::hasACPI()
{
	return true;
}

bool RootDriver::hasPCI()
{
	return true;
}

void RootDriver::initialise()
{
	auto isa = new BusHardware(reinterpret_cast<BusDriver*>(new ISADriver()));
	hw->addChild(isa);

	if (hasACPI()) {
		auto acpi = new BusHardware(reinterpret_cast<BusDriver*>(new ACPIDriver()));
		hw->addChild(acpi);
	}

	if (hasPCI()) {
		auto pci = new BusHardware(reinterpret_cast<BusDriver*>(new PCIDriver()));
		hw->addChild(pci);
	}
}

void RootDriver::detect()
{

}

void RootDriver::deinitialise()
{

}

void RootDriver::setPowerState(DevicePowerState state)
{

}

const char* RootDriver::getHumanReadableName()
{
	return "Computer";
}