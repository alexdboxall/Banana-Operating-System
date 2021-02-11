#include "hw/bus/ps2bus.hpp"
#include "hw/bus/ps2port.hpp"
#include "hw/mouse/ps2mouse.hpp"
#include "hw/ports.hpp"
#include "hw/acpi.hpp"
#include "core/main.hpp"
#include <stdint.h>


PS2Mouse::PS2Mouse() : Mouse("PS/2 Mouse")
{

}

void PS2Mouse::configure()
{
	
}

void ps2MouseHandler(regs* r, void* context)
{
	((PS2Mouse*) context)->handler();
}

//this code was written long ago, and is quite bad
void PS2Mouse::handler()
{
	uint8_t status = inb(0x64);
	if ((status & 1) == 0) return;		//no data
	if ((status & 0x20) == 0) return;	//keyboard data

	mouse_bytes[cycle++] = inb(0x60);

	if (!(mouse_bytes[0] & 0x8)) {			//if the first mouse packet happens to be out of alignment (e.g. 2nd/3rd packet), reset it here
												//until we get it right (this code will be executed on each packet send until we get it right
		cycle = 0;
		return;
	}

	if ((mouseMode == 0 && cycle >= 3) || ((mouseMode == 3 || mouseMode == 4) && cycle >= 4)) {
		cycle = 0;

		if ((mouse_bytes[0] & 0x80) || (mouse_bytes[0] & 0x40)) {
			cycle = 0;
			mouse_bytes[0] = 0;
			mouse_bytes[1] = 0;
			mouse_bytes[2] = 0;
			mouse_bytes[3] = 0;
			return;
		}

		//???
		int xmove = mouse_bytes[1] - ((mouse_bytes[0] << 4) & 0x100);
		int ymove = 0 - (mouse_bytes[2] - ((mouse_bytes[0] << 3) & 0x100)));
		kprintf("MOUSE X: %d\nMOUSE Y: %d\n", xmove, ymove);
	}
}

int PS2Mouse::open(int a, int, void* ctrl)
{
	//store parents
	port = (PS2Port*) parent;
	controller = (PS2*) ctrl;

	cycle = 0;
	addIRQHandler(12, ps2MouseHandler, true, (void*) this);

	return 0;
}

int PS2Mouse::read(int a, int b, void* c)
{
	return 0;
}

int PS2Mouse::write(int command, int b, void* c)
{
	return 0;
}

int PS2Mouse::ioctl(int a, int b, void* c)
{
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

void PS2Mouse::hibernate()
{

}

void PS2Mouse::wake()
{

}

void PS2Mouse::disableLegacy()
{

}

void PS2Mouse::powerSaving(int level)
{

}