#include <krnl/common.hpp>
#include <krnl/panic.hpp>
#include <krnl/fault.hpp>
#include <krnl/hal.hpp>
#include <sys/syscalls.hpp>
#include <thr/prcssthr.hpp>
#include <thr/elf.hpp>
#include <hal/intctrl.hpp>
#include <hal/device.hpp>
#include <hw/acpi.hpp>
#include <hw/cpu.hpp>
#include <vm86/vm8086.hpp>
#include <arch/i386/x86.hpp>
#include <arch/i386/apic.hpp>

#pragma GCC optimize ("O2")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

void (*keInterruptHandlers[256][4])(regs* r, void* context);
void* keInterruptContexts[256][4];

int convertLegacyIRQNumber(int num)
{
	if (features.hasAPIC) {
		if (num < 16) {
			num = legacyIRQRemaps[num];
		} else {
			KePanic("[HalInstallIRQHandler] Legacy IRQ with number 16 or higher");
		}
	}

	return num;
}

void KeSetupInterrupts()
{
	//set all handlers to null so they don't get called
	for (int i = 0; i < 256; ++i) {
		for (int j = 0; j < 4; ++j) {
			keInterruptHandlers[i][j] = nullptr;
			keInterruptContexts[i][j] = nullptr;		//not needed, but just to keep a consistant startup state
		}
	}
}

extern "C" uint64_t int_handler(struct regs* r)
{
	while (KeIsKernelInPanic()) {
		HalDisableInterrupts();
		HalStallProcessor();
	}

	//kprintf("@:> %X\n", r->eip);

	int num = r->int_no;

	//send EOI command for IRQs
	//this is done now because the handler could cause a task switch, which
	//would mean the EOI never gets called, and so the system basically locks up
	if (num >= 32 && num < 32 + 24) {
		HalEndOfInterrupt(num - 32);
	}

	auto handleList = keInterruptHandlers[num];
	auto contextList = keInterruptContexts[num];

	//call handler if it exists
	for (int i = 0; i < 4; ++i) {
		if (handleList[i]) {
			if (r->int_no == 96) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-function-type"
				uint64_t retV = reinterpret_cast<uint64_t(*)(regs*, void*)>(handleList[i])(r, contextList[i]);
#pragma GCC diagnostic pop
				return retV;
			} else {
				handleList[i](r, contextList[i]);
			}
		}
	}

	return 0;
}

void HalInstallISRHandler(int num, void (*handler)(regs*, void*), void* context)
{
	for (int i = 0; i < 4; ++i) {
		if (keInterruptHandlers[num][i] == nullptr) {
			//set handler
			keInterruptHandlers[num][i] = handler;
			keInterruptContexts[num][i] = context;
			return;
		}
	}

	KePanic("[intctrl] A!");
}

int HalInstallIRQHandler(int num, void (*handler)(regs*, void*), bool legacy, void* context)
{
	if (features.hasAPIC) {
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
				KePanic("[HalInstallIRQHandler] Legacy IRQ with number 16 or higher");
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
			KePanic("[apic] OOPS!");
		}
	}

	//IRQs start at 32
	num += 32;

	for (int i = 0; i < 4; ++i) {
		if (keInterruptHandlers[num][i] == nullptr) {
			//set handler
			keInterruptHandlers[num][i] = handler;
			keInterruptContexts[num][i] = context;

			return num - 32;
		}
	}

	KePanic("can't install IRQ handler, too many!");
	return -1;
}

void HalUninstallISRHandler(int num, void (*handler)(regs*, void*))
{
	for (int i = 0; i < 4; ++i) {
		if (handler == keInterruptHandlers[num][i]) {
			keInterruptHandlers[num][i] = nullptr;
			keInterruptContexts[num][i] = nullptr;
		}
	}
}

void HalUninstallIRQHandler(int num, void (*handler)(regs*, void*), bool legacy)
{
	if (legacy && features.hasAPIC) {
		if (num < 16) {
			num = legacyIRQRemaps[num];
		} else {
			KePanic("[intctrl] E!");
		}
	}

	num += 32;
	for (int i = 0; i < 4; ++i) {
		if (handler == keInterruptHandlers[num][i]) {
			keInterruptHandlers[num][i] = nullptr;
			keInterruptContexts[num][i] = nullptr;
		}
	}
}
