#include "hal/device.hpp"
#include "krnl/common.hpp"
#include "krnl/computer.hpp"
#include "hal/intctrl.hpp"
#include "hw/cpu.hpp"
#include "thr/prcssthr.hpp"
#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

Device::Device(const char* name)
{
	setName(name);

	children = new DeviceNode();
	children->next = nullptr;
	children->child = nullptr;

	noPorts = 0;
	noMems = 0;

	interrupt = -1;
	interrupt2 = -1;
	dmaChannel = -1;

	deviceType = DeviceType::Unknown;
}

Device::~Device()
{

}

void Device::findAndLoadDriver()
{
	kprintf("DON'T USE THIS CODE ANYMORE. Device::findAndLoadDriver()\n");
}

void Device::preOpenPCI(PCIDeviceInfo info)
{
	detectionType = DetectionType::PCI;
	pci.info = info;
}

void Device::preOpenACPI(ACPI_HANDLE h, char* namespaceName, char* pnpID)
{
	detectionType = DetectionType::ACPI;
	acpi.handle = h;
	memcpy(acpi.namespaceName, namespaceName, sizeof(acpi.namespaceName));
	memcpy(acpi.pnpID, pnpID, sizeof(acpi.pnpID));
}


int Device::addIRQHandler(int num, void (*handler)(regs*, void*), bool legacy, void* context)
{
	return installIRQHandler(num, handler, legacy, context);
}

Device* Device::getParent()
{
	return parent;
}

void Device::removeIRQHandler(int num, void (*handler)(regs*, void*), bool legacy)
{
	uninstallIRQHandler(num, handler, legacy);
}


/*
Wondering why something like this->parent->read() isn't working?
MAKE SURE THAT this->addChild() is called BEFORE CONFIG AND OPEN
*/


//Called to add a new child.
void Device::addChild(Device* child)
{
	child->parent = this;

	DeviceNode* conductor = children;

	while (conductor->next) {
		conductor = conductor->next;
	}
	conductor->child = child;
	conductor->next = new DeviceNode;
	conductor = conductor->next;
	conductor->next = nullptr;
	conductor->child = nullptr;
}

void Device::removeAllChildren()
{
	DeviceNode* conductor = children;

	while (conductor->next) {
		delete conductor->child;
		conductor = conductor->next;
	}

	children->next = nullptr;
	children->child = nullptr;
}

//These call the functions above on all children
//should not be overriden
void Device::hibernateAll()
{
	hibernate();

	DeviceNode* conductor = children;

	while (conductor->next) {
		conductor->child->hibernateAll();
		conductor = conductor->next;
	}
}

void Device::wakeAll()
{
	wake();

	DeviceNode* conductor = children;

	while (conductor->next) {
		conductor->child->wakeAll();
		conductor = conductor->next;
	}
}

void Device::detectAll()
{
	detect();

	DeviceNode* conductor = children;

	while (conductor->next) {
		conductor->child->detectAll();
		conductor = conductor->next;
	}
}

void Device::disableLegacyAll()
{

}

void Device::loadDriversForAll()
{

}

void Device::closeAll()
{
	kprintf("closing %s\n", this->getName());
	close(0, 0, nullptr);

	DeviceNode* conductor = children;

	while (conductor->next) {
		conductor->child->closeAll();
		conductor = conductor->next;
	}
}

void Device::powerSavingAll(PowerSavingLevel level)
{
	powerSaving(level);

	DeviceNode* conductor = children;

	while (conductor->next) {
		conductor->child->powerSavingAll(level);
		conductor = conductor->next;
	}
}

void Device::setName(const char* name)
{
	strcpy(humanName, name);
}

char* Device::getName()
{
	return humanName;
}

void Device::addToLinkedList(LinkedList<Device>& list, DeviceType devType)
{
	if (deviceType == devType) {
		list.addElement(this);
	}

	DeviceNode* conductor = children;

	while (conductor->next) {
		conductor->child->addToLinkedList(list, devType);
		conductor = conductor->next;
	}
}

//these can/should be overwritten
void Device::hibernate()
{

}

void Device::wake()
{

}

void Device::detect()
{

}

void Device::disableLegacy()
{

}

void Device::powerSaving(PowerSavingLevel level)
{

}


LinkedList<Device> getDevicesOfType(DeviceType devType)
{
	LinkedList <Device> r;
	computer->addToLinkedList(r, devType);
	return r;
}

DriverlessDevice::DriverlessDevice(const char* name): Device(name)
{
	deviceType = DeviceType::Driverless;
}

int DriverlessDevice::open(int, int, void*)
{
	KePanic("CANNOT OPEN DRIVERLESS DEVICE");
	return -1;
}

int DriverlessDevice::close(int, int, void*)
{
	return 0;
}

void DriverlessDevice::detect()
{

}