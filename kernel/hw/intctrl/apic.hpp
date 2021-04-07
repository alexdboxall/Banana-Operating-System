
#ifndef _APIC_HPP_
#define _APIC_HPP_

#include <stdint.h>
#include "hal/intctrl.hpp"

#define IA32_APIC_BASE_MSR 0x1B
#define IA32_APIC_BASE_MSR_BSP 0x100			// Processor is a BSP
#define IA32_APIC_BASE_MSR_ENABLE 0x800
#define APIC_REGISTER_LVT_TIMER					0x320
#define APIC_REGISTER_TIMER_INITCNT				0x380
#define APIC_REGISTER_TIMER_CURRCNT				0x390
#define APIC_REGISTER_TIMER_DIV					0x3E0
#define APIC_REGISTER_LVT_MASKED				0x10000
#define APIC_REGISTER_LVT_TIMER_MODE_PERIODIC	0x20000

class IOAPIC: public Device
{
private:

protected:

public:
	int number;
	uint32_t base;
	uint32_t gsiBase;
	int handles;

	bool handlesGSIWithNumber(unsigned number);

	void redirect(uint8_t irq, uint64_t apic_id, uint8_t vector, bool levelTriggered = false, bool activeLow = false);

	IOAPIC();

	int open(int, int, void*);
	int read(int);			
	void write(int, int);
	int close(int, int, void*);
};

extern IOAPIC* ioapics[8];
extern int noOfIOAPICs;

class APIC: public InterruptController
{
private:

protected:
	void io_wait();

public:
	int installIRQHandler(int num, void (*handler)(regs*, void*), bool legacy, void* context = 0) override;

	uint32_t getBase();

	APIC();
	void eoi(uint8_t irqNum) override;
	void disable() override;

	int open(int, int, void*);
	int close(int, int, void*);
};


#endif