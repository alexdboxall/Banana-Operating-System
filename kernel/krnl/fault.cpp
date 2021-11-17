#include <krnl/panic.hpp>
#include <thr/prcssthr.hpp>
#include "krnl/common.hpp"
#include "krnl/panic.hpp"
#include "sys/syscalls.hpp"
#include "thr/prcssthr.hpp"
#include "thr/elf.hpp"
#include "hal/intctrl.hpp"
#include "hal/device.hpp"
#include "krnl/hal.hpp"

void KeDisplayProgramFault(const char* text)
{
	kprintf(text);
	if (currentTaskTCB->processRelatedTo->terminal) {
		currentTaskTCB->processRelatedTo->terminal->puts(text, VgaColour::White, VgaColour::Maroon);
	}
}

bool (*gpFaultIntercept)(void* r) = nullptr;

void KeGeneralProtectionFault(void* r, void* context)
{
	gpFaultIntercept = Vm::faultHandler;
	if (gpFaultIntercept) {
		bool handled = gpFaultIntercept(r);
		if (handled) {
			return;
		}
	}

	KeDisplayProgramFault("General protection fault");
	HalDisplayDebugInfo(r);

	Thr::terminateFromIRQ();
}

void KePageFault(void* r, void* context)
{
	if (HalHandlePageFault(r, context)) {
		return;
	}

	KeDisplayProgramFault("Page fault");
	HalDisplayDebugInfo(r);

	Thr::terminateFromIRQ();
}


void KeNonMaskableInterrupt(void* r, void* context)
{
	HalReceivedNMI();
}

void KeOtherFault(void* r, void* context)
{
	KeDisplayProgramFault("Unhandled exception - CHECK KERNEL LOGS");
	HalDisplayDebugInfo(r);

	Thr::terminateFromIRQ();
}

#pragma GCC diagnostic push
#pragma GCC optimize ("O0")


void KeOpcodeFault(void* r, void* context)
{
	if (HalHandleOpcodeFault(r, context)) {
		return;
	}

	KeDisplayProgramFault("Opcode fault");
	HalDisplayDebugInfo(r);

	Thr::terminateFromIRQ();
}
#pragma GCC diagnostic pop

#pragma GCC diagnostic pop

void KeDoubleFault(void* r, void* context)
{
	KePanic("DOUBLE FAULT");
}

