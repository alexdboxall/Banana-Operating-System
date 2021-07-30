#include "core/main.hpp"
#include "core/physmgr.hpp"
#include "core/virtmgr.hpp"
#include "core/kheap.hpp"
#include "dbg/kconsole.hpp"
#include "core/computer.hpp"
#include "krnl/hal.hpp"
#include "krnl/bootmsg.hpp"
#include "krnl/atexit.hpp"

#pragma GCC optimize ("O0")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

/*

Minimum System Requirements:

	CPU:	Intel 486 or better (Pentium recommended)
	RAM:	8 MB (16 MB to run the GUI)
	HDD:	64 MB

	VGA compatible video card;
	VGA compatible, or MDA monitor;
	USB or PS/2 keyboard

	If the computer was made in the 90s, you'll be fine
	If the computer was made in the 80s, it'll be more intersting
*/

extern "C" {
#include "libk/string.h"
}

uint32_t sysBootSettings = 0;
extern "C" void _init();
extern VAS* firstVAS;

#pragma GCC optimize ("O2")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")


extern "C" void KeEntryPoint()
{
	sysBootSettings = *((uint32_t*) 0x500);

	outb(0x3f8 + 1, 0x00);    // Disable all interrupts
	outb(0x3f8 + 3, 0x80);    // Enable DLAB (set baud rate divisor)
	outb(0x3f8 + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
	outb(0x3f8 + 1, 0x00);    //                  (hi byte)
	outb(0x3f8 + 3, 0x03);    // 8 bits, no parity, one stop bit
	outb(0x3f8 + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
	outb(0x3f8 + 4, 0x0B);    // IRQs enabled, RTS/DSR set

	kprintf("\n\nKERNEL HAS STARTED.\n");

	KeDisplaySplashScreen();

	Phys::physicalMemorySetup(((*((uint32_t*) 0x524)) + 4095) & ~0xFFF);		//cryptic one-liner
	Virt::virtualMemorySetup();

	KeInitialiseAtexit();

	{
		VAS v;
		firstVAS = &v;

		_init();

		computer = new Computer();
		computer->open(0, 0, &v);
	}
}
