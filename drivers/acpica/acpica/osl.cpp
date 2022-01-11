
#include "krnl/kheap.hpp"
#include "krnl/virtmgr.hpp"
#include "krnl/computer.hpp"
#include "krnl/common.hpp"
#include "krnl/hal.hpp"
#include "hw/acpi.hpp"
#include "hal/timer.hpp"
#include "krnl/main.hpp"
#include "thr/prcssthr.hpp"
#include "hal/intctrl.hpp"
#include "hw/cpu.hpp"

#include <stdarg.h>

////#pragma GCC optimize ("O2")
////#pragma GCC optimize ("-fno-strict-aliasing")
//#pragma GCC optimize ("-fno-align-labels")
//#pragma GCC optimize ("-fno-align-jumps")
//#pragma GCC optimize ("-fno-align-loops")
//#pragma GCC optimize ("-fno-align-functions")

extern "C" {
#include "libk/string.h"
#include "acpi.h"
#include "actypes.h"

#define FILE int
	//MOST OF THESE DON'T ACTUALLY EXIST, JUST HERE TO STOP THE COMPILER COMPLAINING
	//THAT WE DON'T HAVE THE HEADER FILE (THE DEFINITIONS ARE HIDDEN DEEP WITHIN ACPICA)
	void* memmove(void* destination, const void* source, size_t n);
	char* strcpy(char*  destination, const char*  source);
	//char* strncpy(char*  destination, const char*  source, size_t n);
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
	//char* strchr(const char* s, int c);
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
		return milliTenthsSinceBoot * 1000;
	}

	void AcpiOsWaitEventsComplete(void)
	{
		KePanic("AcpiOsWaitEventsComplete");
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
			KePanic("[acpica osl] AcpiOsWritePciConfiguration bad width!");
			break;
		}

		return AE_OK;

	}

	ACPI_STATUS AcpiOsSignal(UINT32 Function, void* Info)
	{
		switch (Function) {
		case ACPI_SIGNAL_FATAL:
			KePanic("[acpi]	AML fatal opcode");
			break;
		case ACPI_SIGNAL_BREAKPOINT:
			kprintf("[acpi]	AML breakpoint\n");
			break;
		default:
			KePanic("[acpi] AcpiOsSignal");
			return AE_BAD_PARAMETER;
		}

		return AE_OK;
	}

	ACPI_STATUS AcpiOsReadMemory(ACPI_PHYSICAL_ADDRESS Address, UINT64* Value, UINT32 Width)
	{
		KePanic("Read Memory...\n");
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
		KePanic("Write Memory...\n");

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
		int pages = (Length + 4096) / 4096;
		size_t virt = Virt::allocateKernelVirtualPages(pages);

		for (int i = 0; i < pages; ++i) {
			Virt::getAKernelVAS()->mapPage((PhysicalAddress & ~0xFFF) + i * 4096, virt + i * 4096, PAGE_PRESENT | PAGE_SUPERVISOR);
		}
		
		CPU::writeCR3(CPU::readCR3());

		return (void*) (virt | (PhysicalAddress & 0xFFF));
	}

	void AcpiOsUnmapMemory(void* where, ACPI_SIZE length)
	{
		kprintf("ignoring ACPICA request to unmap memory...\n");
		//Virt::getCurrent()->freeAllocatedPages(((size_t) where) & ~0xFFF);
	}

	ACPI_STATUS AcpiOsGetPhysicalAddress(void* LogicalAddress, ACPI_PHYSICAL_ADDRESS* PhysicalAddress)
	{
		*PhysicalAddress = Virt::getAKernelVAS()->virtualToPhysical((size_t) LogicalAddress);
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
		kprintf("AcpiOsReadable 0x%X\n", Memory);
		return true;
	}

	BOOLEAN AcpiOsWritable(void* Memory, ACPI_SIZE Length)
	{
		kprintf("AcpiOsWritable 0x%X\n", Memory);
		return true;
	}

	ACPI_THREAD_ID AcpiOsGetThreadId()
	{
		//kprintf("AcpiOsGetThreadId\n");
		return 1;	// currentTaskTCB->rtid + 1;
	}

	ACPI_STATUS AcpiOsExecute(ACPI_EXECUTE_TYPE Type, ACPI_OSD_EXEC_CALLBACK Function, void* Context)
	{
		KePanic("TODO: PUT CONTEXT ON THE STACK AcpiOsExecute");
		//createKernelThread(kernelProcess, (void(*)()) Function, 128);
		return AE_OK;
	}

	void AcpiOsSleep(UINT64 Milliseconds)
	{
		milliTenthSleep(Milliseconds * 10);
	}

	void AcpiOsStall(UINT32 Microseconds)
	{
		uint64_t end = milliTenthsSinceBoot + Microseconds / 100 + 1;
		while (milliTenthsSinceBoot < end) {

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
		if (Units > 1) {
			kprintf("AcpiOsWaitSemaphore units > 1\n");
			return AE_SUPPORT;
		}

		if (Timeout == 0xFFFF) {
			((Semaphore*) Handle)->acquire();
		} else {
			uint32_t startNano = milliTenthsSinceBoot;
			uint32_t extra = ((uint32_t) Timeout) * 10;

			while (milliTenthsSinceBoot < startNano + extra) {
				bool success = ((Semaphore*) Handle)->tryAcquire();
				if (success) return AE_OK;
			}
			kprintf("AcpiOsWaitSemaphore AE_TIME\n");
			return AE_TIME;
		}
		
		return AE_OK;
	}

	ACPI_STATUS AcpiOsSignalSemaphore(ACPI_SEMAPHORE Handle, UINT32 Units)
	{
		//kprintf("TODO: AcpiOsSignalSemaphore\n");

		if (Units > 1) {
			kprintf("AcpiOsSignalSemaphore unts > 1\n");

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

		HalInstallIRQHandler(InterruptLevel, (void(*)(struct regs*, void*))Subhandler, false, ctx);
		return AE_OK;
	}

	ACPI_STATUS AcpiOsRemoveInterruptHandler(UINT32 InterruptNumber, ACPI_OSD_HANDLER Handler)
	{
		KePanic("AcpiOsRemoveInterruptHandler");
		return AE_OK;
	}

	void AcpiOsVprintf(const char* format, va_list list)
	{

	}

	void AcpiOsPrintf(const char* format, ...)
	{
		
	}
#endif

#undef FILE
}