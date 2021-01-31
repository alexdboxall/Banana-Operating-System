
#ifndef _APIC_HPP_
#define _APIC_HPP_

#include <stdint.h>
#include "hal/intctrl.hpp"

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

	void redirect(uint8_t irq, uint64_t apic_id, uint8_t vector);

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