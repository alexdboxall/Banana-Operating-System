#include "arch/i386/hal.hpp"
#include <hw/cpu.hpp>

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

uint64_t(*_i386_HAL_tscFunction)();

namespace Hal
{
	uint64_t noTSC()
	{
		return 0;
	}

	uint64_t readTSC()
	{
		uint64_t ret;
		asm volatile ("rdtsc" : "=A"(ret));
		return ret;
	}

	void initialise()
	{
		if (CPU::current()->features.hasTSC) {
			_i386_HAL_tscFunction = readTSC;

		}  else {
			_i386_HAL_tscFunction = noTSC;
		}
	}

	void makeBeep(int hertz)
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

	extern "C" void _i386_getRDRAND();
	uint32_t getRand()
	{
		//_i386_getRDRAND()

		return 0;
	}

	void endOfInterrupt();

	void restart();
	void shutdown();
	void sleep();
}