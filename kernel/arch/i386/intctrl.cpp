#include "krnl/common.hpp"
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
#include <arch/i386/x86.hpp>

#pragma GCC optimize ("O2")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

#include <krnl/fault.hpp>

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
