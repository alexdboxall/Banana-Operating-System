#include "debugger/debug.hpp"
#include "core/prcssthr.hpp"
#include "hw/ports.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wframe-address"

namespace Debug
{
	bool exceptionInDebugger = false;

	char debugExceptionNames[][32] = {
	"Division by zero error",
	"Debug",
	"Non-maskable interrupt",
	"Breakpoint",
	"Overflow",
	"Bound range exceeded",
	"Invalid opcode",
	"Device not available",
	"Dobule fault",
	"Coprocessor segment",
	"Invalid TSS",
	"Segment not present",
	"Stack segment fault",
	"General protection fault",
	"Page fault",
	"Reserved",
	"Floating point exception",
	"Alignment check",
	"Machine check",
	"SIMD floating-point exception",
	"Virtualisation exception",
	};


	bool askIfWantDump()
	{
		return true;

		bool resp = false;

		while (1) {
			char c = inb(0x60);
			if (c == 0x17 || c == 0x43) {
				goto gotResp;
			}
			if (c == 0x20 || c == 0x23) {
				resp = true;
				goto gotResp;
			}
		}

	gotResp:

		/*while (1) {
			char c = inb(0x60);
			if (!c) break;
		}*/

		return resp;
	}

	void pauseForEnter()
	{
		while (1) {
			char c = inb(0x60);
			if (c == 0x1C || c == 0x5A) {
				break;
			}
		}

		while (1) {
			char c = inb(0x60);
			if (!c) break;
		}

		return;
	}

	void dumpRegisters(regs* r)
	{
		size_t cr2;
		asm volatile ("mov %%cr2, %0" : "=r"(cr2));
		size_t cr3;
		asm volatile ("mov %%cr3, %0" : "=r"(cr3));
		kernelProcess->terminal->puts(" interrupt ", VgaColour::White, VgaColour::Teal);
		kernelProcess->terminal->putx(r->int_no);
		kernelProcess->terminal->puts(" (", VgaColour::White, VgaColour::Teal);
		kernelProcess->terminal->puts(debugExceptionNames[r->int_no], VgaColour::White, VgaColour::Teal);
		kernelProcess->terminal->puts(") ", VgaColour::White, VgaColour::Teal);
		kernelProcess->terminal->puts("\n eax: ", VgaColour::White, VgaColour::Teal);
		kernelProcess->terminal->putx(r->eax);
		kernelProcess->terminal->puts("\n ebx: ", VgaColour::White, VgaColour::Teal);
		kernelProcess->terminal->putx(r->ebx);
		kernelProcess->terminal->puts("\n ecx: ", VgaColour::White, VgaColour::Teal);
		kernelProcess->terminal->putx(r->ecx);
		kernelProcess->terminal->puts("\n edx: ", VgaColour::White, VgaColour::Teal);
		kernelProcess->terminal->putx(r->edx);
		kernelProcess->terminal->puts("\n esi: ", VgaColour::White, VgaColour::Teal);
		kernelProcess->terminal->putx(r->esi);
		kernelProcess->terminal->puts("\n edi: ", VgaColour::White, VgaColour::Teal);
		kernelProcess->terminal->putx(r->edi);
		kernelProcess->terminal->puts("\n esp: ", VgaColour::White, VgaColour::Teal);
		kernelProcess->terminal->putx(r->esp);
		kernelProcess->terminal->puts("\n  *u: ", VgaColour::White, VgaColour::Teal);
		kernelProcess->terminal->putx(r->useresp);
		kernelProcess->terminal->puts("\n ebp: ", VgaColour::White, VgaColour::Teal);
		kernelProcess->terminal->putx(r->ebp);
		kernelProcess->terminal->puts("\n eip: ", VgaColour::White, VgaColour::Teal);
		kernelProcess->terminal->putx(r->eip);
		kernelProcess->terminal->puts("\n cr2: ", VgaColour::White, VgaColour::Teal);
		kernelProcess->terminal->putx(cr2);
		kernelProcess->terminal->puts("\n cr3: ", VgaColour::White, VgaColour::Teal);
		kernelProcess->terminal->putx(cr3);
		kernelProcess->terminal->puts("\n err: ", VgaColour::White, VgaColour::Teal);
		kernelProcess->terminal->putx(r->err_code);
		kernelProcess->terminal->puts("\n cs: ", VgaColour::White, VgaColour::Teal);
		kernelProcess->terminal->putx(r->cs);
		kernelProcess->terminal->puts("  ds: ", VgaColour::White, VgaColour::Teal);
		kernelProcess->terminal->putx(r->ds);
		kernelProcess->terminal->puts("  es: ", VgaColour::White, VgaColour::Teal);
		kernelProcess->terminal->putx(r->es);
		kernelProcess->terminal->puts("  ss: ", VgaColour::White, VgaColour::Teal);
		kernelProcess->terminal->putx(r->ss);
		kernelProcess->terminal->puts("\n  fs: ", VgaColour::White, VgaColour::Teal);
		kernelProcess->terminal->putx(r->fs);
		kernelProcess->terminal->puts("  gs: ", VgaColour::White, VgaColour::Teal);
		kernelProcess->terminal->putx(r->gs);
		
		kernelProcess->terminal->puts("\n  eflags: ", VgaColour::White, VgaColour::Teal);
		kernelProcess->terminal->putx(r->eflags);
	}

	void handleFault(regs* r)
	{
		setActiveTerminal(kernelProcess->terminal);

		kernelProcess->terminal->puts("Exception ", VgaColour::White, VgaColour::Teal);
		kernelProcess->terminal->putx(r->int_no);
		kernelProcess->terminal->puts(" (", VgaColour::White, VgaColour::Teal);
		kernelProcess->terminal->puts(debugExceptionNames[r->int_no], VgaColour::White, VgaColour::Teal);
		kernelProcess->terminal->puts(") ", VgaColour::White, VgaColour::Teal);
		kernelProcess->terminal->puts("while debugging: Ignore / Dump", VgaColour::White, VgaColour::Teal);
		if (askIfWantDump()) {
			dumpRegisters(r);
			pauseForEnter();
		}
	}

	void displayFunctionCallers(int levels)
	{
		lockScheduler();
		exceptionInDebugger = true;

		kprintf("DBG: Callers to the function:\n");
		
		if (levels >= 1) kprintf("        0: 0x%X\n", (uint32_t) __builtin_return_address(0));
		if (levels >= 2) kprintf("        1: 0x%X\n", (uint32_t) __builtin_return_address(1));
		if (levels >= 3) kprintf("        2: 0x%X\n", (uint32_t) __builtin_return_address(2));
		if (levels >= 4) kprintf("        3: 0x%X\n", (uint32_t) __builtin_return_address(3));
		if (levels >= 5) kprintf("        4: 0x%X\n", (uint32_t) __builtin_return_address(4));
		if (levels >= 6) kprintf("        5: 0x%X\n", (uint32_t) __builtin_return_address(5));
		
		exceptionInDebugger = false;
		unlockScheduler();
	}
}

#pragma GCC diagnostic pop