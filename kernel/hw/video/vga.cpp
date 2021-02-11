
#include "hw/video/vga.hpp"
#include "vm86/vm8086.hpp"
#include "fs/vfs.hpp"
#include "hw/ports.hpp"
#include "core/prcssthr.hpp"
#include "hal/intctrl.hpp"
#include "hw/cpu.hpp"

#pragma GCC optimize ("O0")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")


VGAVideo::VGAVideo() : Video("VGA Display")
{

}

void VGAVideo::setPlane(int pl)
{
	outb(0x3CE, 4);
	outb(0x3CF, pl & 3);

	outb(0x3C4, 2);
	outb(0x3C5, 1 << (pl & 3));
}

int VGAVideo::close(int a, int b, void* c)
{
	return 0;
}

int VGAVideo::open(int a, int b, void* c)
{
	loadVM8086FileAsThread(kernelProcess, "C:/Banana/System/VGASET.COM", 0x0000, 0x90, 0x12, 0x12);
	sleep(1);
	kprintf("loaded vm86 file.\n");

	width = 640;
	height = 480;

	mono = false;

	return 0;
}

uint8_t colLookup[4][4][4] = {
	{
		{0, 0, 1, 1},
		{2, 3, 3, 1},
		{2, 2, 3, 9},
		{10, 10, 11, 11},
	},
	{
		{4, 5, 5, 1},
		{6, 8, 8, 9},
		{2, 2, 3, 9},
		{10, 10, 11, 11},
	},
	{
		{4, 4, 5, 5},
		{6, 6, 13, 13},
		{6, 7, 7, 13},
		{10, 10, 14, 15},
	},
	{
		{12, 12, 13, 13},
		{12, 12, 13, 13},
		{12, 12, 13, 13},
		{14, 14, 15, 15},
	},
};

void VGAVideo::putrect(int x, int y, int w, int h, uint32_t colour)
{
	uint8_t red = (colour >> 22) & 3;
	uint8_t green = (colour >> 14) & 3;
	uint8_t blue = (colour >> 6) & 3;

	int px = colLookup[red][green][blue];

	int originalX = x;
	int maxY = y + h;
	int originalW = w;

	uint8_t* vram = (uint8_t*) (VIRT_LOW_MEGS + 0xA0000);

	for (; y < maxY; ++y) {
		x = originalX;
		w = originalW;
		while (w) {
			if (0 && !(x & 7) && w >= 8) {
				int addr = (y * width + x) >> 3;
				setPlane(0);
				vram[addr] = ((px >> 0) & 1) ? 0xFF : 0;
				setPlane(1);
				vram[addr] = ((px >> 1) & 1) ? 0xFF : 0;
				setPlane(2);
				vram[addr] = ((px >> 2) & 1) ? 0xFF : 0;
				setPlane(3);
				vram[addr] = ((px >> 3) & 1) ? 0xFF : 0;
				x += 8;
				w -= 8;

			} else {
				putpixel(x++, y, colour);
				--w;
			}
		}
	}
	
}

void VGAVideo::putpixel(int x, int y, uint32_t colour)
{
	uint8_t* vram = (uint8_t*) (VIRT_LOW_MEGS + 0xA0000);

	int addr = y * width + x;

	int bit = 7 - (addr & 7);
	addr >>= 3;

	uint8_t red = (colour >> 22) & 3;
	uint8_t green = (colour >> 14) & 3;
	uint8_t blue = (colour >> 6) & 3;

	int px = colLookup[red][green][blue];

	int w = ~(1 << bit);
	for (int i = 0; i < 4; ++i) {
		if (mono && i != 0) {
			px >>= 1;
			continue;
		}
		setPlane(i);
		vram[addr] = (vram[addr] & w) | ((px & 1) << bit);
		px >>= 1;
	}
}