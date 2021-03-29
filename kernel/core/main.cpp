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
	RAM:	4 MB (8 MB to install it)
	HDD:	64 MB

	VGA compatible video card
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
*/

extern "C" {
	#include "libk/string.h"
}

uint32_t sysBootSettings = 0;
extern "C" void callGlobalConstructors();
extern VAS* firstVAS;
extern void installVgaTextImplementation();

extern size_t VGA_TEXT_MODE_ADDRESS;

#pragma GCC optimize ("O2")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

void hwTextMode_loadInData(VgaText* terminal)
{
	uint16_t* ptr = (uint16_t*) VGA_TEXT_MODE_ADDRESS;
	ptr += 80;

	uint16_t* data = (uint16_t*) terminal->displayData;

	//load the display in
	for (int y = 0; y < terminal->terminalDisplayHeight; ++y) {
		for (int i = 0; i < 80; ++i) {
			*ptr++ = *data++;
		}
	}
}

void hwTextMode_loadInTitle(VgaText* terminal, char* title)
{
	if (vgamono) {
		terminal->titleFg = (VgaColour) 2;
		terminal->titleCol = (VgaColour) 0;
	}
	uint16_t* ptr = (uint16_t*) VGA_TEXT_MODE_ADDRESS;
	for (int i = 0; i < 80; ++i) {
		*ptr++ = ((uint8_t) title[i]) | (((uint16_t) (((int) terminal->titleFg) & 0xF) | ((((int) terminal->titleCol) & 0xF) << 4)) << 8);
	}
}

void hwTextMode_scrollScreen(VgaText* terminal)
{
	if (vgamono) {
		terminal->currentFg = (VgaColour) 2;
		terminal->currentBg = (VgaColour) 0;
	}
	uint8_t* ptr = (uint8_t*) VGA_TEXT_MODE_ADDRESS;
	for (int y = 2; y < 25; ++y) {
		for (int x = 0; x < 160; ++x) {
			ptr[y * 160 + x - 160] = ptr[y * 160 + x];
			if (y == 24) {
				if (x & 1) {
					ptr[y * 160 + x] = terminal->combineColours((uint8_t) terminal->currentFg, (uint8_t) terminal->currentBg);
				} else {
					ptr[y * 160 + x] = ' ';
				}
			}
		}
	}
}

void hwTextMode_writeCharacter(VgaText* terminal, char c, enum VgaColour fg, enum VgaColour bg, int x, int y)
{
	if (vgamono) {
		fg = (VgaColour) 2;
		bg = (VgaColour) 0;
	}
	uint16_t word = terminal->combineCharAndColour(c, terminal->combineColours((uint8_t) fg, (uint8_t) bg));
	uint16_t* ptr = (uint16_t*) VGA_TEXT_MODE_ADDRESS;
	if (vgamono) word = c | 0x200;
	ptr += (y * VgaText::width + x) + (25 - terminal->terminalDisplayHeight) * 80;
	*ptr = word;
}

void hwTextMode_showCursor(VgaText* terminal, bool show)
{
	if (vgamono) return;

	if (show) {
		outb(0x3D4, 0x0A);
		outb(0x3D5, (inb(0x3D5) & 0xC0) | (15 - terminal->cursorHeight));

		outb(0x3D4, 0x0B);
		outb(0x3D5, (inb(0x3D5) & 0xE0) | 15);

	} else {
		outb(0x3D4, 0x0A);
		outb(0x3D5, 0x20);
	}
}

void hwTextMode_update(VgaText* terminal)
{

}

void hwTextMode_updateCursor(VgaText* terminal)
{
	if (vgamono) return;

	uint16_t pos = terminal->cursorX + (terminal->cursorY + (25 - terminal->terminalDisplayHeight)) * VgaText::width;

	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void hwTextMode_disableBlink(VgaText* terminal, bool disable)
{
	if (vgamono) return;

	if (!disable) {           //enable
		inb(0x3DA);
		outb(0x3C0, 0x30);
		outb(0x3C0, inb(0x3C1) | 8);

	} else {            //disable
		inb(0x3DA);
		outb(0x3C0, 0x30);
		outb(0x3C0, inb(0x3C1) & 0xF7);
	}
}


void setupTextMode()
{
	extern bool vgamono;
	if (((*((uint16_t*) 0x410)) & 0x30) == 0x30) {
		VGA_TEXT_MODE_ADDRESS -= 0x8000;
		vgamono = true;
	}

	textModeImplementation.disableBlink = hwTextMode_disableBlink;
	textModeImplementation.loadInData = hwTextMode_loadInData;
	textModeImplementation.loadInTitle = hwTextMode_loadInTitle;
	textModeImplementation.scrollScreen = hwTextMode_scrollScreen;
	textModeImplementation.showCursor = hwTextMode_showCursor;
	textModeImplementation.update = hwTextMode_update;
	textModeImplementation.updateCursor = hwTextMode_updateCursor;
	textModeImplementation.writeCharacter = hwTextMode_writeCharacter;
}

extern "C" void kernel_main()
{
	installVgaTextImplementation();
	setupTextMode();

	outb(0x3f8 + 1, 0x00);    // Disable all interrupts
	outb(0x3f8 + 3, 0x80);    // Enable DLAB (set baud rate divisor)
	outb(0x3f8 + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
	outb(0x3f8 + 1, 0x00);    //                  (hi byte)
	outb(0x3f8 + 3, 0x03);    // 8 bits, no parity, one stop bit
	outb(0x3f8 + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
	outb(0x3f8 + 4, 0x0B);    // IRQs enabled, RTS/DSR set

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

		computer = new Computer();
		computer->open(0, 0, nullptr);
	}

	panic("SCOPE ENDED IN KERNEL MAIN");
}
