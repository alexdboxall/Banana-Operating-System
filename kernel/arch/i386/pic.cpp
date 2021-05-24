#include <arch/i386/pic.hpp>
#include <krnl/hal.hpp>

void picIoWait()
{
	asm volatile ("jmp 1f\n\t"
				  "1:jmp 2f\n\t"
				  "2:");
}

void picDisable()
{
	//this disables the PIC
	outb(0xA1, 0xFF);
	outb(0x21, 0xFF);
}

uint16_t picGetIRQReg(int ocw3)
{
	outb(PIC1_COMMAND, ocw3);
	outb(PIC2_COMMAND, ocw3);
	return (inb(PIC2_COMMAND) << 8) | inb(PIC1_COMMAND);
}

void picRemap()
{
	//remaps interrupts 0-15 to 32-47 to avoid conflicts

	int offset1 = 32;		//first 8 IRQs start at 32 (to 39)
	int offset2 = 40;		//next  8 IRQs start at 40 (to 47)

	//save masks
	uint8_t a1 = inb(PIC1_DATA);
	uint8_t a2 = inb(PIC2_DATA);

	// starts the initialization sequence (in cascade mode)
	outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
	picIoWait();
	outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	picIoWait();

	// ICW2: Master PIC vector offset
	outb(PIC1_DATA, offset1);
	picIoWait();

	// ICW2: Slave PIC vector offset
	outb(PIC2_DATA, offset2);
	picIoWait();

	// ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
	outb(PIC1_DATA, 4);
	picIoWait();

	// ICW3: tell Slave PIC its cascade identity (0000 0010)
	outb(PIC2_DATA, 2);
	picIoWait();

	outb(PIC1_DATA, ICW4_8086);
	picIoWait();
	outb(PIC2_DATA, ICW4_8086);
	picIoWait();

	//restore saved masks.
	outb(PIC1_DATA, a1);
	outb(PIC2_DATA, a2);
}

void picEOI(int irqNum)
{
	if (irqNum == 7) {
		uint16_t isr = picGetIRQReg(PIC_READ_ISR);
		if (!(isr & (1 << 7))) {
			//spurious IRQ
			return;
		}
	}

	if (irqNum == 15) {
		uint16_t isr = picGetIRQReg(PIC_READ_ISR);
		if (!(isr & (1 << 15))) {
			//spurious, master still needs to know about it though
			outb(PIC1_COMMAND, PIC_EOI);
			return;
		}
	}

	//acknowledge interrupt
	if (irqNum >= 8) {
		outb(PIC2_COMMAND, PIC_EOI);
	}

	outb(PIC1_COMMAND, PIC_EOI);
}