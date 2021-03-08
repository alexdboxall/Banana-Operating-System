#ifndef _INTCTRL_HPP_
#define _INTCTRL_HPP_

#include <stdint.h>
#include <stddef.h>
#include "hal/device.hpp"
#include "hw/acpi.hpp"

//if you change this, very bad stuff could happen if you don't change the matching assembly
//(warning: THIS INCLUDES THE FORKING CODE, SYSCALLS AND INTERRUPTS, TASK CREATION, TASK SWITCHING, XADD VOODOO, ETC.!)
struct regs
{	
	//PUSHED LATER				PUSHED EARLIER
	//POPPED EARLIER			POPPED LATER
	unsigned int gs, fs, es, ds;
	unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
	unsigned int int_no, err_code;
	unsigned int eip, cs, eflags, useresp, ss;

	//VM8086 ONLY
	unsigned int v86es, v86ds, v86fs, v86gs;
};

extern "C" uint64_t int_handler(struct regs* r);
extern "C" void Subhandler(struct regs* r, void* context);

class InterruptController : public Device
{
private:

protected:
	friend uint64_t int_handler(struct regs* r);
	friend void Subhandler(struct regs* rgs, void* context);

	void (*handlers[256][4])(regs* r, void* context);
	void* contexts[256][4];

public:
	InterruptController(const char* name);
	virtual void installISRHandler(int num, void (*handler)(regs*, void*), void* context = 0);
	virtual int installIRQHandler(int num, void (*handler)(regs*, void*), bool legacy, void* context = 0);
	virtual void uninstallISRHandler(int num, void (*handler)(regs*, void*));
	virtual void uninstallIRQHandler(int num, void (*handler)(regs*, void*), bool legacy);
	virtual void clearAllHandlers(int num, bool legacy);
	virtual void eoi(uint8_t irqNum) = 0;
	virtual void disable() = 0;
	virtual ~InterruptController();

	int convertLegacyIRQNumber(int num);
};

InterruptController* setupInterruptController();

#endif