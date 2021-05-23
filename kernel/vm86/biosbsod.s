org 0x900
bits 32

cli
mov eax,cr0
and eax,0x7FFFFFFF
mov cr0,eax
jmp 0x28:0x900

bits 16

prot16:
	mov ax,0x0020 ; 8.9.2. Step 4.
	mov ds,ax
	mov es,ax
	mov fs,ax
	mov gs,ax
	mov ss,ax

	mov sp, 0x7000

	mov eax,cr0 ; 8.9.2. Step 2.
	and al,0xFE	
	mov cr0,eax	;FREEZE!

	jmp word 0:real16		; 8.9.2. Step 7.

align 16
bits 16
real16:
	cli
	mov ax, 0
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	mov sp, 0x8000

	mov ax, 3
	int 0x10


