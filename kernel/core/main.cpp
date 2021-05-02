#include "core/main.hpp"
#include "core/physmgr.hpp"
#include "core/virtmgr.hpp"
#include "core/kheap.hpp"
#include "dbg/kconsole.hpp"
#include "core/computer.hpp"
#include "hw/ports.hpp"

#pragma GCC optimize ("O0")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

/*

Minimum System Requirements:

	CPU:	Intel 386 or better (hopefully, 486 is the oldest tested)
	RAM:	6 MB (12 MB to install it)
	HDD:	64 MB

	VGA (or EGA) compatible video card;
	VGA (or EGA) compatible, or MDA monitor;
	USB or PS/2 keyboard

	If the computer was made in the 90s, you'll be fine
	If the computer was made in the 80s, it'll be more intersting
*/

/*

Kernel Subsystems

Krnl	Core Kernel
Phys	Physical Memory Manager
Virt	Virtual Memory Manager
Sys		System Calls
Thr		Processes, Threads, Program / Driver Loading
Hal		Hardware Abstraction Library
Dev		Device Subsystem
Dbg		Debugging
Fs		Filesystem
Reg		Registry
Vm		x86 Virtualisation
User	User settings, etc.

*/

extern "C" {
	#include "libk/string.h"
}

uint32_t sysBootSettings = 0;
extern "C" void callGlobalConstructors();
extern VAS* firstVAS;
extern void installVgaTextImplementation();

#pragma GCC optimize ("O2")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

extern "C" void kernel_main()
{
	outb(0x3f8 + 1, 0x00);    // Disable all interrupts
	outb(0x3f8 + 3, 0x80);    // Enable DLAB (set baud rate divisor)
	outb(0x3f8 + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
	outb(0x3f8 + 1, 0x00);    //                  (hi byte)
	outb(0x3f8 + 3, 0x03);    // 8 bits, no parity, one stop bit
	outb(0x3f8 + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
	outb(0x3f8 + 4, 0x0B);    // IRQs enabled, RTS/DSR set

	kprintf("\n\nKERNEL HAS STARTED.\n");

	installVgaTextImplementation();

	size_t highestFreeAddr = *((uint32_t*) 0x524);
	highestFreeAddr = (highestFreeAddr + 4095) & ~0xFFF;
	
	Phys::physicalMemorySetup(highestFreeAddr);
	Virt::virtualMemorySetup();

	uint32_t* dp = (uint32_t*) 0x500;
	uint32_t da = *dp++;
	uint32_t db = *dp++;

	if (da != db || (da & 0x348) != 0x300) {
		panic("");
	}

	sysBootSettings = da;
	{
		VAS v;
		firstVAS = &v;

		//needs memory to be set up before calling
		callGlobalConstructors();
		kprintf("global constructors called.\n");

		Virt::swappingSetup();

		computer = new Computer();
		kprintf("computer at 0x%X.\n", computer);

		computer->open(0, 0, nullptr);
	}

	panic("SCOPE ENDED IN KERNEL MAIN");
}
