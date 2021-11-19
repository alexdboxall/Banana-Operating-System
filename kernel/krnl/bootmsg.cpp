#include <krnl/common.hpp>
#include <krnl/bootmsg.hpp>
#include <krnl/hal.hpp>

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

void KeDisplaySplashScreen()
{
	for (int i = 0; "Starting Banana..."[i]; ++i) {
		HalConsoleWriteCharacter("Starting Banana..."[i], 0xF, 0x0, 2 + i, 1);
	}
}


void KeSetBootMessage(const char* msg)
{
	uint16_t vgatext[79];
	memset((void*) vgatext, 0, sizeof(vgatext));
	int xstart = (80 - strlen(msg)) / 2;
	for (int i = 0; msg[i]; ++i) {
		vgatext[xstart + i] = ((uint16_t) msg[i]) | 0x0700;
	}

	uint16_t* b = (uint16_t*) 0xC20B8000;
	memcpy(b + 80 * 20, vgatext, sizeof(vgatext));
	kprintf("\n--> msg: %s\n", msg);
	
	return;

	while (true) {
		uint8_t a = inb(0x60);
		if (a == 0x1C || a == 0x5A) {
			while (true) {
				a = inb(0x60);
				if (a != 0x1C && a != 0x5A) return;
			}
		}
	}
}