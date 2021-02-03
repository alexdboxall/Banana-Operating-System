#include "core/main.hpp"
#include "core/physmgr.hpp"
#include "core/virtmgr.hpp"
#include "core/kheap.hpp"
#include "core/kconsole.hpp"
#include "core/computer.hpp"
#include "hw/ports.hpp"
#pragma GCC optimize ("O0")

/*

Minimum System Requirements:

	CPU:	Intel 386 or better (hopefully, 486 is the oldest tested)
	RAM:	4 MB
	HDD:	64 MB

	VGA compatible video card
	USB or PS/2 keyboard

	If the computer was made in the 90s, you'll be fine
	If the computer was made in the 80s, it'll be more intersting
*/

extern "C" {
	#include "libk/string.h"
}

uint32_t sysBootSettings = 0;
extern "C" void callGlobalConstructors();
extern VAS* firstVAS;
extern void installVgaTextImplementation();

#define VGA_TEXT_MODE_ADDRESS 0xC20B8000

#pragma GCC optimize ("O2")

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
	uint16_t* ptr = (uint16_t*) VGA_TEXT_MODE_ADDRESS;
	for (int i = 0; i < 80; ++i) {
		*ptr++ = ((uint8_t) title[i]) | (((uint16_t) (((int) terminal->titleFg) & 0xF) | ((((int) terminal->titleCol) & 0xF) << 4)) << 8);
	}
}

void hwTextMode_scrollScreen(VgaText* terminal)
{
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
	uint16_t word = terminal->combineCharAndColour(c, terminal->combineColours((uint8_t) fg, (uint8_t) bg));
	uint16_t* ptr = (uint16_t*) VGA_TEXT_MODE_ADDRESS;
	ptr += (y * VgaText::width + x) + (25 - terminal->terminalDisplayHeight) * 80;
	*ptr = word;
}

void hwTextMode_showCursor(VgaText* terminal, bool show)
{
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
	uint16_t pos = terminal->cursorX + (terminal->cursorY + (25 - terminal->terminalDisplayHeight)) * VgaText::width;

	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void hwTextMode_disableBlink(VgaText* terminal, bool disable)
{
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

	PhysMem::physicalMemorySetup(highestFreeAddr);
	VirtMem::virtualMemorySetup();

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
