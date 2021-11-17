#ifndef _INTCTRL_HPP_
#define _INTCTRL_HPP_

#include <stdint.h>
#include <stddef.h>
#include "hal/device.hpp"
#include "hw/acpi.hpp"

#include <arch/regs.hpp>

extern "C" uint64_t int_handler(struct regs* r);
extern "C" void Subhandler(struct regs* r, void* context);

void setupINTS();
void installISRHandler(int num, void (*handler)(regs*, void*), void* context = 0);
int installIRQHandler(int num, void (*handler)(regs*, void*), bool legacy, void* context = 0);
void uninstallISRHandler(int num, void (*handler)(regs*, void*));
void uninstallIRQHandler(int num, void (*handler)(regs*, void*), bool legacy);
int convertLegacyIRQNumber(int num);

InterruptController* setupInterruptController();

#endif