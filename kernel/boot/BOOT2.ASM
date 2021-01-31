bits	16
org 0x7E00

jmp	main

times 1024 db 0

%include "FAT.INC"
%include "GDT.INC"

puts:
		pusha				; save registers
.Loop1:
		lodsb				; load next byte from string from SI to AL
		or	al, al			; Does AL=0?
		jz	putsdone		; Yep, null terminator found-bail out
		mov	ah, 0eh			; Nope-Print the character
		int	10h			; invoke BIOS
		jmp	.Loop1			; Repeat until null terminator found
putsdone:
		popa				; restore registers
		ret				; we are done, so return

_bpb:
_bpb.logicalSectorsPerFAT	dd 0
_bpb.totalFATs				db 0
_bpb.reservedSectors		dw 0
_bpb.hiddenSectors			dd 0

main:
	cli

	mov edi, eax

	xor	ax, ax
	mov	ds, ax
	mov	es, ax
	mov	ss, ax
	mov	sp, 0xFFFF
	sti
	
	;non-partition
	;EAX=000003c1 EBX=00000000 ECX=0000187e EDX=00000280
	;ESI=00000065 EDI=000003c1 EBP=00000000 ESP=0000ffff
	;EIP=00008694 EFL=00000246 [---Z-P-] CPL=0 II=0 A20=1 SMM=0 HLT=0
	; 0x3C1 sectors / FAT
	; 2 FATs
	; 0x187E reserved sectors
	; 0 hidden sectors
	; Dirve = 0x80

	;partition
	;EAX=00000a74 EBX=00000080 ECX=0000187e EDX=00000280
	;ESI=00000065 EDI=00000a74 EBP=00000000 ESP=0000ffff
	;EIP=00008694 EFL=00000246 [---Z-P-] CPL=0 II=0 A20=1 SMM=0 HLT=0
	;
	; 0xA74 sectors / FAT		(CORRECT)
	; 2 FATs					(CORRECT)
	; 0x187E reserved sectors	(CORRECT)
	; 0x80 hidden sectors		(CORRECT)
	; Drive = 0x80				(CORRECT)
	;
	; For reference:
	;	FAT STARTS AT 0x31FC00 (sctr 0x18FE (0x187E + 0x80))
	;	

	mov eax, edi		

	mov eax, [0x7C00 + 0x24]
	mov ebx, [0x7C00 + 0x1C]
	mov cx, [0x7C00 + 0xE]
	mov dh, [0x7C00 + 0x10]

	mov [_bpb.logicalSectorsPerFAT], eax
	mov [_bpb.hiddenSectors], ebx
	mov [_bpb.reservedSectors], cx
	mov [_bpb.totalFATs], dh

	mov [driveNumber], dl


	mov ax, 3			;go into a text mode
	int 0x10
	mov ax, 0xFF00
	mov cx, 0x4000
	mov di, 0xB800
	mov es, di
	xor di, di
	rep stosw

	mov ax, 0x4F02
	mov bx, 0x4115
	mov cx, 0x4115
	;int 0x10

	mov si, intro
	call puts

	
.skipKey:

	call enableA20
	call DetectRAM

	mov si, waitmsg
	call puts

	;disable hardware text blinking
	mov dx, 0x3DA
    in al, dx
    mov dx, 0x3C0
    mov al, 0x30
    out dx, al
    inc dx
    in al, dx
    and al, 0xF7
    dec dx
    out dx, al  

	;BIOS method, just in case
	mov ax, 0x1003
	mov bl, 0			;enable bg intensity, disable blinking
	mov bh, 0			;avoid problems on some adapters
	int 0x10

	jmp loadKernelImage



fail:
    cli
    hlt
    jmp fail

debugMsg db "SECOND STAGE DEBUGGER.", 0xA, 0xD, "At each stage, a number will be recorded. Remember the highest number you get.", "Press ENTER to advance to the next stage.", 0xA, 0xD, "NUMBERS: 0 ", 0

debugger:
	mov si, debugMsg
	call puts
	jmp $

loadKernelImage:
	mov [fsInputFilepathA + 0], byte 'B'
	mov [fsInputFilepathA + 1], byte 'A'
	mov [fsInputFilepathA + 2], byte 'N'
	mov [fsInputFilepathA + 3], byte 'A'
	mov [fsInputFilepathA + 4], byte 'N'
	mov [fsInputFilepathA + 5], byte 'A'
	mov [fsInputFilepathA + 6], byte ' '
	mov [fsInputFilepathA + 7], byte ' '
	mov [fsInputFilepathA + 8], byte ' '
	mov [fsInputFilepathA + 9], byte ' '
	mov [fsInputFilepathA + 10], byte ' '

	mov [fsInputFilepathB + 0], byte 'K'
	mov [fsInputFilepathB + 1], byte 'E'
	mov [fsInputFilepathB + 2], byte 'R'
	mov [fsInputFilepathB + 3], byte 'N'
	mov [fsInputFilepathB + 4], byte 'E'
	mov [fsInputFilepathB + 5], byte 'L'
	mov [fsInputFilepathB + 6], byte '3'
	mov [fsInputFilepathB + 7], byte '2'
	mov [fsInputFilepathB + 8], byte 'E'
	mov [fsInputFilepathB + 9], byte 'X'
	mov [fsInputFilepathB + 10], byte 'E'

	mov eax, 0x80000000    ; Set the A-register to 0x80000000.
    cpuid                  ; CPU identification.
    cmp eax, 0x80000001    ; Compare the A-register with 0x80000001.
    jb .force32         ; It is less, there is no long mode.
	mov eax, 0x80000001    ; Set the A-register to 0x80000001.
    cpuid                  ; CPU identification.
    test edx, 1 << 29      ; Test if the LM-bit, which is bit 29, is set in the D-register.
    jz .force32				; They aren't, there is no long mode.'

	; IF 64 BIT...
	mov [fsInputFilepathB + 6], byte '6'
	mov [fsInputFilepathB + 7], byte '4'
	
.force32:

	mov [fsOutputSeg], word 0
	mov [fsOutputOff], word 0x7000

	call readFileIntoProtectedMode

	call InstallGDT

	mov edi, [pmodeWriteOffset]

	cli
    mov eax, cr0	
    or eax, 1
    mov cr0, eax

    jmp CODE_DESC:ProtectedMode

;FILESYSTEM STUFF.
;REPLACE WITH VALUES THEN CALL readFile TO USE THE FILESYSTEM

fsInputFilepathA db "BANANA     ", 0
fsInputFilepathB db "BOOTSET SYS", 0
fsOutputSeg dw 0x0
fsOutputOff dw 0x7000

intro db "Starting Banana...", 0xA, 0xD, 0
waitmsg db "", 0xA, 0xD, 0

driveNumber db 0

enableA20:

	cli
	pusha

    call    wait_input
    mov     al,0xAD
    out     0x64,al		; disable keyboard
    call    wait_input

    mov     al,0xD0
    out     0x64,al		; tell controller to read output port
    call    wait_output

    in      al,0x60
    push    eax		; get output port data and store it
    call    wait_input

    mov     al,0xD1
    out     0x64,al		; tell controller to write output port
    call    wait_input

    pop     eax
    or      al,2		; set bit 1 (enable a20)
    out     0x60,al		; write out data back to the output port

    call    wait_input
    mov     al,0xAE		; enable keyboard
    out     0x64,al

    call    wait_input
popa
    sti
    ret

; wait for input buffer to be clear

wait_input:
    in      al,0x64
    test    al,2
    jnz     wait_input
    ret

; wait for output buffer to be clear

wait_output:
    in      al,0x64
    test    al,1
    jz      wait_output
    ret

DetectRAM:
	pusha
	mov di, 0x600
	mov ax, 0;0x2800
	mov es, ax
	
	call do_e820

	popa
	ret

; use the INT 0x15, eax= 0xE820 BIOS function to get a memory map
; inputs: es:di -> destination buffer for 24 byte entries
; outputs: bp = entry count, trashes all registers except esi
do_e820:
	xor ebx, ebx		; ebx must be 0 to start
	xor bp, bp		; keep an entry count in bp
	mov edx, 0x0534D4150	; Place "SMAP" into edx
	mov eax, 0xe820
	mov [es:di + 20], dword 1	; force a valid ACPI 3.X entry
	mov ecx, 24		; ask for 24 bytes
	int 0x15
	jc short .failed	; carry set on first call means "unsupported function"
	mov edx, 0x0534D4150	; Some BIOSes apparently trash this register?
	cmp eax, edx		; on success, eax must have been reset to "SMAP"
	jne short .failed
	test ebx, ebx		; ebx = 0 implies list is only 1 entry long (worthless)
	je short .failed
	jmp short .jmpin
.e820lp:
	mov eax, 0xe820		; eax, ecx get trashed on every int 0x15 call
	mov [es:di + 20], dword 1	; force a valid ACPI 3.X entry
	mov ecx, 24		; ask for 24 bytes again
	int 0x15
	jc short .e820f		; carry set means "end of list already reached"
	mov edx, 0x0534D4150	; repair potentially trashed register
.jmpin:
	jcxz .skipent		; skip any 0 length entries
	cmp cl, 20		; got a 24 byte ACPI 3.X response?
	jbe short .notext
	test byte [es:di + 20], 1	; if so: is the "ignore this data" bit clear?
	je short .skipent
.notext:
	mov ecx, [es:di + 8]	; get lower uint32_t of memory region length
	or ecx, [es:di + 12]	; "or" it with upper uint32_t to test for zero
	jz .skipent		; if length uint64_t is 0, skip entry
	inc bp			; got a good entry: ++count, move to next storage spot
	add di, 24
.skipent:
	test ebx, ebx		; if ebx resets to 0, list is complete
	jne short .e820lp
.e820f:
	mov [0x513], bp	; store the entry count
	clc			; there is "jc" on end of list to this point, so the carry must be cleared
	ret
.failed:
	mov [0x513], word 0
	stc			; "function unsupported" error exit
	ret


bits 32

ProtectedMode:
	mov	ax, DATA_DESC
	mov	ds, ax
	mov	ss, ax
	mov	es, ax
	mov	esp, 0x240000
	
	;the bss was cleared on the first trip to pmode

	cli
	jmp	CODE_DESC:0x100000


	mov eax, 0xDEADDEAD
	hlt
	jmp $

;1st stage bootloader will forget to load the last sector
times 512 db 0