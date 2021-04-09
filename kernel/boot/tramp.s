org 0x2000
bits 16

extern 
start:
	cli
	cld
	lgdt [0xFE0]
	lidt [0xFE8]
	mov eax, [0xFF0]
	mov cr3, eax

	mov esp, 0xC2003000

	mov eax, cr0 
	or al, 1
	mov cr0, eax

	jmp 0x8:PModeMain

bits 32
PModeMain:
	mov eax, 0x12345678
	jmp $