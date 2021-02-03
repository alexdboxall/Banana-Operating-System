#include "core/common.hpp"
#include "hal/intctrl.hpp"
#include "hw/intctrl/apic.hpp"
#include "hw/ports.hpp"
#include "hw/acpi.hpp"
#include "hw/cpu.hpp"
#pragma GCC optimize ("O2")

#define IA32_APIC_BASE_MSR 0x1B
#define IA32_APIC_BASE_MSR_BSP 0x100 // Processor is a BSP
#define IA32_APIC_BASE_MSR_ENABLE 0x800
#define APIC_REGISTER_LVT_TIMER					0x320
#define APIC_REGISTER_TIMER_INITCNT				0x380
#define APIC_REGISTER_TIMER_CURRCNT				0x390
#define APIC_REGISTER_TIMER_DIV					0x3E0
#define APIC_REGISTER_LVT_MASKED				0x10000
#define APIC_REGISTER_LVT_TIMER_MODE_PERIODIC	0x20000

bool IOAPICsSetupYet = false;
IOAPIC* ioapics[8];
int noOfIOAPICs;

APIC::APIC(): InterruptController("Advanced Programmable Interrupt Controller")
{
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
}

void APIC::io_wait()
{
	asm volatile ("jmp 1f\n\t"
				  "1:jmp 2f\n\t"
				  "2:");
}

void APIC::disable()
{

}

int APIC::installIRQHandler(int num, void (*handler)(regs*, void*), bool legacy, void* context)
{
	if (legacy) {
		if (num < 16) {
			num = legacyIRQRemaps[num];
		} else {
			panic("[installIRQHandler] Legacy IRQ with number 16 or higher");
		}
	}

	//redirect the 'num'th of the IO APIC (0 - 23) to the IRQ on the local system (number + 32)
	
	//which one do we use? the first one where handlesGSIWithNumber(num) returns true;

	bool found = false;
	kprintf("System has %d IOAPICs\n", noOfIOAPICs);
	for (int i = 0; i < noOfIOAPICs; ++i) {
		if (ioapics[i]->handlesGSIWithNumber(num)) {
			ioapics[i]->redirect(num, getCPUNumber(), num + 32);
			found = true;
			break;
		}
	}
	if (!found) {
		panic("[apic] OOPS!");
	}

	//IRQs start at 32
	num += 32;
	
	for (int i = 0; i < 4; ++i) {
		if (handlers[num][i] == nullptr) {
			//set handler
			handlers[num][i] = handler;
			contexts[num][i] = context;

			return num - 32;
		}
	}

	panic("[apic] Could not install IRQ handler, too many already!");
	return -1;
}

//this local APIC stuff
void APIC::eoi(uint8_t irqNum)
{
	uint32_t* ptr = (uint32_t*) (size_t) (getBase() + 0xb0);
	*ptr = 1;
}

//this local APIC stuff
uint32_t APIC::getBase()
{
	if (!computer->features.hasMSR) {
		return 0;
	}
	
	uint64_t ret = computer->rdmsr(IA32_APIC_BASE_MSR);
	return (ret & 0xfffff000);
}

int APIC::open(int, int, void*)
{
	uint32_t* ptr = (uint32_t*) (size_t) (getBase() + 0xf0);

	memory[noMems].rangeStart = getBase();
	memory[noMems++].rangeLength = 0x100;

	uint32_t val = *ptr;
	val |= (1 << 8);
	*ptr = val;

	return 0;
}

int APIC::close(int, int, void*)
{
	disable();
	return 0;
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
	kprintf("OPENING IOAPIC.\n");

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

void IOAPIC::redirect(uint8_t irq, uint64_t apic_id, uint8_t irqNumberOnLocalAPIC)
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

	// set delivery vector
	low &= ~0xff;
	low |= irqNumberOnLocalAPIC;

	write(low_index, low);
}

int IOAPIC::close(int, int, void*) { 
	return 0; 
}