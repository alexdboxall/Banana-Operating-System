#include "core/common.hpp"
#include "krnl/panic.hpp"
#include "sys/syscalls.hpp"
#include "thr/prcssthr.hpp"
#include "thr/elf.hpp"
#include "hal/intctrl.hpp"
#include "hw/intctrl/pic.hpp"
#include "hw/intctrl/apic.hpp"
#include "hal/device.hpp"
#include "hw/acpi.hpp"
#include "krnl/hal.hpp"
#include "hw/cpu.hpp"
#include "vm86/vm8086.hpp"

#pragma GCC optimize ("O2")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

void (*INT_handlers[256][4])(regs* r, void* context);
void* INT_contexts[256][4];

extern "C" uint64_t int_handler(struct regs* r)
{
	while (Krnl::kernelInPanic) {
		Hal::disableIRQs();
		Hal::stallProcessor();
	}

	int num = r->int_no;

	//send EOI command for IRQs
	//this is done now because the handler could cause a task switch, which
	//would mean the EOI never gets called, and so the system basically locks up
	if (num >= 32 && num < 32 + 24) {
		Hal::endOfInterrupt(num - 32);
	}

	auto handleList = INT_handlers[num];
	auto contextList = INT_contexts[num];

	//call handler if it exists
	for (int i = 0; i < 4; ++i) {
		if (handleList[i]) {
			if (r->int_no == 96) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-function-type"
				return reinterpret_cast<uint64_t(*)(regs*, void*)>(handleList[i])(r, contextList[i]);		//this has got to be the world's worst line of code, ever
#pragma GCC diagnostic pop
			} else {
				handleList[i](r, contextList[i]);
			}
		}
	}

	return 0;
}

void installISRHandler(int num, void (*handler)(regs*, void*), void* context)
{
	for (int i = 0; i < 4; ++i) {
		if (INT_handlers[num][i] == nullptr) {
			//set handler
			INT_handlers[num][i] = handler;
			INT_contexts[num][i] = context;
			return;
		}
	}

	panic("[intctrl] A!");
}

int installIRQHandler(int num, void (*handler)(regs*, void*), bool legacy, void* context)
{
	if (computer->features.hasAPIC) {
		bool levelTriggered = false;
		bool activeLow = false;

		if (legacy) {
			if (num < 16) {
				num = legacyIRQRemaps[num];
				if (legacyIRQFlags[num] & 2) {
					activeLow = true;
				}
				if (legacyIRQFlags[num] & 8) {
					levelTriggered = false;
				}
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
				ioapics[i]->redirect(num, CPU::getNumber(), num + 32, levelTriggered, activeLow);
				found = true;
				break;
			}
		}
		if (!found) {
			panic("[apic] OOPS!");
		}
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

	panic("can't install IRQ handler, too many!");
	return -1;
}

void uninstallISRHandler(int num, void (*handler)(regs*, void*))
{
	for (int i = 0; i < 4; ++i) {
		if (handler == handlers[num][i]) {
			INT_handlers[num][i] = nullptr;
			INT_contexts[num][i] = nullptr;
		}
	}
}

void clearAllHandlers(int num, bool legacy)
{
	if (legacy && computer->features.hasAPIC) {
		if (num < 16) {
			num = legacyIRQRemaps[num];
		} else {
			panic("[intctrl] D!");
		}
	}

	num += 32;
	for (int i = 0; i < 4; ++i) {
		handlers[num][i] = nullptr;
		contexts[num][i] = nullptr;
	}
}

void uninstallIRQHandler(int num, void (*handler)(regs*, void*), bool legacy)
{
	if (legacy && computer->features.hasAPIC) {
		if (num < 16) {
			num = legacyIRQRemaps[num];
		} else {
			panic("[intctrl] E!");
		}
	}

	num += 32;
	for (int i = 0; i < 4; ++i) {
		if (handler == INT_handlers[num][i]) {
			INT_handlers[num][i] = nullptr;
			INT_contexts[num][i] = nullptr;
		}
	}
}

void setupINTS() {
	//set all handlers to null so they don't get called
	for (int i = 0; i < 256; ++i) {
		for (int j = 0; j < 4; ++j) {
			INT_handlers[i][j] = nullptr;
			INT_contexts[i][j] = nullptr;		//not needed, but just to keep a consistant startup state
		}
	}
}

int convertLegacyIRQNumber(int num)
{
	if (computer->features.hasAPIC) {
		if (num < 16) {
			num = legacyIRQRemaps[num];
		} else {
			panic("[installIRQHandler] Legacy IRQ with number 16 or higher");
		}
	}

	return num;
}