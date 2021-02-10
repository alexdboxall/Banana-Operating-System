#include "hw/video/vga.hpp"
#include "vm86/vm8086.hpp"
#include "fs/vfs.hpp"
#include "hw/ports.hpp"
#include "core/prcssthr.hpp"
#include "hal/intctrl.hpp"
#include "hw/cpu.hpp"

VGA::VGA() : Video("VGA Compatible Display")
{

}

int VGA::open(int a, int b, void* c)
{
	loadVM8086FileAsThread(kernelProcess, "C:/Banana/System/VGASET.COM", 0x0000, 0x90, 0x12, 0x12);

	width = 640;
	height = 480;

	mono = false;

	return 0;
}

int VGA::close(int a, int b, void* c)
{
	return 0;
}

void VGA::setPlane(int pl)
{
	outb(0x3CE, 4);
	outb(0x3CF, pl & 3);

	outb(0x3C4, 2);
	outb(0x3C5, 1 << (pl & 3));
}

void VGA::putpixel(int x, int y, uint32_t colour)
{
	uint8_t* vram = (uint8_t*) (VIRT_LOW_MEGS + 0xA0000);
	
	int addr = y * width + x;

	int bit = 7 - (addr & 7);
	addr >>= 3;

	int px = (x + y) & 1 ? 9 : 1;

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