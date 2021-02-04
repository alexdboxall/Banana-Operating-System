#include "hal/device.hpp"
#include "core/common.hpp"
#include "core/computer.hpp"
#include "hal/intctrl.hpp"
#include "hw/cpu.hpp"
#include "core/prcssthr.hpp"
//#pragma GCC optimize ("Os")

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
	bool driverFound = false;

	if (detectionType == DetectionType::Manual) {

	} else if (detectionType == DetectionType::ISAProbe) {

	} else if (detectionType == DetectionType::PCI) {

	} else if (detectionType == DetectionType::USB) {

	} else if (detectionType == DetectionType::ACPI) {

	}

	if (driverFound) {
		//call start() on the driver DLL
		//that will call	 Whatever* w = new Whatever("Fancy Hardware")
		//NEW!! then it will return w

		Device* newDevice = nullptr;		//the return value
		
		if (!parent) {
			panic("TRIED TO LOAD DRIVER FOR THE ROOT (COMPUTER)");
		}

		DeviceNode* conductor = parent->children;

		while (conductor->next) {
			if (conductor->child == this) {
				lockScheduler();

				conductor->child = newDevice;					//replace ourselves with the new one
				newDevice->parent = this->parent;				//the new device doesn't have a parent yet

				newDevice->detectionType = detectionType;
				newDevice->acpi = acpi;
				newDevice->pci = pci;
				if (newDevice->dmaChannel == -1) newDevice->dmaChannel = dmaChannel;
				if (newDevice->interrupt == -1) newDevice->interrupt = interrupt;

				newDevice->next = this->next;

				if (newDevice->noMems == 0) {
					newDevice->noMems = noMems;
					for (int i = 0; i < noMems; ++i) {
						newDevice->memory[i] = memory[i];
					}
				}

				if (newDevice->noPorts == 0)
				{
					newDevice->noPorts = noPorts;
					for (int i = 0; i < noPorts; ++i) {
						newDevice->ports[i] = ports[i];
					}
				}

				unlockScheduler();

				newDevice->open(0, 0, nullptr);

				delete this;			//suicide
				return;
			}
			conductor = conductor->next;
		}
	}
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
	if (this->deviceType == DeviceType::Intctrl) {
		InterruptController* intc = reinterpret_cast<InterruptController*>(this);
			
		return intc->installIRQHandler(num, handler, legacy, context);

	} else {
		return thisCPU()->intCtrl->installIRQHandler(num, handler, legacy, context);
	}
}

void Device::removeIRQHandler(int num, void (*handler)(regs*, void*), bool legacy)
{
	if (this->deviceType == DeviceType::Intctrl) {
		(reinterpret_cast<InterruptController*>(this))->uninstallIRQHandler(num, handler, legacy);

	} else {
		thisCPU()->intCtrl->uninstallIRQHandler(num, handler, legacy);
	}
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
	disableLegacy();

	DeviceNode* conductor = children;

	while (conductor->next) {
		conductor->child->disableLegacyAll();
		conductor = conductor->next;
	}
}

void Device::loadDriversForAll()
{
	if (deviceType == DeviceType::Unknown) {
		findAndLoadDriver();
	}

	DeviceNode* conductor = children;

	while (conductor->next) {
		conductor->child->loadDriversForAll();
		conductor = conductor->next;
	}
}

void Device::closeAll()
{
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

}

int DriverlessDevice::open(int, int, void*)
{
	panic("CANNOT OPEN DRIVERLESS DEVICE");
	return -1;
}

int DriverlessDevice::close(int, int, void*)
{
	return 0;
}

void DriverlessDevice::detect()
{

}