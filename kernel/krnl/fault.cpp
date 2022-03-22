#include <krnl/panic.hpp>
#include <krnl/common.hpp>
#include <krnl/panic.hpp>
#include <krnl/hal.hpp>
#include <sys/syscalls.hpp>
#include <thr/prcssthr.hpp>
#include <thr/elf.hpp>
#include <hal/intctrl.hpp>
#include <hal/device.hpp>

void (*keInterruptHandlers[256][4])(regs* r, void* context);
void* keInterruptContexts[256][4];

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
	while (KeIsKernelInPanic) {
		HalDisableInterrupts();
		HalStallProcessor();
	}

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
				uint64_t retV = reinterpret_cast<uint64_t(*)(regs*, void*)>(handleList[i])(r, contextList[i]);		//this has got to be the world's worst line of code, ever
#pragma GCC diagnostic pop
				return retV;
			} else {
				handleList[i](r, contextList[i]);
			}
		}
	}

	return 0;
}

#define RETURN_CODE_ON_OPCODE_FAULT					124
#define RETURN_CODE_ON_OTHER_FAULT					125
#define RETURN_CODE_ON_GENERAL_PROTECTION_FAULT		126
#define RETURN_CODE_ON_PAGE_FAULT					127

void KeDisplayProgramFault(const char* text)
{
	kprintf(text);
	if (currentTaskTCB->processRelatedTo->terminal) {
		currentTaskTCB->processRelatedTo->terminal->puts(text, VgaColour::White, VgaColour::Maroon);
	}
}

void KeGeneralProtectionFault(void* r, void* context)
{
	kprintf("GP FAULT!\n");

	if (HalHandleGeneralProtectionFault(r, context)) {
		return;
	}

	KeDisplayProgramFault("General protection fault");
	HalDisplayDebugInfo(r);

	KeTerminateCurrentThread(RETURN_CODE_ON_GENERAL_PROTECTION_FAULT);
}

void KePageFault(void* r, void* context)
{
	kprintf("page fault.\n");
	if (HalHandlePageFault(r, context)) {
		return;
	}

	KeDisplayProgramFault("Page fault");
	HalDisplayDebugInfo(r);

	KeTerminateCurrentThread(RETURN_CODE_ON_PAGE_FAULT);
}

void KeNonMaskableInterrupt(void* r, void* context)
{
	HalReceivedNMI();
}

void KeOtherFault(void* r, void* context)
{
	KeDisplayProgramFault("Unhandled exception - CHECK KERNEL LOGS");
	HalDisplayDebugInfo(r);

	KeTerminateCurrentThread(RETURN_CODE_ON_OTHER_FAULT);
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

	KeTerminateCurrentThread(RETURN_CODE_ON_OPCODE_FAULT);
}

#pragma GCC diagnostic pop

#pragma GCC diagnostic pop

void KeDoubleFault(void* r, void* context)
{
	KePanic("DOUBLE FAULT");
}

