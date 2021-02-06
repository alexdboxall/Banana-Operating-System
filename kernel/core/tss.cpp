#include "core/tss.hpp"
#include "core/gdt.hpp"
#include "core/common.hpp"
#include "hw/cpu.hpp"
#pragma GCC optimize ("O0")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

uint16_t doubleFaultSelector;

TSS::TSS()
{

}

void TSS::setESP(size_t esp)
{
	size_t* memoryLocation = (size_t*) (size_t) (ptr + 4 / 2);
	*memoryLocation = esp;
}

int TSS::setup(size_t esp, bool load)
{
	ptr = (uint16_t*) malloc(1024);
	memset(ptr, 0, 1024);

	//write the size
	*(ptr + 0x66 / 2) = 0x68;

	//write SS if needed
	if (sizeof(size_t) == 4) {
		*(ptr + 0x8 / 2) = 0x10;			//kernel SS
	}

	setESP(esp);

	kprintf("TSS setup 0x%X\n", esp);

	GDTEntry tssEnt;
	tssEnt.setBase((size_t) ptr);
	tssEnt.setLimit(0x68);
	tssEnt.access = 0b10001001;
	tssEnt.flags = 0;
	tssEnt.size = PLATFORM_ID == 64 ? 0 : 1;

	int gdtEntry = thisCPU()->gdt.addEntry(tssEnt);
	thisCPU()->gdt.flush();

	uint16_t gdtOffset = gdtEntry | 3;
	if (load) {
		asm volatile ("mov %0, %%ax; ltrw %%ax" :: "r"(gdtOffset) : "%ax");
	} else {
		uint32_t* p2 = (uint32_t*) (((uint8_t*) ptr) + 0x1C);
		*p2 = thisCPU()->readCR3();
	}
	return gdtEntry;
}