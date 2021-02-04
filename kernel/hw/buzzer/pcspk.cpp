#include "core/main.hpp"
#include "hw/ports.hpp"
#include "hw/buzzer/pcspk.hpp"
#include <stdint.h>
//#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

Beep::Beep() : Buzzer("PC Speaker")
{
	ports[noPorts].rangeStart = 0x61;
	ports[noPorts].rangeLength = 1;
	ports[noPorts++].width = 0;

	ports[noPorts].rangeStart = 0x42;
	ports[noPorts].rangeLength = 2;
	ports[noPorts++].width = 0;
}

void Beep::start(int hertz)
{
	if (hertz == 0) {
		uint8_t tmp = inb(0x61) & 0xFC;
		outb(0x61, tmp);

	} else {
		uint32_t div = 1193180 / hertz;

		outb(0x43, 0xB6);
		outb(0x42, (uint8_t) (div));
		outb(0x42, (uint8_t) (div >> 8));

		uint8_t tmp = inb(0x61);
		if (tmp != (tmp | 3)) {
			outb(0x61, tmp | 3);
		}
	}
}

int Beep::open(int a, int b, void* c)
{
	return 0;
}

int Beep::close(int a, int b, void* c)
{
	return 0;
}
