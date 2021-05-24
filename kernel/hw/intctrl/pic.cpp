#include "hw/intctrl/pic.hpp"
#include "krnl/hal.hpp"
#include "core/main.hpp"
#include "hal/intctrl.hpp"
#include "krnl/hal.hpp"

#pragma GCC optimize ("O0")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

#define PIC1			0x20		/* IO base address for master PIC */
#define PIC2			0xA0		/* IO base address for slave PIC */
#define PIC1_COMMAND	PIC1
#define PIC1_DATA		(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA		(PIC2+1)

#define PIC_READ_IRR    0x0a		/* OCW3 irq ready next CMD read */
#define PIC_READ_ISR    0x0b		/* OCW3 irq service next CMD read */

#define PIC_EOI			0x20		/* End-of-interrupt command code */

#define ICW1_ICW4		0x01		/* ICW4 (not) needed */
#define ICW1_SINGLE		0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL		0x08		/* Level triggered (edge) mode */
#define ICW1_INIT		0x10		/* Initialization - required! */

#define ICW4_8086		0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO		0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM		0x10		/* Special fully nested (not) */

PIC::PIC() : InterruptController ("Programmable Interrupt Controller")
{
	ports[noPorts].rangeStart = 0x0020;
	ports[noPorts].rangeLength = 2;
	ports[noPorts++].width = 0;

	ports[noPorts].rangeStart = 0x00A0;
	ports[noPorts].rangeLength = 2;
	ports[noPorts++].width = 0;
}

void PIC::ioWait()
{
	asm volatile (  "jmp 1f\n\t"
				  "1:jmp 2f\n\t"
				  "2:");
}

void PIC::disable()
{
	//this disables the PIC
	outb(0xA1, 0xFF);
	outb(0x21, 0xFF);
}

uint16_t PIC::getIRQReg(int ocw3)
{
	outb(PIC1_COMMAND, ocw3);
	outb(PIC2_COMMAND, ocw3);
	return (inb(PIC2_COMMAND) << 8) | inb(PIC1_COMMAND);
}

void PIC::remap()
{
	//remaps interrupts 0-15 to 32-47 to avoid conflicts
	
	int offset1 = 32;		//first 8 IRQs start at 32 (to 39)
	int offset2 = 40;		//next  8 IRQs start at 40 (to 47)

	//save masks
	uint8_t a1 = inb(PIC1_DATA);                        
	uint8_t a2 = inb(PIC2_DATA);

	// starts the initialization sequence (in cascade mode)
	outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);  
	ioWait();
	outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	ioWait();

	// ICW2: Master PIC vector offset
	outb(PIC1_DATA, offset1);                 
	ioWait();

	// ICW2: Slave PIC vector offset
	outb(PIC2_DATA, offset2);                 
	ioWait();

	// ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
	outb(PIC1_DATA, 4);                       
	ioWait();

	// ICW3: tell Slave PIC its cascade identity (0000 0010)
	outb(PIC2_DATA, 2);                      
	ioWait();

	outb(PIC1_DATA, ICW4_8086);
	ioWait();
	outb(PIC2_DATA, ICW4_8086);
	ioWait();

	//restore saved masks.
	outb(PIC1_DATA, a1); 
	outb(PIC2_DATA, a2);
}

void PIC::eoi(uint8_t irqNum)
{
	Hal::endOfInterrupt(irqNum);
}

int PIC::open(int, int, void*)
{
	//do not mask any IRQs
	outb(PIC1_DATA, 0x00);
	outb(PIC2_DATA, 0x00);

	remap();

	return 0;
}

int PIC::close(int, int, void*)
{
	disable();
	return 0;
}