
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

#pragma GCC optimize ("O2")			// I swear there's a compiler bug (unless I've got UB somewhere), it's not putting RETs after CALLs that end the function with Os enabled
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")


RootHardware* keDeviceTreeRoot;

void KeSetupDeviceTree()
{
	// we need RootDriver::RootDriver() to return quickly without calling initialise() so we can do
	// keDeviceTreeRoot = new RootDriver(), otherwise keDeviceTreeRoot is undefined during the call
	// to initialise()
	keDeviceTreeRoot = new RootHardware();

	keDeviceTreeRoot->driver->hw = keDeviceTreeRoot;
	keDeviceTreeRoot->driver->initialise();

	keDeviceTreeRoot->detectRecursively();				// load disk drivers
	// TODO: load filesystem
	keDeviceTreeRoot->detectRecursively();				// load USB, PCI devices, ACPI devices, legacy PnP etc.
	keDeviceTreeRoot->driver->detectLegacyISA();		// PS/2 keyboard, serial ports, etc.
}

bool KeIsPortInUse(uint16_t port, int length)
{
	return keDeviceTreeRoot->portInUseRecursive(port, length) != nullptr;
}

Hardware* KeGetOwnerOfPort(uint16_t port, int length)
{
	return keDeviceTreeRoot->portInUseRecursive(port, length);
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

void KePrintIOPortUsage()
{
	kprintf("\n\n----------------------------------------\n\nIO PORTS:\n\n");
	for (int port = 0; port < 0x10000; ++port) {
		auto portOwner = KeGetOwnerOfPort(port, 1);
		if (portOwner) {
			kprintf("%X: %s\n", port, portOwner->_getDriver()->getHumanReadableName());
		}
	}
	kprintf("\n\n----------------------------------------\n\n");
}

Hardware* Hardware::portInUseRecursive(int port, int range)
{	
	// check ourselves first
	for (auto const& portRange : portRanges) {
		if (portRange.start < port + range && port < portRange.start + portRange.length) {
			return this;
		}
	}

	// now check any children
	for (auto const& child : children) {
		if (child == this) {
			KePanic("WTF?!");
		}
		auto owner = child->portInUseRecursive(port, range);
		if (owner) {
			return owner;
		}
	}

	// nope! not in use
	return nullptr;
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
		"<SERIAL>  ",
		"<DMA>     "
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

	kprintf("registering port range starting at %d for device %s\n", start, getHumanReadableName());

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