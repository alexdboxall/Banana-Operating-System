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

		//Krnl::setBootMessage(message);

		if (guiMouseHandler) {
			CPU::current()->writeCR3(panicVAS->pageDirectoryBasePhysical);
			while (1);
			((void (*)(void))0x5000)();
		}
		
		//VgaText::hiddenOut = false;

		//give it those classic colours
		activeTerminal->setDefaultColours(VgaColour::White, VgaColour::Blue);
		activeTerminal->clearScreen();
		activeTerminal->setTitle((char*) "");
		activeTerminal->setDefaultColours(VgaColour::White, VgaColour::Blue);

		//print error message
		activeTerminal->puts("\n      FATAL SYSTEM ERROR\n\n");
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

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wframe-address"
		

		activeTerminal->puts("      Technical information:\n        ");
		activeTerminal->puts("    CR0: ");
		activeTerminal->putx(CPU::readCR0());
		activeTerminal->puts("    CR2: ");
		activeTerminal->putx(CPU::readCR2());
		activeTerminal->puts("\n            CR3: ");
		activeTerminal->putx(CPU::readCR3());
		activeTerminal->puts("    CR4: ");
		activeTerminal->putx(CPU::readCR4());
		activeTerminal->puts("\n            Callers: ");

		while (1);

		/*kprintf("0: 0x%X\n", __builtin_return_address(0));
		kprintf("1: 0x%X\n", __builtin_return_address(1));
		kprintf("2: 0x%X\n", __builtin_return_address(2));

		activeTerminal->putx((size_t) __builtin_return_address(0));
		activeTerminal->puts(", ");
		activeTerminal->putx((size_t) __builtin_return_address(1));
		activeTerminal->puts(", ");
		activeTerminal->putx((size_t) __builtin_return_address(2));*/

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