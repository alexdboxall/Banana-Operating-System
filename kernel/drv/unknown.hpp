#pragma once

#include <drv/device.hpp>
#include <drv/driver.hpp>
#include <drv/driver/pci.hpp>

extern "C" {
#include <libk/string.h>
}

class UnknownHardware : public Hardware
{
protected:
	virtual Driver* _getDriver() override
	{
		return (Driver*) nullptr;
	}

	HardwareType getType()
	{
		return HardwareType::Unknown;
	}

	// this kind of data is normally in the driver, but we don't have one, 
	// and we need this data to work out what driver to load
	
	char pciDeviceName[256];

public:
	UnknownHardware() : Hardware()
	{
		connectionType = DeviceRootConnectionType::None;
	}

	UnknownHardware(DevicePCIConnectionInfo info) : Hardware()
	{
		connectionType = DeviceRootConnectionType::PCI;
		pci.info = info;

		strcpy(pciDeviceName, "Unknown ");
		strcat(pciDeviceName, PCIDriver::lookupDeviceName(pci.info));
	}

	void setISAPnPDetection(uint8_t csn, uint64_t value)
	{
		connectionType = DeviceRootConnectionType::ISAPnP;
		isapnp.csn = csn;
		isapnp.vendorID = (value & 0xFFFFFFFF);
		isapnp.serialNumber = value >> 32;
	}

	virtual const char* getHumanReadableName() override
	{
		if (connectionType == DeviceRootConnectionType::PCI) {
			return pciDeviceName;

		} else if (connectionType == DeviceRootConnectionType::ISAPnP) {
			return "Legacy ISA Plug and Play Device";

		} else {
			return Hardware::getHumanReadableName();
		}
	}
};
