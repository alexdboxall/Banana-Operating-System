#include "hw/bus/ps2.hpp"
#include "hw/bus/ps2port.hpp"
#include "hw/mouse/ps2mouse.hpp"
#include "hw/ports.hpp"
#include "hw/acpi.hpp"
#include "core/main.hpp"
#include <stdint.h>

void (*guiMouseHandler) (int xdelta, int ydelta, int buttons, int z) = nullptr;

PS2Mouse::PS2Mouse() : Mouse("PS/2 Mouse")
{

}

void ps2MouseHandler(regs* r, void* context)
{
	((PS2Mouse*) context)->handler();
}

//this code was written long ago, and is quite bad
void PS2Mouse::handler()
{
	kprintf("Mouse handler.\n");
	//uint8_t status = inb(0x64);
	//if ((status & 1) == 0) return;		//no data
	//if ((status & 0x20) == 0) return;	//keyboard data

	mouse_bytes[cycle++] = inb(0x60);

	if (!(mouse_bytes[0] & 0x8)) {			//if the first mouse packet happens to be out of alignment (e.g. 2nd/3rd packet), reset it here
												//until we get it right (this code will be executed on each packet send until we get it right
		cycle = 0;
		return;
	}

	if ((mouseMode == 0 && cycle >= 3) || ((mouseMode == 3 || mouseMode == 4) && cycle >= 4)) {
		cycle = 0;
		kprintf("0x%X, 0x%X, 0x%X\n", mouse_bytes[0], mouse_bytes[1], mouse_bytes[2]);

		if ((mouse_bytes[0] & 0x80) || (mouse_bytes[0] & 0x40)) {
			cycle = 0;
			mouse_bytes[0] = 0;
			mouse_bytes[1] = 0;
			mouse_bytes[2] = 0;
			mouse_bytes[3] = 0;
			return;
		}

		//int xmove = mouse_bytes[0] & 0x10 ? -((int)mouse_bytes[1]) : mouse_bytes[1];
		//int ymove = mouse_bytes[0] & 0x20 ? mouse_bytes[2] : -((int) mouse_bytes[2]);

		int xmove = mouse_bytes[1] - ((mouse_bytes[0] << 4) & 0x100);
		int ymove = 0 - (mouse_bytes[2] - ((mouse_bytes[0] << 3) & 0x100));

		if (guiMouseHandler) {
			guiMouseHandler(xmove, ymove, mouse_bytes[0] & 1, 0);
		}
	}
}

int PS2Mouse::open(int a, int, void* ctrl)
{
	kprintf("PS2Mouse::open.\n");

	//store parents
	port = (PS2Port*) parent;
	controller = (PS2*) ctrl;

	port->deviceWrite(0xF6);
	port->deviceRead();

	port->deviceWrite(PS2_DEV_CMD_ENABLE_SCANNING);
	port->deviceRead();

	cycle = 0;
	mouseMode = 0;
	addIRQHandler(12, ps2MouseHandler, true, (void*) this);

	return 0;
}

int PS2Mouse::close(int a, int b, void* c)
{
	return 0;
}

void PS2Mouse::detect()
{
	return;
}