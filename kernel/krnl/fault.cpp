#include <krnl/panic.hpp>
#include <krnl/common.hpp>
#include <krnl/panic.hpp>
#include <krnl/fault.hpp>
#include <krnl/hal.hpp>
#include <sys/syscalls.hpp>
#include <thr/prcssthr.hpp>
#include <thr/elf.hpp>
#include <hal/intctrl.hpp>
#include <hal/device.hpp>

/// <summary>
/// Displays an error message on the screen and to the serial port.
/// </summary>
/// <param name="message">The message to output.</param>
void KeDisplayProgramFault(const char* message)
{
	kprintf(message);
	if (currentTaskTCB->processRelatedTo->terminal) {
		currentTaskTCB->processRelatedTo->terminal->puts(message, VgaColour::White, VgaColour::Maroon);
	}
}


/// <summary>
/// The kernel's handler to a general protection fault, to be called when an general protection fault occurs.
/// It may be hooked by HalHandleGeneralProtectionFault.
/// </summary>
/// <param name="registers">A pointer to a system specific data structure containing the CPU's state before the fault occured.</param>
/// <param name="context">Ignored here, except perhaps for a general protection fault hook, but it is required for the interrupt handler interface.</param>
void KeGeneralProtectionFault(void* registers, void* context)
{
	if (HalHandleGeneralProtectionFault(registers, context)) {
		return;
	}

	KeDisplayProgramFault("General protection fault");
	HalDisplayDebugInfo(registers);
	KeTerminateCurrentThread(RETURN_CODE_ON_GENERAL_PROTECTION_FAULT);
}


/// <summary>
/// The kernel's handler to a page fault, to be called when an page fault occurs.
/// </summary>
/// <param name="registers">A pointer to a system specific data structure containing the CPU's state before the fault occured.</param>
/// <param name="context">Ignored here, but it is required for the interrupt handler interface.</param>
void KePageFault(void* registers, void* context)
{
	if (HalHandlePageFault(registers, context)) {
		return;
	}

	KeDisplayProgramFault("Page fault");
	HalDisplayDebugInfo(registers);
	KeTerminateCurrentThread(RETURN_CODE_ON_PAGE_FAULT);
}


/// <summary>
/// The kernel's handler to a opcode fault, to be called when an opcode fault occurs.
/// </summary>
/// <param name="registers">A pointer to a system specific data structure containing the CPU's state before the fault occured.</param>
/// <param name="context">Ignored here, but it is required for the interrupt handler interface.</param>
void KeOpcodeFault(void* registers, void* context)
{
	if (HalHandleOpcodeFault(registers, context)) {
		return;
	}

	KeDisplayProgramFault("Opcode fault");
	HalDisplayDebugInfo(registers);
	KeTerminateCurrentThread(RETURN_CODE_ON_OPCODE_FAULT);
}


/// <summary>
/// The kernel's handler to miscellaneous faults, to be called when they occur.
/// </summary>
/// <param name="registers">A pointer to a system specific data structure containing the CPU's state before the fault occured.</param>
/// <param name="context">Ignored here, but it is required for the interrupt handler interface.</param>
void KeOtherFault(void* registers, void* context)
{
	KeDisplayProgramFault("Unhandled exception - CHECK KERNEL LOGS");
	HalDisplayDebugInfo(registers);
	KeTerminateCurrentThread(RETURN_CODE_ON_OTHER_FAULT);
}


/// <summary>
/// The kernel's handler to non maskable interrupts, to be called if a non-maskable interrupt occurs.
/// </summary>
/// <param name="registers">Ignored here, but it is required for the interrupt handler interface.</param>
/// <param name="context">Ignored here, but it is required for the interrupt handler interface.</param>
void KeNonMaskableInterrupt(void* registers, void* context)
{
	HalReceivedNMI();
}


/// <summary>
/// The kernel's handler to an unrecoverable double fault, to be called if a double fault occurs.
/// </summary>
/// <param name="registers">Ignored here, but it is required for the interrupt handler interface.</param>
/// <param name="context">Ignored here, but it is required for the interrupt handler interface.</param>
void KeDoubleFault(void* registers, void* context)
{
	KePanic("DOUBLE FAULT");
}
