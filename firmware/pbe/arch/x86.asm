bits 16
section .text

start:
	mov edi, eax

	mov ax, 0
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov [___bootdrive], dl

	mov eax, edi
		
	mov eax, [0x7C00 + 0x24]
	mov ebx, [0x7C00 + 0x1C]
	mov cx, [0x7C00 + 0xE]
	mov dh, [0x7C00 + 0x10]

	mov [___bootLogicalSectorsPerFAT], eax
	mov	[___bootTotalFATs], dh
	mov [___bootFATReservedSectors], cx
	mov [___bootFATHiddenSectors], ebx

	mov ax, 3
	int 0x10

	;disable blink
	mov ax, 0x1003
	mov bl, 0
	mov bh, 0
	int 0x10

    mov ax, 3
	int 0x10

	call enableA20

	mov di, 0x1200
	mov ax, 0
	mov es, ax
	call do_e820

	mov [fs:0x900], dword 0
	mov [fs:0x904], dword 0

	;32 bit p-mode code
	mov [fs:0x908], word 0xFFFF
	mov [fs:0x90A], word 0
	mov [fs:0x90C], word 0x9A00
	mov [fs:0x90E], word 0xCF
	
	;32 bit p-mode code
	mov [fs:0x910], word 0xFFFF
	mov [fs:0x912], word 0
	mov [fs:0x914], word 0x9200
	mov [fs:0x916], word 0xCF
	
	;16 bit p-mode code
	mov [fs:0x918], word 0xFFFF
	mov [fs:0x91A], word 0
	mov [fs:0x91C], word 0x9A00
	mov [fs:0x91E], word 0x0F

	;16 bit p-mode data
	mov [fs:0x920], word 0xFFFF
	mov [fs:0x922], word 0
	mov [fs:0x924], word 0x9200
	mov [fs:0x926], word 0x0F

	mov [fs:0x928], word 0x27
	mov [fs:0x92A], dword 0x900

	mov eax, 0x928
	lgdt [eax]        ; load GDT into GDTR

	mov dl, [___bootdrive]

    mov eax, cr0	
    or eax, 1
    mov cr0, eax

    jmp 0x8:PMODE_INIT

	hlt
	jmp $

___bootdrive db 0
___bootLogicalSectorsPerFAT dd 0
___bootTotalFATs db 0
___bootFATReservedSectors dw 0
___bootFATHiddenSectors dd 0

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
	mov [0xBBBB], bp	; store the entry count
	clc			; there is "jc" on end of list to this point, so the carry must be cleared
	ret
.failed:
	mov [0xBBBB], word 0
	stc			; "function unsupported" error exit
	ret

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

bits 32
extern x86bbootdisk
extern main
PMODE_INIT:
	cli
	mov	ax, 0x10
	mov	ds, ax
	mov	ss, ax
	mov	es, ax

    mov esp, 0xC000

	mov [x86bbootdisk], dl

    call main
	jmp $


global x86Internal_getKey
global x86Internal_wait100ms
global x86InternalReadSector
global x86InternalWriteSector

_returnBuffer dd 0

x86Internal_getKey:
    pusha
    mov [_returnBuffer], dword 0
    mov [realModeCommand], byte 1
    call SWITCH_TO_REAL
    mov [_returnBuffer], eax
    popa
    mov eax, [_returnBuffer]
    ret

x86Internal_wait100ms:
    pusha
    mov [realModeCommand], byte 0
    call SWITCH_TO_REAL
    popa
    ret

x86InternalReadSector:
	mov [realModeCommand], byte 2
	call SWITCH_TO_REAL
	ret

x86InternalWriteSector:
	mov [realModeCommand], byte 3
	call SWITCH_TO_REAL
	ret

rmSwitchyStack dd 0
realModeCommand db 0
realModeData1 dd 0
realModeData2 dd 0
realModeData3 dd 0
realModeData4 dd 0
realModeRet1 dd 0
realModeRet2 dd 0
realModeRet3 dd 0
realModeRet4 dd 0




SWITCH_TO_REAL:
	mov [realModeData1], eax
	mov [realModeData2], ebx
	mov [realModeData3], ecx
	mov [realModeData4], edx

	cli ; 8.9.2. Step 1.

	mov [rmSwitchyStack], esp

	mov eax,cr0 ; 8.9.2. Step 2.
	and eax,0x7FFFFFFF	;0x7FFFFFFF
	mov cr0,eax

	jmp 0x18:prot16


[BITS 16]

prot16:
	mov ax,0x0020 ; 8.9.2. Step 4.
	mov ds,ax
	mov es,ax
	mov fs,ax
	mov gs,ax
	mov ss,ax

	mov sp, 0xB800

	mov eax,cr0 ; 8.9.2. Step 2.
	and al,0xFE	
	mov cr0,eax	;FREEZE!

	jmp word 0:real16		; 8.9.2. Step 7.

align 16
bits 16
real16:
	cli
	mov ax, 0x0
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

    mov ax, 0
	mov ss, ax

	mov sp, 0xB800

    cmp [realModeCommand], byte 0
    je REAL_MODE_WAIT_100MILLI
    cmp [realModeCommand], byte 1
    je REAL_MODE_GET_KEY
	cmp [realModeCommand], byte 2
    je RM_READ_JUMPER
	cmp [realModeCommand], byte 3
    je RM_WRITE_JUMPER

    jmp goBackHome

REAL_MODE_WAIT_100MILLI:
    mov ah, 0x86
	mov cx, 0x1
	mov dx, 0x7000      ;should be 0x86A0, but it takes a moment to do the syscall
	int 0x15
    jmp goBackHome

REAL_MODE_GET_KEY:
    mov ah, 1
	int 0x16
	jnz .hasKey
	mov eax, 0
    jmp goBackHome
.hasKey:
    mov ah, 0
    int 0x16
    jmp goBackHome






RM_READ_JUMPER:
.RM_READ:
	mov [blkcnt], word 1
	mov ebx, [realModeData2]

	mov [d_add], bx
	and [d_add], word 0xF
	shr ebx, 4
	mov [d_seg], bx

	mov eax, [realModeData1]
	mov [d_lba], eax
	mov edx, [realModeData4]

	cmp dl, 0
	je .RM_FLOPPY_READ
	cmp dl, 1
	je .RM_FLOPPY_READ

	mov ax, 0x4200
	mov si, DAPACK
	int 0x13
	jc .err

	mov eax, 0
	jmp goBackHome

.RM_FLOPPY_READ:
	push es
	pushad

	pushad
	mov ah, 0
	mov edx, [realModeData4]
	int 0x13
	popad

	call LBACHS

	mov si, 4

.retryfdc:
	mov bx, [d_seg]
	mov es, bx
	mov bx, [d_add]

	mov ah, 2
	mov al, 18
	mov ch, [absoluteTrack]
	mov cl, [absoluteSector]
	mov edx, [realModeData4]
	mov dh, [absoluteHead]
	pushad
	clc
	int 0x13
	jc .fdcerr
	cmp ah, 0
	jne .fdcerr
	popad

	popad
	pop es

	mov eax, 0
	jmp goBackHome

.fdcerr:
	popad

	dec si
	jz .err
	pushad
	mov ah, 0
	mov edx, [realModeData4]
	int 0x13
	popad
	jmp .retryfdc
.err:
	mov eax, 1
	jmp goBackHome

RM_WRITE_JUMPER:
.RM_WRITE:
	mov [blkcnt], word 1
	mov ebx, [realModeData2]
	mov [d_add], bx
	and [d_add], word 0xF
	shr ebx, 4
	mov [d_seg], bx
	mov eax, [realModeData1]
	mov [d_lba], eax
	mov edx, [realModeData4]

	cmp dl, 0
	je .RM_FLOPPY_WRITE
	cmp dl, 1
	je .RM_FLOPPY_WRITE

	mov ax, 0x4300
	mov si, DAPACK
	int 0x13
	je .err

	mov eax, 0
	jmp goBackHome


.RM_FLOPPY_WRITE:
	push es
	pushad

	pushad
	mov ah, 0
	mov edx, [realModeData4]
	int 0x13
	popad

	call LBACHS

	mov si, 4

.retryfdc22:
	mov bx, [d_seg]
	mov es, bx
	mov bx, [d_add]

	mov ah, 3
	mov al, 18
	mov ch, [absoluteTrack]
	mov cl, [absoluteSector]
	mov edx, [realModeData4]
	mov dh, [absoluteHead]
	pushad
	clc
	int 0x13
	jc .fdcerr22
	cmp ah, 0
	jne .fdcerr22
	popad

	popad
	pop es

	mov eax, 0
	jmp goBackHome

.fdcerr22:
	popad

	dec si
	jz .err
	pushad
	mov ah, 0
	mov edx, [realModeData4]
	int 0x13
	popad
	jmp .retryfdc22

.err:
	mov eax, 1
	jmp goBackHome


LBACHS:
	xor dx, dx
    div     WORD [_bpbsectorsPerTrack]           ; divide by sectors per track
    inc     dl                                  ; add 1 (absolute sector formula)
    mov     BYTE [absoluteSector], dl
  
    xor     dx, dx                              ; prepare dx:ax for operation
    div     WORD [_bpbheadsPerCylinder]          ; mod by number of heads (absolute head formula)
    mov     BYTE [absoluteHead], dl             ; everything else was already done from the first formula
 
    mov     BYTE [absoluteTrack], al            ; not much else to do :)
    ret

_bpbheadsPerCylinder dw 2
_bpbsectorsPerTrack dw 18

absoluteSector db 0
absoluteHead db 0
absoluteTrack db 0

align 8
DAPACK:
aaab	db	0x10
aaac	db	0
blkcnt:	dw	1		; int 13 resets this to # of blocks actually read/written
d_add:	dw	0x0500	; memory buffer destination address (0:7c00)
d_seg:	dw	0x0000	; in memory page zero
d_lba:	dd	0		; put the lba to read in this spot
biglba:	dd	0		; more storage bytes only for big lbas ( > 4 bytes )





goBackHome:
	cli

	mov [realModeRet1], eax
	mov [realModeRet2], ebx
	mov [realModeRet3], ecx
	mov [realModeRet4], edx

	xor ax, ax 
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov fs, ax

	cli
	mov [fs:0x900], dword 0
	mov [fs:0x904], dword 0

	;32 bit p-mode code
	mov [fs:0x908], word 0xFFFF
	mov [fs:0x90A], word 0
	mov [fs:0x90C], word 0x9A00
	mov [fs:0x90E], word 0xCF
	
	;32 bit p-mode code
	mov [fs:0x910], word 0xFFFF
	mov [fs:0x912], word 0
	mov [fs:0x914], word 0x9200
	mov [fs:0x916], word 0xCF
	
	;16 bit p-mode code
	mov [fs:0x918], word 0xFFFF
	mov [fs:0x91A], word 0
	mov [fs:0x91C], word 0x9A00
	mov [fs:0x91E], word 0x0F

	;16 bit p-mode data
	mov [fs:0x920], word 0xFFFF
	mov [fs:0x922], word 0
	mov [fs:0x924], word 0x9200
	mov [fs:0x926], word 0x0F

	mov [fs:0x928], word 0x27
	mov [fs:0x92A], dword 0x900

	mov eax, 0x928
	lgdt [eax]        ; load GDT into GDTR

	mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp .flush2
	.flush2:

	cli
	mov eax, cr0 
	or al, 1		; set PE (Protection Enable) bit in CR0 (Control Register 0)
	mov cr0, eax

	jmp 0x8:PMODE_RETURN

align 4
BITS 32
extern movePIC
PMODE_RETURN:
	cli

	mov	ax, 0x10
	mov	ds, ax
	mov	ss, ax
	mov	es, ax

	mov esp, [rmSwitchyStack]
	mov eax, [realModeRet1]
	mov ebx, [realModeRet2]
	mov ecx, [realModeRet3]
	mov edx, [realModeRet4]

	ret
