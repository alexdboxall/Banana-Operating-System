#include "dbg/kconsole.hpp"
#include "krnl/common.hpp"
#include "thr/prcssthr.hpp"
#include "thr/elf.hpp"
#include "hw/cpu.hpp"
#include "krnl/hal.hpp"

#pragma GCC optimize ("O2")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

namespace Dbg
{
	void logs(char* a, VgaText* terminal);

	char* stringifyxWithBase(uint32_t i, char b[], int base)
	{
		char const digit[] = "0123456789ABCDEF";

		char* p = b;
		uint32_t shifter = i;
		do { //Move to where representation ends
			++p;
			shifter = shifter / base;
		} while (shifter);
		*p = '\0';
		do { //Move back, inserting digits as u go
			*--p = digit[i % base];
			i = i / base;
		} while (i);
		return b;
	}

	void logc(char c)
	{
		if (keBootSettings & 16) return;
		while ((inb(0x3F8 + 5) & 0x20) == 0);
		outb(0x3F8, c);
	}

	void logs(char* a)
	{
		while (*a) logc(*a++);
	}

	void logWriteInt(uint32_t i)
	{
		char y[12];
		logs(stringifyxWithBase(i, y, 10));
	}

	void logWriteIntBase(uint32_t i, int base)
	{
		char y[12];
		logs(stringifyxWithBase(i, (char*) y, base));
	}

	void kprintf(const char* format, ...)
	{
#ifndef KERNEL_DEBUG
		return;
#endif
		if (format == nullptr) {
			kprintf("<< (nullptr) >>\n");
			return;
		}

		if (keBootSettings & 16) return;

		va_list list;
		va_start(list, format);
		int i = 0;

		while (format[i]) {
			if (format[i] == '%') {
				switch (format[++i]) {
				case '%': logc('%'); break;
				case 'c': logc(va_arg(list, int)); break;
				case 's': logs(va_arg(list, char*)); break;

				case 'd': logWriteInt(va_arg(list, signed)); break;

				case 'x':
				case 'X': logWriteIntBase(va_arg(list, unsigned), 16); break;

				case 'l':
				case 'L': logWriteIntBase(va_arg(list, unsigned long long), 16); break;

				case 'u': logWriteInt(va_arg(list, unsigned)); break;

				default: logc('%'); logc(format[i]); break;
				}
			} else {
				logc(format[i]);
			}
			i++;
		}

		va_end(list);
	}
}