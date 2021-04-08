org 0xB000
bits 16

start:
	cli
	mov eax, 0x12345678
	jmp $

main:
	cli													; We dont want interrupts ATM
	mov ax, 0										; Were at 0000:7c000, so set our segment registers to that
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	xor ax, ax											; Set our stack to 0x0000 and create it
	mov ss, ax
	xor sp, sp			;itll loop round! to 0xFFFF

	;call enable_A20
	
	;https://forum.osdev.org/viewtopic.php?f=1&t=21364&start=0
	
	;push	ax
	;mov	al, 0xdd	; send enable a20 address line command to controller
	;out	0x64, al
	;pop	ax
	
	mov eax, GDT64Pointer
	lgdt [eax]
	
	;mov eax, [0x7D04]
	;lgdt [eax]    ;our a pointer to our main GDT pointer is in 0x7F04
	
	mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp flush2
	flush2:
	
	
	cli

	mov eax, 0xA000
	mov cr3, eax

	mov eax, cr4
	or eax, 1 << 4			;enable PSE
	;or eax, 1 << 2			;enable TSC disable
	mov cr4, eax
	
	mov eax, cr0
	or eax, 1
	or eax, (1 << 31)		;enable paging and p-mode
	and eax, ~(1 << 16)		;disable write protect
	mov cr0, eax

	nop
	nop
	nop
	nop
	nop
	nop
	nop


	jmp 0x8:PModeMain
	

GDT64:                           ; Global Descriptor Table (64-bit).
      dd      0  
	  dd 	  0
      dw     -1, 0, 0x9A00, 0xcf
      dw     -1, 0, 0x9200, 0xcf

GDT64Pointer:                    ; The GDT-pointer.
    dw $ - GDT64 - 1             ; Limit.
    dq GDT64                     ; Base.
	
	align 64	
bits 32
PModeMain:
	cli
    mov	ax, 0x10		; set data segments to data selector (0x10)
    mov	ds, ax
    mov	ss, ax
    mov	es, ax
    mov	esp, 0x2000
	cld

	call [0x1000]
	mov esp, eax
	call [0x1004]

	mov eax, 0xDEADBEEF
	cli
	hlt
	jmp $