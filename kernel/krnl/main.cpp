#include <krnl/main.hpp>
#include <krnl/physmgr.hpp>
#include <krnl/virtmgr.hpp>
#include <krnl/kheap.hpp>
#include <dbg/kconsole.hpp>
#include <krnl/computer.hpp>
#include <krnl/hal.hpp>
#include <krnl/bootmsg.hpp>
#include <krnl/atexit.hpp>
#include <krnl/bootflags.hpp>

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



extern "C" void _init();
extern VAS* keFirstVAS;

#pragma GCC optimize ("O2")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")


extern "C" void KeEntryPoint()
{
	// Store the boot configuration settings passed to us by the bootloader
	KeInitialiseBootConfigurationFlags();

	// Sets up the first serial port for kernel debugging at 37400 baud
#ifdef KERNEL_DEBUG
	outb(0x3F8 + 1, 0x00);
	outb(0x3F8 + 3, 0x80);
	outb(0x3F8 + 0, 0x03); 
	outb(0x3F8 + 1, 0x00);
	outb(0x3F8 + 3, 0x03);
	outb(0x3F8 + 2, 0xC7);
	outb(0x3F8 + 4, 0x0B);
#endif

	kprintf("\n\nKERNEL HAS STARTED.\n");
	KeDisplaySplashScreen();

	// The bootloader passes us the highest address used by the kernel image and other boot time things
	// in address 0x524. This is then rounded up to the nearest page, and used as the lowest address we
	// can start allocating from.
	Phys::physicalMemorySetup(((*((uint32_t*) 0x524)) + 4095) & ~0xFFF);
	Virt::virtualMemorySetup();

	KeInitialiseAtexit();

	{
		// Due to the nested scope, the VAS initialisation will only occur when
		// we get to here. Reaching this declaration actually sets up the VAS.
		VAS v;
		keFirstVAS = &v;

		// Call global constructors
		_init();

		// Start everything else up. Should never return from computer->open
		computer = new Computer();
		computer->open(0, 0, &v);
	}
}
