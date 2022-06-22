
#include <drv/device.hpp>
#include <drv/driver.hpp>
#include <drv/root.hpp>
#include <krnl/panic.hpp>
#include <dbg/kconsole.hpp>
#include <drv/root.hpp>

#include <drv/driver/acpi.hpp>
#include <drv/driver/pci.hpp>
#include <drv/driver/isa.hpp>
#include <drv/driver/isapnp.hpp>

extern "C" {
#include <libk/string.h>
}

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")


RootHardware* keDeviceTreeRoot;

void KeSetupDeviceTree()
{
	keDeviceTreeRoot = new RootHardware();
	keDeviceTreeRoot->detectRecursively();				// load disk drivers
	// TODO: load filesystem
	keDeviceTreeRoot->detectRecursively();				// load USB, PCI devices, ACPI devices, legacy PnP etc.
	keDeviceTreeRoot->driver->detectLegacyISA();		// PS/2 keyboard, serial ports, etc.
}

bool KeIsPortInUse(uint16_t port, int length)
{
	kprintf("TODO: KeIsPortInUse NOT IMPLEMENTED\n");
	return false;
}

RootHardware* KeGetRootDevice()
{
	return keDeviceTreeRoot;
}

BusHardware* KeGetChildOfRootWithName(const char* str)
{
	for (const auto& child : KeGetRootDevice()->children) {
		if (!strcmp(child->getHumanReadableName(), str)) {
			return reinterpret_cast<BusHardware*>(child);
		}
	}

	return nullptr;
}

BusHardware* KeGetPCIDevice()
{
	return KeGetChildOfRootWithName(PCI_DRIVER_NAME);
}

BusHardware* KeGetACPIDevice()
{
	return KeGetChildOfRootWithName(ACPI_DRIVER_NAME);
}

BusHardware* KeGetISAPnPDevice()
{
	return KeGetChildOfRootWithName(ISA_PNP_DRIVER_NAME);
}

BusHardware* KeGetISADevice()
{
	return KeGetChildOfRootWithName(ISA_DRIVER_NAME);
}

void KePrintDeviceTree()
{
	kprintf("\n\n----------------------------------------\n\nDEVICE TREE:\n\n");
	keDeviceTreeRoot->printRecursively(0);
	kprintf("\n\n----------------------------------------\n\n");
}

void Hardware::printRecursively(int level)
{
	for (int i = 0; i < level; ++i) {
		kprintf("    ");
	}

	char types[][12] = {
		"<UNKNOWN> ",
		"<BUS>     ",
		"<KEYBOARD>",
		"<MOUSE>   ",
		"<ROOT>    ",
		"<DISK>    ",
		"<SERIAL>  "
	};

	kprintf("%s %s\n", types[(int) getType()], getHumanReadableName());

	for (auto const& child : children) {
		child->printRecursively(level + 1);
	}
}

void Hardware::registerMemoryRange(size_t start, size_t length)
{
	DeviceMemoryRange range;
	range.start = start;
	range.length = length;

	memoryRanges.push_back(range);
}

void Hardware::registerPortRange(uint16_t start, uint8_t length, int width)
{
	int bitWidth;
	switch (width) {
	case 1:
		bitWidth = 0;
		break;
	case 2:
		bitWidth = 1;
		break;
	case 4:
		bitWidth = 2;
		break;
	case 8:
		bitWidth = 3;
		break;
	default:
		KePanic("Hardware::registerPortRange INVALID PORT WIDTH");
		return;
	}

	DevicePortRange range;
	range.start = start;
	range.length = length;
	range.alignment = 0;
	range.width = bitWidth;

	portRanges.push_back(range);
}

Hardware::~Hardware()
{

}

void Hardware::registerIRQ(int irq)
{
	for (int i = 0; i < HARDWARE_MAX_IRQ_REGISTRATIONS; ++i) {
		if (!(irqUsageBitflags & (1 << i))) {
			irqs[i] = irq;
			irqUsageBitflags |= (1 << i);
			return;
		}
	}
}

void Hardware::deregisterIRQ(int irq)
{
	for (int i = 0; i < HARDWARE_MAX_IRQ_REGISTRATIONS; ++i) {
		if (irqs[i] == irq) {
			irqUsageBitflags &= ~(1 << i);
		}
	}
}

const char* Hardware::getHumanReadableName()
{
	auto driver = _getDriver();
	if (driver) {
		return driver->getHumanReadableName();
	} else {
		return "Unknown Device";
	}
}

void Hardware::addChild(Hardware* child)
{
	children.push_back(child);
}

void Hardware::removeChild(Hardware* child)
{
	children.erase(std::remove(children.begin(), children.end(), child), children.end());
}

Hardware::Hardware()
{
	irqUsageBitflags = 0;
}

void Hardware::detectRecursively()
{
	kprintf("detecting recursively...\n");

	// we must detect updates to what we have before we can update what they have
	auto driver = _getDriver();
	if (driver) {
		driver->detect();
	}

	for (auto const& child : children) {
		child->detectRecursively();
	}
}

void Hardware::deinitialiseRecursively()
{
	for (auto const& child : children) {
		child->deinitialiseRecursively();
	}
	
	// we can't destroy ourselves until the children are destroyed
	auto driver = _getDriver();
	if (driver) {
		driver->deinitialise();
	}
}

void Hardware::setPowerStateRecursively(DevicePowerState state)
{
	for (auto const& child : children) {
		child->setPowerStateRecursively(state);
	}

	auto driver = _getDriver();
	if (driver) {
		driver->setPowerState(state);
	}
}

void Hardware::getHardwareOfTypeAux(HardwareType type, std::vector<Hardware*>& vec)
{
	if (type == getType()) {
		vec.push_back(this);
	}

	for (const auto& child : children) {
		child->getHardwareOfTypeAux(type, vec);
	}
}

std::vector<Hardware*> KeGetHardwareOfType(HardwareType type)
{
	auto vec = std::vector<Hardware*>();
	keDeviceTreeRoot->getHardwareOfTypeAux(type, vec);
	return vec;
}