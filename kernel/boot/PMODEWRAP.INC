;IN
;	EBX = pointer to string name
;	ECX = length of string name
;OUT
;	EAX = file location on disk
;	ECX = file size on disk
;	EDX = set to 0 on SUCCESS, 1 on FAILURE

bits 16

real32BitCopy:
	mov ebp, eax
	mov ax, 0
	mov fs, AX
	mov [fs:0x5000], ebp
	mov [fs:0x5004], ebx
	mov [fs:0x5008], ecx
	mov eax, ebp

	mov ax, 0
	mov fs, ax
	mov [0x51A0], sp
	mov eax, esp
	mov cr3, eax
	cli

	;call enable_A20

	xor ax, ax 
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov fs, ax

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

	jmp 0x8:ProtectedModeForCD; + 0x7E00

align 8
bits 32
ProtectedModeForCD:
	cli

	mov	ax, 0x10
	mov	ds, ax
	mov	ss, ax
	mov	es, ax
	mov	esp, 0x3F0000  ;4MB
	cld

	cmp [first32bit], byte 1
	jne .skipClearBSS

	;CLEAR THE FIRST FEW MEGABYTES SO THAT THE KERNEL GETS A BSS SECTION AS EXPECTED
	mov edi, 0x100000              ; Set the destination index to 0xB8000.
    mov eax, 0   			; Set the A-register to 0x1F201F201F201F20.
    mov ecx, 0x800000 	            ; Set the C-register to 500.
	shr ecx, 2
	cld
    rep stosd						 ; Clear the screen.                 ; Clear the screen.

.skipClearBSS:
	mov eax, [0x5000]
	mov ebx, [0x5004]
	mov ecx, [0x5008]

.looping:
	mov dl, [eax]
	mov [ebx], dl
	inc eax
	inc ebx

	loop .looping

	;VMWARE GETS TO AT LEAST HERE

	cli ; 8.9.2. Step 1.

	mov eax,cr0 ; 8.9.2. Step 2.
	and eax,0x7FFFFFFF	;0x7FFFFFFF
	mov cr0,eax

	mov [first32bit], byte 0

	;jmp 0x18:prot16 + 0x7c00 ; 8.9.2. Step 3.
	jmp 0x18:prot16; + 0x7E00

first32bit db 1

[BITS 16]

prot16:
	mov ax,0x0020 ; 8.9.2. Step 4.
	mov ds,ax
	mov es,ax
	mov fs,ax
	mov gs,ax
	mov ss,ax

	mov eax,cr0 ; 8.9.2. Step 2.
	and al,0xFE	
	mov cr0,eax	;FREEZE!

	;jmp 0x50:0x50

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

	jmp returnPMCopy

	push fs	
	push BX
	retf




	
bits 16
