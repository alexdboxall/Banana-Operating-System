org 0x8000
bits 16

;Oct 18th - 204 BYTES (TESTED AND WORKS)
;Oct 19th - 84  BYTES (DIDN'T WORK PROPERLY)
;Oct 20th - 60  BYTES (TESTED AND WORKS)

main:
	cli													; We don't want interrupts ATM
	;set to 32 bit GDT entries
	mov al, 0x10		;bh is already clear from XOR EAX, EAX
	cbw					;sign extend AL into AH (clears AH in this situation)
    mov ds, ax
    mov ss, ax

	mov bx, GDT64Pointer - 0x100	;'magic' to get around DS being 0x10 instead of 0x0
	lgdt [bx]
	
	mov eax, cr0 
	or al, 1       ; set PE (Protection Enable) bit in CR0 (Control Register 0)
	mov cr0, eax

	jmp 0x8:PModeMain

GDT64:                           ; Global Descriptor Table (64-bit).
      dd      0  
	  dd 	  0
      dw     -1, 0, 0x9A00, 0xcf
      dw     -1, 0, 0x9200, 0xcf

GDT64Pointer:                    ; The GDT-pointer.
    dw $ - GDT64 - 1             ; Limit.
    dd GDT64                     ; Base.
	
bits 32
PModeMain:
	jmp 0x400000