org 0x2000
bits 16

extern 
start:
	cli
	cld
	lgdt [0xFE0]
	lidt [0xFE8]
	jmp $
