#include <stdint.h>

void start();
void begin()
{
	start();
}

#include "main.hpp"

#include "core/main.hpp"
#include "core/computer.hpp"
#include "core/terminal.hpp"
#include "core/physmgr.hpp"
#include "thr/prcssthr.hpp"
#include "reg/registry.hpp"
#include "hal/intctrl.hpp"
#include "hw/ports.hpp"
#include "hw/acpi.hpp"
#include "fs/vfs.hpp"

extern "C" {
	#include "libk/string.h"
}

namespace Krnl
{
	extern void (*biosPanicHandler)();
}

bool vgamono = false;
size_t VGA_TEXT_MODE_ADDRESS = 0xC20B8000;

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

#include <vm86/vm8086.hpp>

uint8_t biosbsod[1024];
int biosbsodLen; 

namespace Vm {
	bool start8086FromBuffer(uint8_t* buffer, int siz, uint16_t ip, uint16_t cs, uint16_t sp, uint16_t ss);
}

void bringBackToTextMode()
{
	kprintf("Dropping back to text mode!\n");
	Vm::start8086FromBuffer(biosbsod, biosbsodLen, 0x0000, 0x90, 0, 0);
	Vm::finish8086();
	kprintf("In text mode hopefully!\n");
}

#include <fs/vfs.hpp>

void setupTextMode()
{
	if (((*((uint16_t*) 0x410)) & 0x30) == 0x30) {
		VGA_TEXT_MODE_ADDRESS -= 0x8000;
		vgamono = true;
	}

	File* f = new File("C:/Banana/System/BIOSBSOD.COM", currentTaskTCB->processRelatedTo);
	FileStatus fs = f->open(FileOpenMode::Read);
	if (fs != FileStatus::Success) {
		panic("WHOA...");
	}
	int br;
	uint64_t siz;
	bool dir;
	biosbsodLen = siz;
	f->stat(&siz, &dir);
	f->read(siz, biosbsod, &br);
	kprintf("br = %d\n", br);
	f->close();

	Krnl::biosPanicHandler = bringBackToTextMode;

	textModeImplementation.disableBlink = hwTextMode_disableBlink;
	textModeImplementation.loadInData = hwTextMode_loadInData;
	textModeImplementation.loadInTitle = hwTextMode_loadInTitle;
	textModeImplementation.scrollScreen = hwTextMode_scrollScreen;
	textModeImplementation.showCursor = hwTextMode_showCursor;
	textModeImplementation.update = hwTextMode_update;
	textModeImplementation.updateCursor = hwTextMode_updateCursor;
	textModeImplementation.writeCharacter = hwTextMode_writeCharacter;
}

BIOS::BIOS(): Device ("Legacy BIOS")
{
	//claim ports
	/*ports[noPorts].rangeStart = ?;
	ports[noPorts].rangeLength = ?;
	ports[noPorts++].width = 0;*/

	//claim memory
	memory[noMems].rangeStart = 0x400;
	memory[noMems++].rangeLength = 0x100;

	memory[noMems].rangeStart = 0xC0000;
	memory[noMems++].rangeLength = 0x40000;

	//actually, not all of this is claimed by the BIOS, and Banana actually allocates part of this
	memory[noMems].rangeStart = 0x80000;
	memory[noMems++].rangeLength = 0x20000;
}

void start()
{
	BIOS* dev = new BIOS();
	Krnl::computer->addChild(dev);
	setupTextMode();
}


int BIOS::open(int, int, void*)
{
	return 0;
}

int BIOS::close(int, int, void*)
{
	return 0;
}
