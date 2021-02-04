#include "core/kconsole.hpp"
#include "core/common.hpp"
#include "core/prcssthr.hpp"
#include "hw/cpu.hpp"
#include "hw/ports.hpp"
//#pragma GCC optimize ("O2")

bool kernelInPanic = false;

#ifdef JUMPER32
void panic(const char* _message)
{
	char message[128];
	strcpy(message, "JUMPER32: ");
	strcat(message, _message);
#else
void panic(const char* message)
{
#endif

	asm("cli");
	kernelInPanic = true;

	VgaText::hiddenOut = false;

	kprintf("\nFATAL SYSTEM ERROR: %s\n", message);

	setActiveTerminal(kernelProcess->terminal);

	//give it those classic colours
	kernelProcess->terminal->setDefaultColours(VgaColour::White, VgaColour::Blue);
	kernelProcess->terminal->clearScreen();

	//print error message
	kernelProcess->terminal->puts("\n      FATAL SYSTEM ERROR\n\n");
	kernelProcess->terminal->puts("      A problem has occured and Banana cannot continue.\n\n");
	kernelProcess->terminal->puts("          ");
	kernelProcess->terminal->puts(message);
	kernelProcess->terminal->puts("\n\n");
	kernelProcess->terminal->puts("      The currently executing task was:\n\n");
	kernelProcess->terminal->puts("          ");
	kernelProcess->terminal->puts(currentTaskTCB->processRelatedTo->taskname);
	kernelProcess->terminal->puts("\n\n\n");
	kernelProcess->terminal->puts("      Please restart your computer or press RETURN. If this\n");
	kernelProcess->terminal->puts("      screen appears again, hold the 7 key on startup and disable\n");
	kernelProcess->terminal->puts("      APIC and ACPI.\n\n\n");


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wframe-address"
	kprintf("0: 0x%X\n", __builtin_return_address(0));
	kprintf("1: 0x%X\n", __builtin_return_address(1));
	kprintf("2: 0x%X\n", __builtin_return_address(2));

	kernelProcess->terminal->puts("      Technical information:\n        ");
	kernelProcess->terminal->puts("    CR0: ");
	kernelProcess->terminal->putx(thisCPU()->readCR0());
	kernelProcess->terminal->puts("    CR2: ");
	kernelProcess->terminal->putx(thisCPU()->readCR2());
	kernelProcess->terminal->puts("\n            CR3: ");
	kernelProcess->terminal->putx(thisCPU()->readCR3());
	kernelProcess->terminal->puts("    CR4: ");
	kernelProcess->terminal->putx(thisCPU()->readCR4());
	kernelProcess->terminal->puts("\n            Callers: ");
	kernelProcess->terminal->putx((size_t) __builtin_return_address(0));
	kernelProcess->terminal->puts(", ");
	kernelProcess->terminal->putx((size_t) __builtin_return_address(1));
	kernelProcess->terminal->puts(", ");
	kernelProcess->terminal->putx((size_t) __builtin_return_address(2));

#pragma GCC diagnostic pop

	//endlessly loop
	while (1) {
		char c = inb(0x60);
		if (c == 0x1C || c == 0x5A) {
			uint8_t good = 0x02;
			while (good & 0x02) good = inb(0x64);
			outb(0x64, 0xFE);
			
			asm("cli; hlt");
		}
	}
}

void logs(char* a, VgaText* terminal);

char* stringifyxWithBase(uint32_t i, char b[], int base)
{
	char const digit[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

	if (base > 62) {
		base = 62;
	}
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
	va_list list;
	va_start(list, format);
	int i = 0;

	while (format[i]) {
		if (format[i] == '%') {
			switch (format[++i]) {
			case '%': logc('%'); break;
			case 'c': logc(va_arg(list, int)); break;
			case 's': logs(va_arg(list, char*)); break;

			case 'd':
			case 'h': logWriteInt(va_arg(list, signed)); break;

			case 'x': 
			case 'X': logWriteIntBase(va_arg(list, unsigned), 16); break;

			case 'l':
			case 'L': logWriteIntBase(va_arg(list, unsigned long long), 16); break;

			case 'b': 
			case 'w':
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