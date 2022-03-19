
#include <krnl/main.hpp>
#include <krnl/bootflags.hpp>

/*
Stores flags regarding the configuration of how the kernel should run. These are set by the bootloader.
Don't access it manually, use KeGetBootConfigurationFlag instead. It is still public for compatibility by drivers.
These match the flags listed in the enum BootConfigurationFlag

Bit		Mask	Description
0		1		If true, disables the use of the APIC
1		2		If true, safe mode is enabled (does safe mode do anything?)
2		4		If false, forces the PS/2 keyboard driver to treat keypresses as scancode set 1
3		8		Must be 0
4		16		If true, the kernel's timer interrupt is slowed down from 100hz to 30hz, and also disables
				kernel logging through the serial port.
5		32		If true, CPU specific features will be enabled (e.g. UMIP, PSE, global pages, etc.)
6		64		Must be 0
7		128		If false and bit 11 is true, debug boot screen messages will require you to press enter before progressing
8		256		Must be 1
9		512		Must be 1
10		1024	If true, disables the use of ACPI and the APIC
11		2048	If true, displays debug screen messages, and puts the VGA driver into monochrome mode
12		4096	nothing???				vm86 debug??
13		8192	If true, the floppy disk driver will run if there is one detected
14		16384	nothing???				noFPUSaveLoad ??
15		32768	If true, enables remote setup (FORCED TO FALSE at the moment, sysinit/main.cpp, line 1324)
16+				reserved

*/
uint32_t keBootSettings = 0;


bool KeGetBootConfigurationFlag(BootConfigurationFlag flag)
{
	return keBootSettings & ((int) flag);
}

void KeInitialiseBootConfigurationFlags()
{
	// the bootloader puts the flags at the 4 byte at 0x500
	keBootSettings = *((uint32_t*) 0x500);
}