#include "dbg/kconsole.hpp"
#include "core/common.hpp"
#include "thr/prcssthr.hpp"
#include "thr/elf.hpp"
#include "hw/cpu.hpp"
#include "hw/ports.hpp"
#pragma GCC optimize ("O2")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

namespace Krnl
{
	bool kernelInPanic = false;

	void (*guiPanicHandler)();

	void panic(const char* message) {
		if (guiPanicHandler) {
			guiPanicHandler();
		}

		asm("cli");
		kernelInPanic = true;

		VgaText::hiddenOut = false;

		kprintf("\nFATAL SYSTEM ERROR: %s\n", message);

		setActiveTerminal(kernelProcess->terminal);

		//give it those classic colours
		kernelProcess->terminal->setDefaultColours(VgaColour::White, VgaColour::Blue);
		kernelProcess->terminal->clearScreen();

		//print error message
		kernelProcess->terminal->puts("\n      FATAL SYSTEM ERROR\n\n");
		kernelProcess->terminal->puts("      A problem has occured and Banana cannot continue.\n\n");
		kernelProcess->terminal->puts("          ");
		kernelProcess->terminal->puts(message);
		kernelProcess->terminal->puts("\n\n");
		kernelProcess->terminal->puts("      The currently executing task was:\n\n");
		kernelProcess->terminal->puts("          ");
		kernelProcess->terminal->puts(currentTaskTCB->processRelatedTo->taskname);

		kernelProcess->terminal->puts("\n\n\n");
		kernelProcess->terminal->puts("      Please restart your computer or press RETURN. If this\n");
		kernelProcess->terminal->puts("      screen appears again, hold the 7 key on startup and disable\n");
		kernelProcess->terminal->puts("      APIC and ACPI.\n\n\n");

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wframe-address"
		kprintf("0: 0x%X\n", __builtin_return_address(0));
		kprintf("1: 0x%X\n", __builtin_return_address(1));
		kprintf("2: 0x%X\n", __builtin_return_address(2));

		kernelProcess->terminal->puts("      Technical information:\n        ");
		kernelProcess->terminal->puts("    CR0: ");
		kernelProcess->terminal->putx(CPU::readCR0());
		kernelProcess->terminal->puts("    CR2: ");
		kernelProcess->terminal->putx(CPU::readCR2());
		kernelProcess->terminal->puts("\n            CR3: ");
		kernelProcess->terminal->putx(CPU::readCR3());
		kernelProcess->terminal->puts("    CR4: ");
		kernelProcess->terminal->putx(CPU::readCR4());
		kernelProcess->terminal->puts("\n            Callers: ");
		kernelProcess->terminal->putx((size_t) __builtin_return_address(0));
		kernelProcess->terminal->puts(", ");
		kernelProcess->terminal->putx((size_t) __builtin_return_address(1));
		kernelProcess->terminal->puts(", ");
		kernelProcess->terminal->putx((size_t) __builtin_return_address(2));

#pragma GCC diagnostic pop

		//endlessly loop
		while (1) {
			char c = inb(0x60);
			if (c == 0x1C || c == 0x5A) {
				uint8_t good = 0x02;
				while (good & 0x02) good = inb(0x64);
				outb(0x64, 0xFE);

				asm("cli; hlt");
			}
		}
	}

}