
#include "core/kheap.hpp"
#include "core/virtmgr.hpp"
#include "core/common.hpp"
#include "hw/cpu.hpp"
#include "hw/ports.hpp"
#include "hw/acpi.hpp"
#include "hal/timer.hpp"
#include "core/main.hpp"
#include "core/prcssthr.hpp"
#include "hal/intctrl.hpp"
#include <stdarg.h>

extern "C" {
#include "acpi.h"
#include "actypes.h"

#define FILE int
	//MOST OF THESE DON'T ACTUALLY EXIST, JUST HERE TO STOP THE COMPILER COMPLAINING
	//THAT WE DON'T HAVE THE HEADER FILE (THE DEFINITIONS ARE HIDDEN DEEP WITHIN ACPICA)

	void* memcpy(void*  destination, const void*  source, size_t n);
	void* memmove(void* destination, const void* source, size_t n);
	char* strcpy(char*  destination, const char*  source);
	char* strncpy(char*  destination, const char*  source, size_t n);
	char* strcat(char*  destination, const char*  source);
	char* strncat(char*  destination, const char*  source, size_t n);

	int memcmp(const void* s1, const void* s2, size_t n);
	int strcoll(const char* s1, const char* s2);
	int strcmp(const char* s1, const char* s2);
	int strncmp(const char* s1, const char* s2, size_t n);
	size_t strxfrm(char*  s1, const char*  s2, size_t n);

	int strcasecmp(const char* s1, const char* s2);
	int strncasecmp(const char* s1, const char* s2, size_t n);

	void* memchr(const void* s, int c, size_t n);
	char* strchr(const char* s, int c);
	char* strrchr(const char* s, int c);
	size_t strcspn(const char* s1, const char* s2);
	char* strpbrk(const char* s1, const char* s2);
	size_t strspn(const char* s1, const char* s2);
	char* strstr(const char* big, const char* small);
	char* strtok(char*  s, const char*  delim);

	void* memset(void* s, int c, size_t n);
	char* strerror(int errnum);
	size_t strlen(const char* s);

	//THESE DO EXIST
	int isalnum(int c);
	int isalpha(int c);
	int isblank(int c);
	int iscntrl(int c);
	int isdigit(int c);
	int isgraph(int c);
	int islower(int c);
	int isprint(int c);
	int isspace(int c);
	int isupper(int c);
	int isxdigit(int c);
	int ispunct(int c);

	int tolower(int c);
	int toupper(int c);


	int isalnum(int c)
	{
		return isalpha(c) || isdigit(c);
	}

	int isalpha(int c)
	{
		//outside of the "C" locale, any other character
		//may be included as long as it isn't in
		//iscntrl, isdigit, ispunct, or isspace

		return isupper(c) || islower(c);
	}

	int isblank(int c)
	{
		return c == ' ' || c == '\t';
	}

	int iscntrl(int c)
	{
		return c < ' ' || c == 0x7F;
	}

	int isdigit(int c)
	{
		return c >= '0' && c <= '9';
	}

	int isgraph(int c)
	{
		return isalnum(c) || ispunct(c);
	}

	int islower(int c)
	{
		return c >= 'a' && c <= 'z';
	}

	int isprint(int c)
	{
		return isgraph(c) || c == ' ';
	}

	int ispunct(int c)
	{
		return !(isalnum(c) || isspace(c) || iscntrl(c));
	}

	int isspace(int c)
	{
		switch (c) {
		case ' ':
		case '\t':
		case '\n':
		case '\r':
		case '\v':
		case '\f':
			return 1;
		}
		return 0;
	}

	int isupper(int c)
	{
		return c >= 'A' && c <= 'Z';
	}

	int isxdigit(int c)
	{
		return isdigit(c) || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f');
	}

#ifndef JUMPER32
	ACPI_STATUS AcpiOsInitialize()
	{
		return AE_OK;
	}

	ACPI_STATUS AcpiOsTerminate()
	{
		return AE_OK;
	}

	ACPI_PHYSICAL_ADDRESS AcpiOsGetRootPointer()
	{
		ACPI_PHYSICAL_ADDRESS  Ret;
		Ret = 0;
#ifndef JUMPER32
		AcpiFindRootPointer(&Ret);
#endif
		return Ret;
	}

	ACPI_STATUS AcpiOsPredefinedOverride(const ACPI_PREDEFINED_NAMES* PredefinedObject, ACPI_STRING* NewValue)
	{
		if (!PredefinedObject || !NewValue) {
			return AE_BAD_PARAMETER;
		}

		*NewValue = NULL;
		return AE_OK;
	}

	ACPI_STATUS AcpiOsTableOverride(ACPI_TABLE_HEADER* ExistingTable, ACPI_TABLE_HEADER** NewTable)
	{
		*NewTable = NULL;
		return AE_OK;
	}

	ACPI_STATUS AcpiOsPhysicalTableOverride(ACPI_TABLE_HEADER* ExistingTable, ACPI_PHYSICAL_ADDRESS* NewAddress, UINT32* NewTableLength)
	{
		*NewAddress = 0;
		return AE_OK;
	}

	ACPI_STATUS AcpiOsReadPort(ACPI_IO_ADDRESS Address, UINT32* Value, UINT32 Width)
	{
		if (Width == 8) *Value = inb(Address);
		else if (Width == 16) *Value = inw(Address);
		else if (Width == 32) *Value = inl(Address);
		else return AE_BAD_PARAMETER;
		return AE_OK;
	}

	ACPI_STATUS AcpiOsWritePort(ACPI_IO_ADDRESS Address, UINT32 Value, UINT32 Width)
	{
		if (Width == 8) outb(Address, (uint8_t) Value);
		else if (Width == 16) outw(Address, (uint16_t) Value);
		else if (Width == 32) outl(Address, Value);
		else return AE_BAD_PARAMETER;
		return AE_OK;
	}

	UINT64 AcpiOsGetTimer(void)
	{
		return nanoSinceBoot / 100;
	}

	void AcpiOsWaitEventsComplete(void)
	{
		panic("AcpiOsWaitEventsComplete");
	}

	//https://github.com/no92/vineyard/blob/dev/kernel/driver/acpi/osl/pci.c
	ACPI_STATUS AcpiOsReadPciConfiguration(ACPI_PCI_ID* PciId, UINT32 Register, UINT64* Value, UINT32 Width)
	{
		uint32_t regAligned = Register & ~0x03U;
		uint32_t offset = Register & 0x03U;
		uint32_t addr = (uint32_t) ((uint32_t) (PciId->Bus << 16) | (uint32_t) (PciId->Device << 11) | (uint32_t) (PciId->Function << 8) | ((uint32_t) 0x80000000) | regAligned);

		outl(0xCF8, addr);

		uint32_t ret = inl(0xCFC);

		void* res = (char*) &ret + offset;
		size_t count = Width >> 3;
		*Value = 0;

		memcpy(Value, res, count);

		return AE_OK;
	}

	ACPI_STATUS AcpiOsWritePciConfiguration(ACPI_PCI_ID* PciId, UINT32 Register, UINT64 Value, UINT32 Width)
	{
		
		uint32_t addr = (uint32_t) ((uint32_t) (PciId->Bus << 16) | (uint32_t) (PciId->Device << 11) | (uint32_t) (PciId->Function << 8) | ((uint32_t) 0x80000000));
		addr += Register;

		outl(0xCF8, addr);

		switch (Width) {
		case 8:
			outb(0xCFC, Value & 0xFF);
			break;
		case 16:
			outw(0xCFC, Value & 0xFFFF);
			break;
		case 32:
			outl(0xCFC, Value & 0xFFFFFFFF);
			break;
		default:
			panic("[acpica osl] AcpiOsWritePciConfiguration bad width!");
			break;
		}

		return AE_OK;

	}

	ACPI_STATUS AcpiOsSignal(UINT32 Function, void* Info)
	{
		switch (Function) {
		case ACPI_SIGNAL_FATAL:
			panic("[acpi]	AML fatal opcode");
			break;
		case ACPI_SIGNAL_BREAKPOINT:
			//kprintf("[acpi]	AML breakpoint\n");
			break;
		default:
			return AE_BAD_PARAMETER;
		}

		return AE_OK;
	}

	ACPI_STATUS AcpiOsReadMemory(ACPI_PHYSICAL_ADDRESS Address, UINT64* Value, UINT32 Width)
	{
		panic("Read Memory...\n");
		if (Width == 8) {
			uint8_t* a = (uint8_t*) (size_t) Address;
			*Value = *a;
		}
		else if (Width == 16) {
			uint16_t* a = (uint16_t*) (size_t) Address;
			*Value = *a;
		}
		else if (Width == 32) {
			uint32_t* a = (uint32_t*) (size_t) Address;
			*Value = *a;
		}
		else if (Width == 64) {
			uint64_t* a = (uint64_t*) (size_t) Address;
			*Value = *a;
		}
		else return AE_BAD_PARAMETER;
		return AE_OK;
	}

	ACPI_STATUS AcpiOsEnterSleep(UINT8 SleepState, UINT32 RegaValue, UINT32 RegbValue)
	{
		return AE_OK;
	}

	ACPI_STATUS AcpiOsWriteMemory(ACPI_PHYSICAL_ADDRESS Address, UINT64 Value, UINT32 Width)
	{
		panic("Write Memory...\n");

		if (Width == 8) {
			uint8_t* a = (uint8_t*) (size_t) Address;
			*a = Value;
		}
		else if (Width == 16) {
			uint16_t* a = (uint16_t*) (size_t) Address;
			*a = Value;
		}
		else if (Width == 32) {
			uint32_t* a = (uint32_t*) (size_t) Address;
			*a = Value;
		}
		else if (Width == 64) {
			uint64_t* a = (uint64_t*) (size_t) Address;
			*a = Value;
		}
		else return AE_BAD_PARAMETER;
		return AE_OK;
	}

	void* AcpiOsMapMemory(ACPI_PHYSICAL_ADDRESS PhysicalAddress, ACPI_SIZE Length)
	{
		bool invlpg = thisCPU()->features.hasINVLPG;
		
		int pages = (Length + 4096) / 4096;
		size_t virt = VirtMem::allocateKernelVirtualPages(pages);

		for (int i = 0; i < pages; ++i) {
			VirtMem::getAKernelVAS()->mapPage((PhysicalAddress & ~0xFFF) + i * 4096, virt + i * 4096, PAGE_PRESENT | PAGE_SUPERVISOR);
			
			if (invlpg) {
				asm volatile ("invlpg (%0)" : : "b"((void*) (virt + i * 4096)) : "memory");
			}
		}
		
		if (!invlpg) {
			thisCPU()->writeCR3(thisCPU()->readCR3());
		}

		return (void*) (virt | (PhysicalAddress & 0xFFF));
	}

	void AcpiOsUnmapMemory(void* where, ACPI_SIZE length)
	{
		//VirtMem::getCurrent()->freeAllocatedPages(((size_t) where) & ~0xFFF);
	}

	ACPI_STATUS AcpiOsGetPhysicalAddress(void* LogicalAddress, ACPI_PHYSICAL_ADDRESS* PhysicalAddress)
	{
		*PhysicalAddress = VirtMem::getAKernelVAS()->virtualToPhysical((size_t) LogicalAddress);
		return AE_OK;
	}

	void* AcpiOsAllocate(ACPI_SIZE Size)
	{
		void* v = malloc(Size);
		return v;
	}

	void AcpiOsFree(void* Memory)
	{
		free(Memory);
	}

	BOOLEAN AcpiOsReadable(void* Memory, ACPI_SIZE Length)
	{
		kprintf("AcpiOsReadable\n");
		return true;
	}

	BOOLEAN AcpiOsWritable(void* Memory, ACPI_SIZE Length)
	{
		kprintf("AcpiOsWritable\n");
		return true;
	}

	ACPI_THREAD_ID AcpiOsGetThreadId()
	{
		//kprintf("AcpiOsGetThreadId\n");
		return 1;	// currentTaskTCB->rtid + 1;
	}

	ACPI_STATUS AcpiOsExecute(ACPI_EXECUTE_TYPE Type, ACPI_OSD_EXEC_CALLBACK Function, void* Context)
	{
		panic("TODO: PUT CONTEXT ON THE STACK AcpiOsExecute");
		//createKernelThread(kernelProcess, (void(*)()) Function, 128);
		return AE_OK;
	}

	void AcpiOsSleep(UINT64 Milliseconds)
	{
		nanoSleep(Milliseconds * 1000 * 1000);
	}

	void AcpiOsStall(UINT32 Microseconds)
	{
		uint64_t end = nanoSinceBoot + ((UINT64) Microseconds * 1000);
		while (nanoSinceBoot < end) {

		}
	}

	ACPI_STATUS AcpiOsCreateSemaphore(UINT32 MaxUnits, UINT32 InitialUnits, ACPI_SEMAPHORE* OutHandle)
	{
		//kprintf("TODO: AcpiOsCreateSemaphore\n");

		Semaphore* s = new Semaphore(InitialUnits);
		s->currentCount = 0;
		*OutHandle = s;

		return AE_OK;
	}

	ACPI_STATUS AcpiOsDeleteSemaphore(ACPI_SEMAPHORE Handle)
	{
		//kprintf("AcpiOsDeleteSemaphore\n");

		delete (Semaphore*) Handle;
		return AE_OK;
	}

	ACPI_STATUS AcpiOsWaitSemaphore(ACPI_SEMAPHORE Handle, UINT32 Units, UINT16 Timeout)
	{
		//kprintf("TODO: AcpiOsWaitSemaphore\n");

		if (Units > 1) {
			return AE_SUPPORT;
		}

		if (Timeout == 0xFFFF) {
			((Semaphore*) Handle)->acquire();
		} else {
			uint64_t startNano = nanoSinceBoot;
			uint64_t extra = ((uint64_t) Timeout) * 1000 * 1000;

			while (nanoSinceBoot < startNano + extra) {
				bool success = ((Semaphore*) Handle)->tryAcquire();
				if (success) return AE_OK;
			}
			return AE_TIME;
		}
		
		return AE_OK;
	}

	ACPI_STATUS AcpiOsSignalSemaphore(ACPI_SEMAPHORE Handle, UINT32 Units)
	{
		//kprintf("TODO: AcpiOsSignalSemaphore\n");

		if (Units > 1) {
			return AE_SUPPORT;
		}
		((Semaphore*) Handle)->release();
		return AE_OK;
	}

	ACPI_STATUS AcpiOsCreateLock(ACPI_SPINLOCK* OutHandle)
	{
		//kprintf("AcpiOsCreateLock\n");

		*OutHandle = (ACPI_SPINLOCK*) malloc(4);
		*((int*) *OutHandle) = 0;

		return AE_OK;
	}

	void AcpiOsDeleteLock(ACPI_HANDLE Handle)
	{
		//kprintf("TODO: AcpiOsDeleteLock\n");
	}

	ACPI_CPU_FLAGS AcpiOsAcquireLock(ACPI_SPINLOCK Handle)
	{
		extern unsigned long asmQuickAcquireLock(size_t*);
		extern unsigned long asmAcquireLock(size_t*);

		return asmAcquireLock((size_t*) Handle);
	}

	void AcpiOsReleaseLock(ACPI_SPINLOCK Handle, ACPI_CPU_FLAGS Flags)
	{
		extern void asmReleaseLock(size_t*, size_t);
		extern void asmQuickReleaseLock(size_t*);

		asmReleaseLock((size_t*) Handle, Flags);
	}

	void Subhandler(struct regs* rgs, void* context)
	{
		size_t* ctx = (size_t*) context;
		size_t c = ctx[0];
		void(*f)(struct regs*, void*) = (void(*)(struct regs*, void*))c;
		f(rgs, (void*) ctx[1]);
	}

	ACPI_STATUS AcpiOsInstallInterruptHandler(UINT32 InterruptLevel, ACPI_OSD_HANDLER Handler, void* Context)
	{
		size_t* ctx = (size_t*) malloc(sizeof(size_t) * 2);
		ctx[0] = reinterpret_cast<size_t>(Handler);
		ctx[1] = (size_t) Context;

		thisCPU()->intCtrl->installIRQHandler(InterruptLevel, (void(*)(struct regs*, void*))Subhandler, false, ctx);
		return AE_OK;
	}

	ACPI_STATUS AcpiOsRemoveInterruptHandler(UINT32 InterruptNumber, ACPI_OSD_HANDLER Handler)
	{
		panic("AcpiOsRemoveInterruptHandler");
		return AE_OK;
	}

	char* __i__int_str(intmax_t i, char b[], int base, bool plusSignIfNeeded, bool spaceSignIfNeeded,
					   int paddingNo, bool justify, bool zeroPad)
	{

		if (justify && zeroPad) {
			zeroPad = false;
		}

		char digit[32] = { 0 };
		memset(digit, 0, 32);
		strcpy(digit, "0123456789");

		if (base == 16) {
			strcat(digit, "ABCDEF");
		} else if (base == 17) {
			strcat(digit, "abcdef");
			base = 16;
		}

		char* p = b;
		if (i < 0) {
			*p++ = '-';
			i *= -1;
		} else if (plusSignIfNeeded) {
			*p++ = '+';
		} else if (!plusSignIfNeeded && spaceSignIfNeeded) {
			*p++ = ' ';
		}

		intmax_t shifter = i;
		do {
			++p;
			shifter = shifter / base;
		} while (shifter);

		*p = '\0';
		do {
			*--p = digit[i % base];
			i = i / base;
		} while (i);

		int padding = paddingNo - (int) strlen(b);
		if (padding < 0) padding = 0;

		if (justify) {
			while (padding--) {
				if (zeroPad) {
					b[strlen(b)] = '0';
				} else {
					b[strlen(b)] = ' ';
				}
			}

		} else {
			char a[256] = { 0 };
			while (padding--) {
				if (zeroPad) {
					a[strlen(a)] = '0';
				} else {
					a[strlen(a)] = ' ';
				}
			}
			strcat(a, b);
			strcpy(b, a);
		}

		return b;
	}

	void __i_displayCharacter(char c, int* a, FILE*  stream, char* buffer, int size)
	{
		while ((inb(0x3F8 + 5) & 0x20) == 0);
		outb(0x3F8, c);

		*a += 1;
	}

	void __i_displayString(char* c, int* a, FILE*  stream, char* buffer, int size)
	{
		for (int i = 0; c[i]; ++i) {
			__i_displayCharacter(c[i], a, stream, buffer, size);
		}
	}

	int __i_internal_printf(const char*  format, va_list list, FILE* stream, char* buffer, int size)
	{
		return 0;

		/*int chars = 0;
		char intStrBuffer[256] = { 0 };

		char plainCharBuffer[1024] = { 0 };
		plainCharBuffer[0] = 0;

		for (int i = 0; format[i]; ++i) {

			char specifier = '\0';
			char length = '\0';

			int  lengthSpec = 0;
			int  precSpec = 0;
			bool leftJustify = false;
			bool zeroPad = false;
			bool spaceNoSign = false;
			bool altForm = false;
			bool plusSign = false;
			bool emode = false;
			int  expo = 0;

			if (format[i] == '%') {
				if (strlen(plainCharBuffer)) {
					__i_displayString(plainCharBuffer, &chars, stream, buffer, size);
					plainCharBuffer[0] = 0;
				}
				++i;

				bool extBreak = false;
				while (1) {

					switch (format[i]) {
					case '-':
						leftJustify = true;
						++i;
						break;

					case '+':
						plusSign = true;
						++i;
						break;

					case '#':
						altForm = true;
						++i;
						break;

					case ' ':
						spaceNoSign = true;
						++i;
						break;

					case '0':
						zeroPad = true;
						++i;
						break;

					default:
						extBreak = true;
						break;
					}

					if (extBreak) break;
				}

				while (isdigit(format[i])) {
					lengthSpec *= 10;
					lengthSpec += format[i] - 48;
					++i;
				}

				if (format[i] == '*') {
					lengthSpec = va_arg(list, int);
					if (lengthSpec < 0) {
						lengthSpec = 0 - lengthSpec;
						leftJustify = true;
					}
					++i;
				}

				if (format[i] == '.') {
					++i;
					while (isdigit(format[i])) {
						precSpec *= 10;
						precSpec += format[i] - 48;
						++i;
					}

					if (format[i] == '*') {
						precSpec = va_arg(list, int);
						if (precSpec < 0) {
							precSpec = 6;       //defaut value
						}
						++i;
					}
				} else {
					precSpec = 6;
				}

				if (format[i] == 'h' || format[i] == 'l' || format[i] == 'j' ||
					format[i] == 'z' || format[i] == 't' || format[i] == 'L') {
					length = format[i];
					++i;

					if (format[i] == 'h') {
						length = 'H';
						++i;
					} else if (format[i] == 'l') {
						length = 'q';
						++i;
					}
				}
				specifier = format[i];

				memset(intStrBuffer, 0, 256);

				int base = 10;
				if (specifier == 'o') {
					base = 8;
					specifier = 'u';
					if (altForm) {
						__i_displayString((char*) "0", &chars, stream, buffer, size);
					}
				}
				if (specifier == 'p') {
					base = 16;
					length = 'z';
					specifier = 'u';
				}

				switch (specifier) {
				case 'X':
					base = 16;
					__attribute__((fallthrough));
				case 'x':
					base = base == 10 ? 17 : base;
					if (altForm) {
						__i_displayString((char*) "0x", &chars, stream, buffer, size);
					}
					__attribute__((fallthrough));
				case 'u':
				{
					switch (length) {
					case 0:
					{
						unsigned int integer = va_arg(list, unsigned int);
						__i__int_str(integer, intStrBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
						__i_displayString(intStrBuffer, &chars, stream, buffer, size);
						break;
					}
					case 'H':
					{
						unsigned char integer = (unsigned char) va_arg(list, unsigned int);
						__i__int_str(integer, intStrBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
						__i_displayString(intStrBuffer, &chars, stream, buffer, size);
						break;
					}
					case 'h':
					{
						unsigned short int integer = va_arg(list, unsigned int);
						__i__int_str(integer, intStrBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
						__i_displayString(intStrBuffer, &chars, stream, buffer, size);
						break;
					}
					case 'l':
					{
						unsigned long integer = va_arg(list, unsigned long);
						__i__int_str(integer, intStrBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
						__i_displayString(intStrBuffer, &chars, stream, buffer, size);
						break;
					}
					case 'q':
					{
						unsigned long long integer = va_arg(list, unsigned long long);
						__i__int_str(integer, intStrBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
						__i_displayString(intStrBuffer, &chars, stream, buffer, size);
						break;
					}
					case 'j':
					{
						uintmax_t integer = va_arg(list, uintmax_t);
						__i__int_str(integer, intStrBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
						__i_displayString(intStrBuffer, &chars, stream, buffer, size);
						break;
					}
					case 'z':
					{
						size_t integer = va_arg(list, size_t);
						__i__int_str(integer, intStrBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
						__i_displayString(intStrBuffer, &chars, stream, buffer, size);
						break;
					}
					case 't':
					{
						ptrdiff_t integer = va_arg(list, ptrdiff_t);
						__i__int_str(integer, intStrBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
						__i_displayString(intStrBuffer, &chars, stream, buffer, size);
						break;
					}
					default:
						break;
					}
					break;
				}

				case 'd':
				case 'i':
				{
					switch (length) {
					case 0:
					{
						int integer = va_arg(list, int);
						__i__int_str(integer, intStrBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
						__i_displayString(intStrBuffer, &chars, stream, buffer, size);
						break;
					}
					case 'H':
					{
						signed char integer = (signed char) va_arg(list, int);
						__i__int_str(integer, intStrBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
						__i_displayString(intStrBuffer, &chars, stream, buffer, size);
						break;
					}
					case 'h':
					{
						short int integer = va_arg(list, int);
						__i__int_str(integer, intStrBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
						__i_displayString(intStrBuffer, &chars, stream, buffer, size);
						break;
					}
					case 'l':
					{
						long integer = va_arg(list, long);
						__i__int_str(integer, intStrBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
						__i_displayString(intStrBuffer, &chars, stream, buffer, size);
						break;
					}
					case 'q':
					{
						long long integer = va_arg(list, long long);
						__i__int_str(integer, intStrBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
						__i_displayString(intStrBuffer, &chars, stream, buffer, size);
						break;
					}
					case 'j':
					{
						intmax_t integer = va_arg(list, intmax_t);
						__i__int_str(integer, intStrBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
						__i_displayString(intStrBuffer, &chars, stream, buffer, size);
						break;
					}
					case 'z':
					{
						size_t integer = va_arg(list, size_t);
						__i__int_str(integer, intStrBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
						__i_displayString(intStrBuffer, &chars, stream, buffer, size);
						break;
					}
					case 't':
					{
						ptrdiff_t integer = va_arg(list, ptrdiff_t);
						__i__int_str(integer, intStrBuffer, base, plusSign, spaceNoSign, lengthSpec, leftJustify, zeroPad);
						__i_displayString(intStrBuffer, &chars, stream, buffer, size);
						break;
					}
					default:
						break;
					}
					break;
				}

				case 'c':
				{
					if (length == 'l') {
						//__i_displayCharacter(va_arg(list, wint_t), &chars, stream, buffer, size);
					} else {
						__i_displayCharacter(va_arg(list, int), &chars, stream, buffer, size);
					}

					break;
				}

				case 's':
				{
					__i_displayString(va_arg(list, char*), &chars, stream, buffer, size);
					break;
				}

				case 'n':
				{
					switch (length) {
					case 'H':
						*(va_arg(list, signed char*)) = chars;
						break;
					case 'h':
						*(va_arg(list, short int*)) = chars;
						break;

					case 0:
					{
						int* a = va_arg(list, int*);
						*a = chars;
						break;
					}

					case 'l':
						*(va_arg(list, long*)) = chars;
						break;
					case 'q':
						*(va_arg(list, long long*)) = chars;
						break;
					case 'j':
						*(va_arg(list, intmax_t*)) = chars;
						break;
					case 'z':
						*(va_arg(list, size_t*)) = chars;
						break;
					case 't':
						*(va_arg(list, ptrdiff_t*)) = chars;
						break;
					default:
						break;
					}
					break;
				}

				case 'e':
				case 'E':
					emode = true;
					__attribute__((fallthrough));
				case 'f':
				case 'F':
				case 'g':
				case 'G':
				{
					double floating = va_arg(list, double);

					while (emode && floating >= 10) {
						floating /= 10;
						++expo;
					}

					int form = lengthSpec - precSpec - expo - (precSpec || altForm ? 1 : 0);
					if (emode) {
						form -= 4;      // 'e+00'
					}
					if (form < 0) {
						form = 0;
					}
					int tempform = form;
					if (leftJustify) {
						form = 0;
					}
					__i__int_str(floating, intStrBuffer, base, plusSign, spaceNoSign, form, \
								 leftJustify, zeroPad);

					int lenIntstrbuffer = (int) strlen(intStrBuffer);

					__i_displayString(intStrBuffer, &chars, stream, buffer, size);

					floating -= (int) floating;

					for (int i = 0; i < precSpec; ++i) {
						floating *= 10;
					}
					intmax_t decPlaces = (intmax_t) (floating + 0.5);

					if (precSpec) {
						__i_displayCharacter('.', &chars, stream, buffer, size);
						//printf("Tempform = %d\n", tempform);
						__i__int_str(decPlaces, intStrBuffer, 10, false, false, 0, false, false);
						intStrBuffer[precSpec] = 0;
						__i_displayString(intStrBuffer, &chars, stream, buffer, size);
					} else if (altForm) {
						__i_displayCharacter('.', &chars, stream, buffer, size);
						//++lenIntstrbuffer;
					}

					if (tempform - lenIntstrbuffer > 0) {
						for (int i = 0; i < tempform - lenIntstrbuffer; ++i) {
							__i_displayCharacter(' ', &chars, stream, buffer, size);
						}
					}

					break;
				}


				case 'a':
				case 'A':
					//ACK! Hexadecimal floating points...
					break;

				default:
					break;
				}

				if (specifier == 'e') {
					__i_displayString((char*) "e+", &chars, stream, buffer, size);
				} else if (specifier == 'E') {
					__i_displayString((char*) "E+", &chars, stream, buffer, size);
				}

				if (specifier == 'e' || specifier == 'E') {
					__i__int_str(expo, intStrBuffer, 10, false, false, 2, false, true);
					__i_displayString(intStrBuffer, &chars, stream, buffer, size);
				}

			} else {
				int ln = strlen(plainCharBuffer);
				if (ln < 1000) {
					plainCharBuffer[ln] = format[i];
					plainCharBuffer[ln + 1] = 0;

				} else {
					__i_displayString(plainCharBuffer, &chars, stream, buffer, size);
					plainCharBuffer[0] = 0;

					__i_displayCharacter(format[i], &chars, stream, buffer, size);
				}
			}
		}


		if (strlen(plainCharBuffer)) {
			__i_displayString(plainCharBuffer, &chars, stream, buffer, size);
			plainCharBuffer[0] = 0;
		}

		//write null char, but don't save it to 'chars' by using a dummy
		//(only if sprintf, not printf)
		if (buffer) {
			int dummy = chars;
			__i_displayCharacter(0, &dummy, stream, buffer, size);
		}

		return chars;*/
	}


	void AcpiOsVprintf(const char* format, va_list list)
	{
		//__i_internal_printf(format, list, nullptr, nullptr, 0);
	}

	void AcpiOsPrintf(const char* format, ...)
	{
		va_list list;
		va_start(list, format);
		AcpiOsVprintf(format, list);
		va_end(list);
	}
#endif

#undef FILE
}