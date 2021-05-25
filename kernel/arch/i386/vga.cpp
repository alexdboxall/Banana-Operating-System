#include "arch/i386/hal.hpp"
#include "arch/i386/pic.hpp"
#include "arch/i386/rtc.hpp"

#include <hw/cpu.hpp>
#include "vm86/x87em.hpp"
#include <krnl/panic.hpp>
#include <thr/prcssthr.hpp>

#include "core/common.hpp"
#include "krnl/panic.hpp"
#include "sys/syscalls.hpp"
#include "thr/prcssthr.hpp"
#include "thr/elf.hpp"
#include "hal/intctrl.hpp"
#include "hw/intctrl/pic.hpp"
#include "hw/intctrl/apic.hpp"
#include "hal/device.hpp"
#include "hw/acpi.hpp"
#include "krnl/hal.hpp"
#include "hw/cpu.hpp"
#include "vm86/vm8086.hpp"

#define VGA_TEXT_MODE_ADDRESS (VIRT_LOW_MEGS + 0xB8000)

namespace Hal {
	void consoleScroll(int fg, int bg)
	{
		uint8_t* ptr = (uint8_t*) VGA_TEXT_MODE_ADDRESS;
		for (int y = 2; y < 25; ++y) {
			for (int x = 0; x < 160; ++x) {
				ptr[y * 160 + x - 160] = ptr[y * 160 + x];
				if (y == 24) {
					if (x & 1) {
						ptr[y * 160 + x] = (fg & 0xF) | ((bg & 0xF) << 4);
					} else {
						ptr[y * 160 + x] = ' ';
					}
				}
			}
		}
	}

	void consoleWriteCharacter(char c, int fg, int bg, int x, int y)
	{
		uint16_t word = c | ((fg & 0xF) | ((bg & 0xF) << 4)) << 8;
		uint16_t* ptr = (uint16_t*) VGA_TEXT_MODE_ADDRESS;
		ptr += (y * 80 + x) + 80;
		*ptr = word;
	}

	void consoleCursorUpdate(int x, int y)
	{
		uint16_t pos = x + (y + 1) * 80;

		outb(0x3D4, 0x0F);
		outb(0x3D5, (uint8_t) (pos & 0xFF));
		outb(0x3D4, 0x0E);
		outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
	}
}