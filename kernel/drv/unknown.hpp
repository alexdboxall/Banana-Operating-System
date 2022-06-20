#pragma once

#include <drv/device.hpp>
#include <drv/driver.hpp>

#include <drv/driver/pci.hpp>

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
		pci = info;

		strcpy(pciDeviceName, "Unknown ");
		strcat(pciDeviceName, PCIDriver::lookupDeviceName(pci.info));
	}

	virtual const char* getHumanReadableName() override
	{
		if (connectionType == DeviceRootConnectionType::PCI) {
			return pciDeviceName;

		} else {
			return Hardware::getHumanReadableName();
		}
	}
};
