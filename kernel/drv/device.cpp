
#include <drv/device.hpp>
#include <drv/driver.hpp>
#include <krnl/panic.hpp>

extern "C" {
#include <libk/string.h>
}

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

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

void Hardware::setHumanReadableName(const char* _name)
{
	strcpy(name, _name);
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
	
}

Hardware::Hardware(BuiltinDriver driver)
{

}

Hardware::Hardware(const char* driverPath)
{

}

void Hardware::detectRecursively()
{
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
