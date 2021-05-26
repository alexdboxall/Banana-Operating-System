#include "core/common.hpp"
#include "hal/intctrl.hpp"
#include "hw/intctrl/apic.hpp"
#include "hw/acpi.hpp"
#include "hw/cpu.hpp"
#include "krnl/hal.hpp"
#pragma GCC optimize ("O0")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

bool IOAPICsSetupYet = false;
IOAPIC* ioapics[8];
int noOfIOAPICs;

//this local APIC stuff
uint32_t apicGetBase()
{
	if (!computer->features.hasMSR) {
		return 0;
	}
	
	uint64_t ret = computer->rdmsr(IA32_APIC_BASE_MSR);
	return (ret & 0xfffff000);
}

void apicOpen() {
	if (!IOAPICsSetupYet) {
		//start the IO APICs

		for (uint8_t i = 0; i < ioapicDiscoveryNumber; ++i) {
			IOAPIC* io = new IOAPIC();

			ioapics[i] = io;
			++noOfIOAPICs;

			computer->root->addChild(io);

			io->open(i, 0, nullptr);
		}

		IOAPICsSetupYet = true;
	}

	uint32_t* ptr = (uint32_t*) (size_t) (apicGetBase() + 0xf0);

	//get current register data
	uint32_t val = *ptr;

	//enable the thing
	val |= (1 << 8);

	//spurious IRQ is now at 0xFF
	val |= 0xFF;

	//set the new value
	*ptr = val;

	//set NMIs 
	for (int i = 0; i < nextAPICNMI; ++i) {
		uint8_t processorID = apicNMIInfo[i] & 0xFF;
		uint16_t flags = (apicNMIInfo[i] >> 8) & 0xFFFF;
		uint8_t lint = (apicNMIInfo[i] >> 24) & 0xFF;

		if (processorID == 0xFF/* || processorID == thisAPIC*/) {
			uint32_t* ptr = (uint32_t*) (size_t) (apicGetBase() + (lint == 1 ? 0x360 : 0x350));

			uint32_t data = *ptr;
			data &= ~0xFF;
			data |= 0x2;		//point NMI to IRQ 2
			*ptr = data;
		}
	}
}


IOAPIC::IOAPIC() : Device("IO APIC") {
	
}

#define IOAPICID          0x00
#define IOAPICVER         0x01
#define IOAPICARB         0x02
#define IOAPICREDTBL(n)   (0x10 + 2 * n) // lower-32bits (add +1 for upper 32-bits)

bool IOAPIC::handlesGSIWithNumber(unsigned number)
{
	return (number >= gsiBase) && (number < gsiBase + handles);
}

int IOAPIC::open(int a, int, void*) {
	number = a;
	base = ioapicAddresses[number];
	gsiBase = ioapicGSIBase[number];

	memory[noMems].rangeStart = base;
	memory[noMems++].rangeLength = 0xDEAD;

	handles = ((read(IOAPICVER) >> 16) & 0xFF) + 1;

	return 0;
}	

int IOAPIC::read(int reg) {
	uint32_t volatile* ioapic = (uint32_t volatile*) base;
	ioapic[0] = (reg & 0xff);
	return ioapic[4];
}

void IOAPIC::write(int reg, int val)
{
	uint32_t volatile* ioapic = (uint32_t volatile*) base;
	ioapic[0] = (reg & 0xff);
	ioapic[4] = (uint32_t) val;
}

void IOAPIC::redirect(uint8_t irq, uint64_t apic_id, uint8_t irqNumberOnLocalAPIC, bool levelTriggered, bool activeLow)
{
	const uint32_t low_index = 0x10 + irq * 2;
	const uint32_t high_index = 0x10 + irq * 2 + 1;

	uint32_t high = read(high_index);
																				
	//set APIC ID
	high &= ~0xff000000;
	high |= apic_id << 24;
	write(high_index, high);

	uint32_t low = read(low_index);				
																				
	//unmask the IRQ
	low &= ~(1 << 16);

	//set to physical delivery mode
	low &= ~(1 << 11);

	//set to fixed delivery mode
	low &= ~0x700;

	if (levelTriggered) {
		low |= (1 << 13);
	} else {
		low &= ~(1 << 13);
	}

	if (activeLow) {
		low |= (1 << 15);
	} else {
		low &= ~(1 << 15);
	}

	// set delivery vector
	low &= ~0xff;
	low |= irqNumberOnLocalAPIC;

	write(low_index, low);
}

int IOAPIC::close(int, int, void*) { 
	return 0; 
}