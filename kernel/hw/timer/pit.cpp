#include "hw/timer/pit.hpp"
#include "hal/intctrl.hpp"
#include "hw/ports.hpp"
#include "hw/acpi.hpp"
#include "core/common.hpp"

int pitFreq = 0;

void pitHandler(regs* r, void* context)
{
	timerHandler(10000 / pitFreq);
}

PIT::PIT() : Timer("Programmable Interrupt Timer")
{
	ports[noPorts].rangeStart = 0x40;
	ports[noPorts].rangeLength = 4;
	ports[noPorts++].width = 0;
}

int PIT::open(int hz, int, void*)
{
	write(hz);
	interrupt = addIRQHandler(0, pitHandler, true);

	return 0;
}

void PIT::write(int hz)
{
	frequency = hz; 
	pitFreq = hz;

	int divisor = 1193180 / hz;
	outb(0x43, 0x36);
	outb(0x40, divisor & 0xFF);
	outb(0x40, divisor >> 8);
}

int PIT::close(int a, int b, void* c)
{
	interrupt = -1;
	removeIRQHandler(0, pitHandler, true);
	return 0;
}
