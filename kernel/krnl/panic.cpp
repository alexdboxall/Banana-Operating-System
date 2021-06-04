#include "dbg/kconsole.hpp"
#include "core/common.hpp"
#include "thr/prcssthr.hpp"
#include "thr/elf.hpp"
#include "hw/cpu.hpp"
#include "krnl/hal.hpp"
#pragma GCC optimize ("O2")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")
#include "core/terminal.hpp"

#include "hal/mouse.hpp"

extern "C" void realmodeBSOD();
extern VAS* panicVAS;

namespace Krnl
{
	bool kernelInPanic = false;

	void (*guiPanicHandler)(char*) = nullptr;
	void (*guiProgramFaultHandler)();

	void panic(const char* message) {
		asm("cli");
		kernelInPanic = true;

		kprintf("\nFATAL SYSTEM ERROR: %s\n", message);
		
		//VgaText::hiddenOut = false;

		//give it those classic colours
		activeTerminal->setDefaultColours(VgaColour::White, VgaColour::Blue);
		activeTerminal->clearScreen();
		activeTerminal->setTitle((char*) "");
		activeTerminal->setDefaultColours(VgaColour::White, VgaColour::Blue);

		//print error message
		activeTerminal->puts("\n\n     ");
		activeTerminal->setDefaultColours(VgaColour::Blue, VgaColour::Whote);
		activeTerminal->puts(" STOP ERROR ");
		activeTerminal->setDefaultColours(VgaColour::White, VgaColour::Blue);
		activeTerminal->puts("\n\n");
		activeTerminal->puts("      A problem has occured and Banana cannot continue.\n\n");
		activeTerminal->puts("          ");
		activeTerminal->puts(message);
		activeTerminal->puts("\n\n");

		char* drvName = Thr::getDriverNameFromAddress((size_t) __builtin_return_address(0));
		if (drvName) {
			activeTerminal->puts("      The currently executing driver was:\n\n");
			activeTerminal->puts("          ");
			activeTerminal->puts(drvName);
		} else {
			activeTerminal->puts("      The currently executing task was:\n\n");
			activeTerminal->puts("          ");
			activeTerminal->puts(currentTaskTCB->processRelatedTo->taskname);
		}

		activeTerminal->puts("\n\n\n");
		activeTerminal->puts("      Please restart your computer or press RETURN. If this\n");
		activeTerminal->puts("      screen appears again, hold the 7 key on startup and disable\n");
		activeTerminal->puts("      APIC and ACPI.\n\n\n");

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