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
	entry->esp0 = esp;
}

void TSS::flush()
{
	uint16_t gdtOffset = gdtEntry | 3;
	asm volatile ("mov %0, %%ax; ltrw %%ax" :: "r"(gdtOffset) : "%ax");
}

int TSS::setup(size_t esp, size_t eip)
{
	entry = (TSSEntry*) malloc(sizeof(TSSEntry));
	memset(entry, 0, sizeof(TSSEntry));

	entry->iopb = sizeof(TSSEntry);
	entry->ss0 = 0x10;
	entry->esp0 = esp;

	entry->cs = 0x08;
	entry->ds = 0x10;
	entry->es = 0x10;
	entry->ss = 0x10;

	entry->eip = eip;
	entry->esp = esp;
	entry->eflags = 0x2;

	entry->cr3 = thisCPU()->readCR3();

	GDTEntry tssEnt;
	tssEnt.setBase((size_t) entry);
	tssEnt.setLimit(sizeof(TSSEntry));
	tssEnt.access = 0b10001001;
	tssEnt.flags = 0;
	tssEnt.size = PLATFORM_ID == 64 ? 0 : 1;

	gdtEntry = thisCPU()->gdt.addEntry(tssEnt);
	thisCPU()->gdt.flush();

	kprintf("Setup TSS, GDT entry is 0x%X\n", gdtEntry);

	return gdtEntry;
}