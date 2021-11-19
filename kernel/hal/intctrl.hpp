#ifndef _INTCTRL_HPP_
#define _INTCTRL_HPP_

#include <stdint.h>
#include <stddef.h>
#include "hal/device.hpp"
#include "hw/acpi.hpp"

#include <arch/regs.hpp>
#include <arch/hal.hpp>

extern "C" uint64_t int_handler(struct regs* r);
extern "C" void Subhandler(struct regs* r, void* context);

InterruptController* setupInterruptController();

#endif