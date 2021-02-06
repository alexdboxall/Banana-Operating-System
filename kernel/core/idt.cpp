#include "core/idt.hpp"
#include "core/main.hpp"
#include "core/tss.hpp"
#include "core/cpu.hpp"
#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

IDTEntry::IDTEntry(bool userspaceAllowed)
{
	selector = 0x08;
	mustBeZero = 0;
	type = 0xE;
	storageSegment = 0;
	priv = userspaceAllowed ? 3 : 0;
	present = 1;
}

void IDTEntry::setOffset(uint32_t base)
{
	offsetLow = base & 0xFFFF;
	offsetHigh = (base >> 16) & 0xFFFF;
}

IDT::IDT()
{
}

size_t IDT::getPointerToInvalidOpcodeEntryForF00F()
{
	return (size_t) &entries[6];
}

void IDT::addEntry(IDTEntry entry, int num)
{
	entries[num] = entry.val;
}

void IDT::addEntry(int num, void (*offset)(), bool userspace)
{
	IDTEntry ent(userspace);
	ent.setOffset((size_t) offset);
	addEntry(ent, num);
}

IDTDescriptor idtDescr;

void IDT::flush()
{
	idtDescr.size = 256 * 8 - 1;
	idtDescr.offset = (size_t) (void*) entries;

	asm("lidt %0" : : "m"(idtDescr));  // let the compiler choose an addressing mode
}

extern "C" void isr0();
extern "C" void isr1();
extern "C" void isr2();
extern "C" void isr3();
extern "C" void isr4();
extern "C" void isr5();
extern "C" void isr6();
extern "C" void isr7();
extern "C" void isr8();
extern "C" void isr9();
extern "C" void isr10();
extern "C" void isr11();
extern "C" void isr12();
extern "C" void isr13();
extern "C" void isr14();
extern "C" void isr15();
extern "C" void isr16();
extern "C" void isr17();
extern "C" void isr18();
extern "C" void isr96();

extern "C" void irq0();
extern "C" void irq1();
extern "C" void irq2();
extern "C" void irq3();
extern "C" void irq4();
extern "C" void irq5();
extern "C" void irq6();
extern "C" void irq7();
extern "C" void irq8();
extern "C" void irq9();
extern "C" void irq10();
extern "C" void irq11();
extern "C" void irq12();
extern "C" void irq13();
extern "C" void irq14();
extern "C" void irq15();
extern "C" void irq16();
extern "C" void irq17();
extern "C" void irq18();
extern "C" void irq19();
extern "C" void irq20();
extern "C" void irq21();
extern "C" void irq22();
extern "C" void irq23();

void IDT::setup()
{
	addEntry(0, isr0, false);
	addEntry(1, isr1, false);
	addEntry(2, isr2, false);
	addEntry(3, isr3, false);
	addEntry(4, isr4, false);
	addEntry(5, isr5, false);
	addEntry(6, isr6, false);
	addEntry(7, isr7, false);
	addEntry(8, isr8, false);
	addEntry(9, isr9, false);
	addEntry(10, isr10, false);
	addEntry(11, isr11, false);
	addEntry(12, isr12, false);
	addEntry(13, isr13, false);
	addEntry(14, isr14, false);
	addEntry(15, isr15, false);
	addEntry(16, isr16, false);
	addEntry(17, isr17, false);
	addEntry(18, isr18, false);
	addEntry(96, isr96, true);

	addEntry(32, irq0, false);
	addEntry(33, irq1, false);
	addEntry(34, irq2, false);
	addEntry(35, irq3, false);
	addEntry(36, irq4, false);
	addEntry(37, irq5, false);
	addEntry(38, irq6, false);
	addEntry(39, irq7, false);
	addEntry(40, irq8, false);
	addEntry(41, irq9, false);
	addEntry(42, irq10, false);
	addEntry(43, irq11, false);
	addEntry(44, irq12, false);
	addEntry(45, irq13, false);
	addEntry(46, irq14, false);
	addEntry(47, irq15, false);
	addEntry(48, irq16, false);
	addEntry(49, irq17, false);
	addEntry(50, irq18, false);

	addEntry(51, irq19, false);
	addEntry(52, irq20, false);
	addEntry(53, irq21, false);
	addEntry(54, irq22, false);
	addEntry(55, irq23, false);

	entries[8].type = 0x5;		//task gate
	entries[8].offset = 0;
	entries[8].selector = thisCPU()->doubleFaultSelector;

	flush();
}

