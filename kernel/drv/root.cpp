#pragma once

#include <drv/root.hpp>
#include <drv/bus.hpp>
#include <drv/driver/isa.hpp>
#include <drv/driver/isapnp.hpp>
#include <drv/driver/pci.hpp>
#include <drv/driver/acpi.hpp>

bool RootDriver::hasACPI()
{
	return true;
}

bool RootDriver::hasISAPnP()
{
	return true;
}

bool RootDriver::hasPCI()
{
	return true;
}

void RootDriver::initialise()
{	
	if (hasACPI()) {
		auto acpi = new BusHardware();
		acpi->setDriver(reinterpret_cast<BusDriver*>(new ACPIDriver()));
		hw->addChild(acpi);
	}

	if (hasPCI()) {
		auto pci = new BusHardware();
		pci->setDriver(reinterpret_cast<BusDriver*>(new PCIDriver()));
		hw->addChild(pci);
	}

	if (hasISAPnP()) {
		auto isapnp = new BusHardware();
		isapnp->setDriver(reinterpret_cast<BusDriver*>(new ISAPnPDriver()));
		hw->addChild(isapnp);
	}

	
	/*auto diskDrives = KeGetHardwareOfType(HardwareType::PhysicalDisk);
	if (diskDrives.size() == 0) {
		KePanic("TODO: ADD HARDCODED PORT ATA DRIVE");
	}
	*/
}

void RootDriver::detectLegacyISA()
{
	auto isa = new BusHardware();
	isa->setDriver(reinterpret_cast<BusDriver*>(new ISADriver()));
	hw->addChild(isa);
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