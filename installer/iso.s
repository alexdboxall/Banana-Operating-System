
org 0
bits 16

JMP 0x7C0:main

;times 0xb800 - 3 db '&'



MAIN_DISK_IMG_MEGABYTES equ 64



D_OFFSET equ 0			;	0xb800

;TODO: IMAGE_OFFSET should be a memory address containing a value calclulated by looking at the actual filesystem for file 'OSIMAGE.SYS'
IMAGE_OFFSET equ (0x1A + 60)

;TODO: MBR_OFFSET should be a memory address containing a value calclulated by looking at the actual filesystem for file 'DEFLTMBR.BIN'
MBR_OFFSET equ (0x1A + 59)

;NOTE! CD-ROMs HAVE 2048 BYTE SECTORS
;times 16 * 0x800  db 0

;SECTOR 16 (zero based) (PRIMARY VOLUME)
;db 1
;db "CD001"
;db 1
;db 0
;db  "BANANAOS", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
;;db "BANANA OS 1.0", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
;db "BANANA OS 1 0", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
;times 8 db 0    ;8 zeros

;dd 33	;Number of Logical Blocks in which the volume is recorded
;db 0    ;MSB version
;db 0
;db 0
;db 0

;times 32 db 0

;dw 1	;The size of the set in this logical volume (number of disks).
;db 0    ;MSB version
;db 0    ;MSB version

;dw 1	;The number of this disk in the Volume Set.
;db 0    ;MSB version
;db 0    ;MSB version

;dw 2048 ;Sector size
;db 0 ;MSB version
;db 0 ;MSB version

;dw 0	;The size in bytes of the path table. 
;dw 0

;dd 0    ;Location of little endian path table
;dd 0    ;Location of optional little endian path table
;dd 0    ;Location of big endian path table
;dd 0    ;Location of optional big endian path table

;times 34 db 0       ;Directory entry
;times 128 db 0      ;Volume set ID
;times 128 db 0      ;Publisher ID
;times 128 db 0      ;Data Preparer ID
;times 128 db 0      ;Application ID
;times 38 db 0       ;Copyright File ID
;times 36 db 0       ;Abstract File ID
;times 37 db 0       ;Bibliographic File ID
;times 17 db 0       ;Date/time
;times 17 db 0       ;Date/time
;times 17 db 0       ;Date/time
;times 17 db 0       ;Date/time

;dd 0		;oops, we missed something
;db 1
;db 0
;times 512 db 0
;times 653 db 0
;times (17 * 0x800 - ($-$$)) db 0

;SECTOR 17 (BOOT RECORD VOLUME)
;db 0
;db "CD001"
;db 1
;db "EL TORITO SPECIFICATION", 0, 0, 0, 0, 0, 0, 0, 0, 0
;times 0x20 db 0
;dd 19
;times (18 * 0x800 - ($-$$)) db 0

;SECTOR 18 (VOLUME DESCRIPTOR SET TERMINATOR)
;db 255
;db "CD001"
;db 1
;times (19 * 0x800 - ($-$$)) db 0

;SECTOR 19+ (BOOT CATALOGUE)
;VALIDATION ENTRY
;db 1
;db 0		;x86
;dw 0		;reserved
;db "BANANA OS 1.0", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
;times 24 db 0 ;makes checksumming easier
;checksum dw 0xFF00 ;all the bytes in the validation entry should equal zero (includes 0x55 and 0xAA)
;db 0x55
;db 0xAA

;SECTOR 19 CONTD
;DEFAULT ENTRY
;db 0x88	
;db 0
;dw 0x7C0
;db 0	;System Type.  This must be a copy of byte 5 (System Type) from the Partition Table found in the boot image
;db 0
;dw 4		;4x512 sectors, 1x2048 sector
;dd 23		;LBA 23, but spec says Relative/Logical Block Addressing. Does this mean it should be 3 (sector 20 + 3 = 23)
;db 0
;times (21 * 0x800 - ($-$$)) db 0

;SECTOR 21
;db 0x90			;more headers follow
;db 0			;x86
;dw 1			;1 more sector follows
;times (22 * 0x800 - ($-$$)) db 0

;SECTOR 22
;db 0x88	
;db 0
;dw 0x7C0
;db 0		;System Type.  This must be a copy of byte 5 (System Type) from the Partition Table found in the boot image
;db 0
;dw 4		;two sectors
;dd 23		;LBA 23, but spec says Relative/Logical Block Addressing. Does this mean it should be 3 (sector 20 + 3 = 23)
;db 0
;times (23 * 0x800 - ($-$$)) db 0

;SECTOR 23
sector23Start:

;Prints a string				- DS=>SI points to a string
puts:
	pusha
puts_:
	lodsb				; load next byte from string from SI to AL
	or al, al			; Does AL=0?
	jz .done			; Yep, null terminator found-bail out
	mov	ah, 0eh			; Nope-Print the character
	int	10h
	jmp	puts_			; Repeat until null terminator found
.done:
	popa
	ret					; we are done, so return

putsslowcount dw 0

reboot:
	jmp 0FFFFh:0

shutdown:
	mov ax, 0x5301
	xor bx, bx
	int 0x15

	add al, 0xE
	inc bx
	mov cx, 1
	int 0x15

	sub al, 8
	add cl, 2
	int 0x15

	mov cx, 0xF
	mov dx, 0x4240
	mov ah, 0x86
	int 0x15

	jmp reboot
	
align 4
DAPACK:
aaaaL: db	0x10
	db	0
blkcnt:	dw	4			; int 13 resets this to # of blocks actually read/written
db_add:	dw	0x0		; memory buffer destination address (7C0:800)
db_seg:	dw	0x7C0			; in memory page zero
d_lba:	dd	0x1A		; put the lba to read in this spot
d_biglbaA:	dd	0		; more storage bytes only for big lbas ( > 4 bytes )
d_biglbaB:	dd	0		; more storage bytes only for big lbas ( > 4 bytes )

	DAEND:

main:
	cli
	mov ax, 0x7C0
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov ax, 0x500
    mov ss, ax
    mov sp, 0			;will wrap around to 0xFFFF and on...
    ;sti

	mov ax, 0
	mov fs, ax
	mov [fs:0x4000], byte 0xFE
	mov [fs:0x4001], byte dl

	jmp over
	driveNumber db 0
	introText db 0xA, 0xD, "  Press any key to boot from CD-ROM", 0
	spaceBarRetry db 4
	dot db ".", 0

FlushKeybuffer:
	pushad
.retry:
	mov ah, 1
    int 0x16
	jz .endflushbuf
	mov ah, 0
    int 0x16
	jmp .retry
.endflushbuf:
	popad
	ret

over:
	mov [driveNumber - D_OFFSET], dl

	mov ax, 3
	int 0x10

	mov si, introText - D_OFFSET
	call puts

.retrySpacebar
	mov cx, 0x6
	mov dx, 0x7240
	mov ah, 0x86
	int 0x15
    mov ah, 1
    int 0x16
    cmp ah, 1
	jg BootFromCD

	mov cx, 0x6
	mov dx, 0x7240
	mov ah, 0x86
	int 0x15
    mov ah, 1
    int 0x16
    cmp ah, 1
	jg BootFromCD

	pusha
	mov si, dot - D_OFFSET
	call puts
	popa

	dec byte [spaceBarRetry - D_OFFSET]
	cmp byte [spaceBarRetry - D_OFFSET], 0
	jne .retrySpacebar

DontBootFromCD:
	call ResetScreen
	mov si, manualReset2
	call puts

	int 0x18				;ask to skip this disk and continue booting
	int 0x19				;reset just in case of failure
	jmp shutdown			;shutdown, just in case of failure
	cli
	hlt						
	jmp DontBootFromCD		;loop, just in case of failure

manualReset2 db 0xA, 0xA, 0xD, "  To boot from the hard drive, eject the CD.", 0xA, 0xD, "  Then manually restart your computer by turning it off and on again.", 0xA, 0xA, 0xA, 0xA, 0xA, 0xA, 0xA, 0xA, 0xA, 0xA, 0xA, 0xA, 0xD, 0

BootFromCD:
;blkcnt:	dw	4			; int 13 resets this to # of blocks actually read/written
;db_add:	dw	0x8400		; memory buffer destination address (7C0:800)
;db_seg:	dw	0			; in memory page zero
;d_lba:	dd	0x1A + 1		; put the lba to read in this spot


	;TODO: read the boot sector start point
	;	   using one of the CD-ROM headers (sector 17?)

	;start by reading in sector 17, so we can get the location of the boot image


	;COPY PROTECTION:
	;We are going to READ data from a sector larger than the disk image size to ensure that
	;it is from a bigger disk (a real one). I would like to test 4GB instead of 256MB, but 
	;I think the BIOS only supports 28 bit LBA, which only allows up to 256MB (I think...)
	;This will only prevent naive emulation (padding the disk image will get around it) and people
	;copying onto disks between 64MB and 255MB in size (not many, if any)

	mov [blkcnt - D_OFFSET], word 4		;read one sector from the CDROM
	mov [db_add - D_OFFSET], word 0xF000			;stick it at 0x8000:0
	mov [db_seg - D_OFFSET], word 0
	;mov [d_lba  - D_OFFSET], dword 0x1FF 		;the HDD image is stored at sector 60 on the CDROM
	;mov [d_lba], dword 0xFFFFFFFF
	;mov [d_biglbaA], dword 0x1FFFFF
	;mov [d_biglbaB], dword 0

	;mov si, DAPACK - D_OFFSET		; address of "disk address packet"
	;mov ah, 0x42		; AL is unused
	;mov al, 0
	;mov dl, [driveNumber - D_OFFSET]		; drive number 0 (OR the drive # with 0x80)
	;clc
	;int 0x13		;this is supposed to work
	;jc itsAFake		;it it failed, it is fake
	
	
	jmp notFake

copyprotectMsg db 0xA, 0xD, " DRM failed. ", 0
itsAFake:
	call ResetScreen
	mov si, copyprotectMsg
	call puts
	jmp $
	cli
	hlt
	jmp itsAFake
	jmp itsAFake
	cli
	hlt
	jmp $


ResetScreen:
	mov ax, 3
	int 0x10

	;CHANGE PALETTE
	;(we are changing black into blue)
	mov ax, 0x1000
	mov bl, 0x0
	mov bh, 0x01
	int 0x10

	mov al, 0x39
	out 0x72, al

	mov ah, 1
	mov ch, 0x3f
	int 0x10

	ret


notFake:
	mov [blkcnt - D_OFFSET], word 1			;read one sector from the CDROM
	mov [db_add - D_OFFSET], word 0x7000			;stick it at 0x8000:0
	mov [db_seg - D_OFFSET], word 0
	mov [d_lba  - D_OFFSET], dword 17	;	17 		;the HDD image is stored at sector 60 on the CDROM

	mov si, DAPACK - D_OFFSET		; address of "disk address packet"
	mov ah, 0x42		; AL is unused
	mov al, 0
	mov dl, [driveNumber - D_OFFSET]		; drive number 0 (OR the drive # with 0x80)
	int 0x13


	mov [blkcnt - D_OFFSET], word 16			;read one sector from the CDROM
	mov [db_add - D_OFFSET], word 0x7C00 + 0x800			;stick it at 0x8000:0
	mov [db_seg - D_OFFSET], word 0
	mov ax, 0
	mov fs, ax

	;either one works
	mov eax, [fs:0x7047]				;location of the location of the boot image
	inc eax

	;mov eax, 0x1A

	mov eax, 0x803A
	inc eax			;do not overwrite the already loaded in sectors
	mov [d_lba  - D_OFFSET], dword eax 		;the HDD image is stored at sector 60 on the CDROM

	mov si, DAPACK - D_OFFSET		; address of "disk address packet"
	mov ah, 0x42		; AL is unused
	mov al, 0
	mov dl, [driveNumber - D_OFFSET]		; drive number 0 (OR the drive # with 0x80)
	int 0x13
	jc short $

	mov [db_add - D_OFFSET], word 0x8400			;stick it at 0x8000:0
	mov [db_seg - D_OFFSET], word 0

	mov [blkcnt - D_OFFSET], word 4
	mov ax, 0x7C0
	mov bx, 0x7C0
	mov ds, bx
	mov es, ax
	mov fs, ax
	mov gs, ax

	call FlushKeybuffer
	jmp Stage3


putsslow:
mov [putsslowcount - D_OFFSET], byte 0
pusha
putsslow_:
lodsb                ; load next byte from string from SI to AL
or al, al            ; Does AL=0?
jz .done            ; Yep, null terminator found-bail out
mov    ah, 0eh            ; Nope-Print the character
int    10h

cmp al, 205
je .skipDelay
cmp [putsslowcount - D_OFFSET], word 20
jle .skipDelay

pusha
MOV     CX, 0 ;0x1
MOV     DX, 0x8000
MOV     AH, 0x86
INT     15H
popa

.skipDelay:
;inc word [putsslowcount - D_OFFSET]
jmp    putsslow_            ; Repeat until null terminator found
.done:
popa
ret                    ; we are done, so return


puts512:
mov [countA - D_OFFSET], word 512
pusha
puts512_:
lodsb                ; load next byte from string from SI to AX
cmp [countA - D_OFFSET], word 0
je .done            ; Yep, null terminator found-bail out
dec word [countA - D_OFFSET]
mov    ah, 0eh            ; Nope-Print the character
int    10h
jmp    puts512_            ; Repeat until null terminator found
.done:
popa
ret                    ; we are done, so return


;IN = ECX: sector number
;OUT = EDX: read sucessful
timeXX db 0
checkSector:
    push eax
    push ebx
	push ecx

    mov ah, 0x42
	mov al, 0
	mov dl, byte [HDDNumber - D_OFFSET]
	mov [BLK2 - D_OFFSET], dword 1			;read 1 sector
	mov si, HDDZEROPACKET2 - D_OFFSET			;packet address
	mov [RDF2 - D_OFFSET], dword ecx			;sector ecx
	int 0x13

	cmp ah, 0
	je AAgood
	jmp AAbad

AAgood:
	pop ecx
	mov edx, 1
	jmp AAdone

AAbad:
	pop ecx
	mov edx, 0
	jmp AAdone

AAdone:
    pop ebx
    pop eax
    ret

	bbbb:

getSizeOfDisk:
    mov eax, 1      ;check
    mov ebx, 0      ;add on
    mov ecx, 0      ;scratch

.loopagain:
    mov ecx, eax
    add ecx, ebx            ;combine check with add on

	cmp ecx, 0x3FFFFFFF		;0xFFFFF
	ja .retEarly
    call checkSector        ;IN ECX-sector number, OUT EDX-sector valid?
                            ;MUST PRESERVE EAX + EBX
    shl eax, 1              ;multiply by 2
    cmp edx, 1
    je .itworks

    shr eax, 2              ;undo the multiply by 2 and the last one
    add ebx, eax            ;add to add-on register
    mov eax, 1              ;reset check register

    jmp .loopagain

.itworks:
	mov ecx, eax			;reset sectors
	shr ecx, 1				;remove the *2 just for this
    add ecx, ebx            
    add ecx, 1              ;but add one to go to the next sector
    call checkSector

    cmp edx, 0              ;and it now does not work
    je .end                 ;that must be the last sector!

    jmp .loopagain

.retEarly
	;mov eax, 0x7FFFFFF0
	ret

.end:
	mov ecx, eax			;generate sector again
	shr ecx, 1				;remove the *2 just for this
    add ecx, ebx            ;add the add on
	
    mov eax, ecx
    ret

Stage3:
	call ResetScreen
	mov si, Stage3Msg - D_OFFSET

	mov si, FirstHDDMsg - D_OFFSET

JumpBacktoStage3Loop:
	call FlushKeybuffer

.AwaitKeyPress:
	xor ax, ax
	;int 0x16

	cmp ah, 0x1C
	;je Stage4
	cmp ah, 0x0F

	jmp Stage5

	cmp ah, 0x01
	je partviewr;shutdown
	
	;cmp ah, 6
	;jmp StartSysctrl

	;cmp ah, 4		;pressing '3' will use the third hard drive
	;je ThirdHDD

	;cmp ah, 5		;pressing '4' will use the fourth hard drive
	;je FourthHDD

	jmp .AwaitKeyPress


hexdig db "0123456789ABCDEF", 0
outstr db "** ", 0
partvmsg db "Contents of partition table shown below in hex.", 0xA, 0xD, "In other words, SECTOR 0 at OFFSET 0x1BE", 0xA, 0xA, 0xD, 0xD, \
"ACT         TYPE        LBA FIRST   SIZE", 0xA, 0xD, 0
;000111000111000111000111000111000111
newln db 0xA, 0xD, 0

partviewr:
	call ResetScreen
	mov si, partvmsg
	call puts

	mov ah, 0x42
	mov al, 0
	mov dl, byte [HDDNumber - D_OFFSET]
	mov [BLK2 - D_OFFSET], dword 1
	mov si, HDDZEROPACKET2 - D_OFFSET
	int 0x13

	mov ax, 0x700
	mov fs, ax

	mov si, 0x1BE
	mov bx, hexdig

.looping:
	mov dl, [fs:si]

	mov al, dl
	and al, 15
	xlat
	mov [outstr + 1], byte al

	mov al, dl
	shr al, 4
	xlat
	mov [outstr], byte al

	pusha
	mov si, outstr
	call puts
	popa

	pusha
	mov cx, si
	add cx, 2
	and cx, 15
	cmp cx, 15
	jne .skipNewline
	mov si, newln
	call puts

	.skipNewline
	popa

	inc si
	cmp si, 0x200
	jne .looping


	mov ax, 0
	int 0x16
	mov ax, 0
	mov fs, ax

Stage4:
	call ResetScreen
	call Stage4ScreenReset

	mov cx, 0xF
	mov dx, 0x4240
	mov ah, 0x86
	int 0x15
	
	mov ah, 0x8
	mov dl, byte [HDDNumber - D_OFFSET]
	int 0x13
	cmp dl, 0
	jle BailOut_NoHardDrive

	mov ah, 2h
	mov al, 1
	mov cx, 1
	mov dh, 0
	mov dl, byte [HDDNumber - D_OFFSET]
	xor bx, bx
	mov es, bx
	mov bx, 0x6000
	clc
	int 0x13
	jc BailOut_NoHardDrive

	inc byte [Stage4NoDone - D_OFFSET]

	call Stage4ScreenReset
	
	
	;CHECK CPU HERE...

	pushfd                               ;Save EFLAGS
    pushfd                               ;Store EFLAGS
    xor dword [esp],0x00200000           ;Invert the ID bit in stored EFLAGS
    popfd                                ;Load stored EFLAGS (with ID bit inverted)
    pushfd                               ;Store EFLAGS again (ID bit may or may not be inverted)
    pop eax                              ;eax = modified EFLAGS (ID bit may or may not be inverted)
    xor eax,[esp]                        ;eax = whichever bits were changed
    popfd                                ;Restore original EFLAGS
    and eax,0x00200000                   ;eax = zero if ID bit cannot be changed, else non-zero
	
	cmp eax, 0
	je BailOut_BadCPU



	inc byte [Stage4NoDone - D_OFFSET]

	call Stage4ScreenReset

	mov ecx, 0
	call checkSector
	cmp edx, 0
	je BailOut_NoFloppyDrive

	inc byte [ScannedHDDScanningFloppy - D_OFFSET]

	call Stage4ScreenReset
	inc byte [Stage4NoDone - D_OFFSET]

	call Stage4ScreenReset
	inc byte [ScannedHDDScanningFloppy - D_OFFSET]

	call Stage4ScreenReset
	inc byte [Stage4NoDone - D_OFFSET]

	call Stage4ScreenReset

	call getSizeOfDisk
	cmp eax, 1024 * 2 * MAIN_DISK_IMG_MEGABYTES
	jl BailOut_BadHardDriveSize

diskpassed:

	inc byte [ScannedHDDScanningFloppy - D_OFFSET]

	call Stage4ScreenReset
	inc byte [Stage4NoDone - D_OFFSET]

	call Stage4ScreenReset
	
	call TestRAM			;bails out for us if needed
	inc byte [Stage4NoDone - D_OFFSET]
	call Stage4ScreenReset

	mov cx, 0xF
	mov dx, 0x4240
	mov ah, 0x86
	int 0x15

	jmp Stage5

ramtable:
times 24 * 64 db 0

TestRAM:
	pusha
	mov ax, ds
	mov es, AX
	mov di, ramtable
	call do_e820

	mov cx, bp
	mov di, ramtable
	mov eax, 0		;total RAM

.loopingback:
	;0-3 LOCATION (LOW)
	;4-7 LOCATION (HIGH)
	;8-11 SIZE (LOW)
	;12-15 SIZE (HIGH)
	;16-19 TYPE

	mov ebx, dword [di + 8]			;size LOW
	mov edx, dword [di + 12]		;size HIGH
	mov esi, dword [di + 16]		;TYPE

	cmp esi, 1
	jne .bad

	cmp edx, 0
	jne .veryLargeAmountOfRAM		;if the high DWORD is set, there must be at least 4GB (a whole heap of ram)

	add eax, ebx

.bad:
	add di, 24
	loop .loopingback

	cmp eax, 450 * 1024 * 1024
	jb BailOut_NotEnoughRAM

	popa
	ret

.veryLargeAmountOfRAM:
	popa
	ret			;any more than 4GB of usable RAM is very good

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
	clc			; there is "jc" on end of list to this point, so the carry must be cleared
	ret
.failed:
	stc			; "function unsupported" error exit
	ret


Stage4ScreenReset:
	pusha

	mov ah, 2
	mov bh, 0
	mov dx, 0
	int 0x10

	;call ResetScreen

	mov si, Title2
	sub si, D_OFFSET
	call puts

	mov si, Stage4Msg
	sub si, D_OFFSET
	call puts

	mov cx,	70
.lp:
	mov si, Line
	sub si, D_OFFSET
	call puts
	loop .lp

	mov si, Stage4MsgP2
	sub si, D_OFFSET
	call puts

	mov ch, 0
	mov dh, 0
	mov cl, [Stage4NumberOfTests - D_OFFSET]
	mov dl,	[Stage4NoDone - D_OFFSET]
	mov bx, 0

drawTests:
	cmp	bx, dx
	je .drawCurrent
	jle .drawDone
	jmp .drawProg

.drawCurrent:
	mov si, ScanDoingSymbol
	sub si, D_OFFSET
	call puts
	jmp .drawName

.drawDone:
	mov si, ScanDoneSymbol
	sub si, D_OFFSET
	call puts
	jmp .drawName

.drawProg:
	mov si, ScanProgSymbol
	sub si, D_OFFSET
	call puts
	jmp .drawName

.drawName:
	shl bx, 1		;pointer table goes up in twos, so multiply by two
	mov si, [TESTS - D_OFFSET + bx]		;the table subtracts D_OFFSET for us
	call puts
	shr bx, 1

	inc bx
	cmp bx, cx
	je .end
	jmp drawTests

	mov si, FourBlank - D_OFFSET
	call puts
	
.end:
	mov cx, 14
	sub cx, [Stage4NumberOfTests - D_OFFSET]

.lp3:
	mov si, Newline - D_OFFSET
	call puts
	loop .lp3

	mov si, FourBlank - D_OFFSET
	call puts

	mov cx,	70
.lp4:
	mov si, Line
	sub si, D_OFFSET
	call puts
	loop .lp4

	mov si, Newline
	sub si, D_OFFSET
	call puts

	mov bx, [Stage4NoDone - D_OFFSET]
	add bx, [ScannedHDDScanningFloppy - D_OFFSET]
	shl bx, 1		;pointer table goes up in twos, so multiply by two
	mov si, [TESTSPERCENT - D_OFFSET + bx]		;the table subtracts D_OFFSET for us
	call puts

	mov ax, 6

	mov dx, 0
	mov cx, [Stage4NoDone - D_OFFSET]
	add cx, [ScannedHDDScanningFloppy - D_OFFSET]
.lp6:
	add dx, ax
	loop .lp6

	mov cx, dx
	cmp cx, 0
	je .lp5e
	add cx, 2
.lp5:
	mov si, percentDoneBlock
	sub si, D_OFFSET
	call puts
	loop .lp5
	jmp .lee

.lp5e:
	mov si, percentLeftBlock
	sub si, D_OFFSET
	call puts
	mov si, percentLeftBlock
	sub si, D_OFFSET
	call puts

.lee:
	mov cx, 52
	sub cx, dx
	cmp cx, 0
	jle .lp7e
	add cx, 2
.lp7:
	mov si, percentLeftBlock
	sub si, D_OFFSET
	call puts
	loop .lp7

	jmp .eee

.lp7e:
.eee:
	mov cx, 0x6
	mov dx, 0x4240
	mov ah, 0x86
	;int 0x15
	popa
	ret




BailOut:
	call ResetScreen
	mov si, BailedOut
	sub si, D_OFFSET
	call puts
	ret

BailOut_NotEnoughRAM:
	call BailOut
	mov si, BailOut_NotEnoughRAMMsg - D_OFFSET
	call puts
	jmp BailOver

BailOut_BadCPU:
	call BailOut
	mov si, BailOut_BadCPUMsg - D_OFFSET
	call puts
	jmp BailOver

BailOut_NoHardDrive:
	call BailOut
	mov si, BailOut_NoHardDriveMsg - D_OFFSET
	call puts
	jmp BailOver

BailOut_NoFloppyDrive:
	call BailOut
	mov si, BailOut_NoFloppyDriveMsg - D_OFFSET
	call puts
	jmp BailOver

BailOut_BadHardDriveSize:
	call BailOut
	mov si, BailOut_BadHardDriveSizeMsg - D_OFFSET
	call puts
	jmp BailOver

BailOver:
	mov si, BailOut_Msg - D_OFFSET
	call puts

	mov cx, 0x6
	mov dx, 0x4240
	mov ah, 0x86
	int 0x15

.o:
	mov ax, 1
	int 0x16

	cmp ah, 0x01
	je shutdown

	jmp .o





DAPACKA:
dw 1Ah
dw 0
dd 0
dd 0
dd 0
drivesectors: dd 0
dd 0
dw 0


OFFSET_A dd 0
OFFSET_B dd 0

Stage5:
	cmp [OFFSET_A], dword 0
	je .p1
	jmp .p2

.p1:
	mov ebx, osimageString
	mov cx , 12				;must include null terminator
	mov [cdReturnSpot], byte 0
	call readFromCD
	jmp Stage55

.p2:
	mov ebx, bootprogString
	mov cx , 12				;must include null terminator
	mov [cdReturnSpot], byte 0
	call readFromCD
	
	jmp Stage55

Stage55:
	cmp [OFFSET_A], dword 0
	je .pp1
	jmp .pp2

.pp1:
	mov [OFFSET_A], eax
	jmp Stage5

.pp2:
	mov [OFFSET_B], eax

	mov eax, [OFFSET_A]

	mov bx, 0
	mov fs, bx
	mov bx, 0x7B00

	mov [fs:bx], byte 0x10
	inc bx
	mov [fs:bx], byte 0
	inc bx
	mov [fs:bx], word 8	;count
	add bx, 2
	mov [fs:bx], word 0x0	;add
	add bx, 2
	mov [fs:bx], word 0xC00	;seg
	add bx, 2
	mov [fs:bx], EAX		;lba
	add bx, 4
	mov [fs:bx], dword 0
	add bx, 4
	mov [fs:bx], dword 0
	add bx, 4

	mov dl, [driveNumber - D_OFFSET]		; drive number 0 (OR the drive # with 0x80)
	push ds
	mov ax, 0
	mov ds, ax
	mov si, 0x7B00		; address of "disk address packet"
	
	mov ah, 0x42		; AL is unused
	mov al, 0
	int 0x13
	pop ds
	jc DiskErrorCDROM


	mov eax, [OFFSET_B]

	mov bx, 0
	mov fs, bx
	mov bx, 0x7B00

	mov [fs:bx], byte 0x10
	inc bx
	mov [fs:bx], byte 0
	inc bx
	mov [fs:bx], word 32	;count
	add bx, 2
	mov [fs:bx], word 0x0	;add
	add bx, 2
	mov [fs:bx], word 0x5000	;seg
	add bx, 2
	mov [fs:bx], EAX		;lba
	add bx, 4
	mov [fs:bx], dword 0
	add bx, 4
	mov [fs:bx], dword 0
	add bx, 4

	mov dl, [driveNumber - D_OFFSET]		; drive number 0 (OR the drive # with 0x80)
	push ds
	mov ax, 0
	mov ds, ax
	mov si, 0x7B00		; address of "disk address packet"
	
	mov ah, 0x42		; AL is unused
	mov al, 0
	int 0x13
	pop ds
	jc DiskErrorCDROM

	mov dl, byte [driveNumber]
	mov dh, 0

	push word 0x0
	push word 0xC000	;0xC000

	retf


	;call LicenseAgreement
	;call ProductKey

Stage555:

.StageWhat:
	call Stage100

	mov ax, 9
	mov dl, [HDDNumber - D_OFFSET]	
	int 0x13						;reset drive

	mov ax, 0xD
	mov dl, [HDDNumber - D_OFFSET]
	int 0x13

	call ResetScreen
	mov si, Title - D_OFFSET
	call puts

	mov si, Stage5Msg - D_OFFSET
	call puts

	call FlushKeybuffer

.AwaitKeyPress:
	xor ax, ax
	int 0x16

	cmp ah, 0x1C
	je Stage6
	cmp ah, 0x01
	je shutdown
	cmp ah,	0x0E		;ah, 0x2E		;pressing 'C' will go back a step
	je .StageWhat			;this is call Stage100 is CALLED to, not jumped to
	jmp .AwaitKeyPress


%include "include/stage6.inc"






Stage7:
	jmp Stage8


	reservedSectors dw 0
	numberOfFATs db 0
	sectorsPerFATOld dd 0
	sectorsPerFATNew dd 0

	oldDataStartOffset dd 0
	newDataStartOffset dd 0


%include "include/stage8.inc"

Stage9:
	jmp goodDone
	
	
	;write product key to sector 1 of partition
	pusha
	;read sector 1 of selected partition
	mov ecx, [selectedSpaceLBA - D_OFFSET]
	
	mov [blkcnt - D_OFFSET], word 1
	mov [db_add - D_OFFSET], word 0x7000	;stick it at 0x8000:0
	mov [db_seg - D_OFFSET], word 0
	mov eax, [selectedSpaceLBA - D_OFFSET]
	inc eax
	mov [d_lba  - D_OFFSET], eax
	mov si, DAPACK - D_OFFSET		; address of "disk address packet"
	mov ah, 0x42		; AL is unused
	mov dl, [driveNumber - D_OFFSET]		; drive number 0 (OR the drive # with 0x80)
	int 0x13
	je DiskErrorHDDB

	mov ax, 0
	mov fs, ax
	mov bx, 0
	mov cx, 20			;20 just in case
.startCopyLoop:
	mov al, [fs:0x600 + bx]			;read from product key
	mov [fs:0x7020 + bx], al		;write to 0x20 into the sector
	inc bx
	loop .startCopyLoop

	;write modified sector back
	mov [blkcnt - D_OFFSET], word 1
	mov [db_add - D_OFFSET], word 0x7000	;stick it at 0x8000:0
	mov [db_seg - D_OFFSET], word 0
	mov eax, [selectedSpaceLBA - D_OFFSET]
	inc eax
	mov [d_lba  - D_OFFSET], eax
	mov si, DAPACK - D_OFFSET		; address of "disk address packet"
	mov ah, 0x43
	mov al, 0
	mov dl, [driveNumber - D_OFFSET]		; drive number 0 (OR the drive # with 0x80)
	int 0x13
	je DiskErrorHDDB

	popa


goodDone:
	call ResetScreen

	mov si, donetitle - D_OFFSET
	call puts

	mov si, donemsg - D_OFFSET
	call puts

	;forces the kernel to the first time, should not be required, but on real H/W sometimes this is needed when there was a previous install
	mov ax, 0
	mov fs, ax
	mov [fs:0xFDEC], byte 0x04
	mov [fs:0x401], byte 0xFD

	call FlushKeybuffer

	jmp .dorebootOrMoreOn

.AwaitKeyPress:
	xor ax, ax
	int 0x16

	cmp ah, 0x1C
	je .dorebootOrMoreOn
	jmp .AwaitKeyPress

.dorebootOrMoreOn:
	call ResetScreen
	mov si, manualReset
	call puts

	mov ah, 2
	mov al, 1
	mov ch, 0
	mov cl, 1
	mov dh, 0
	mov dl, 0x80
	mov bx, 0x7C0
	mov es, bx
	mov bx, 0
	int 0x13
	jc .oldWay

	push word 0x7C0
	push word 0x0
	mov dl, 0x80
	retf
.oldWay:
	int 0x18		;move to next disk in boot sequence (e.g. HDD which banana is now on)
	int 0x19		;move to next disk in boot sequence (e.g. HDD which banana is now on)

	call reboot		;in case of failure
	jmp $			;in case of failure
	
manualReset db 0xA, 0xA, 0xD, "   Please manually restart your computer by turning it off and on again.", 0xA, 0xD, "   Boot to the hard drive by changing BIOS settings or by", 0xA, 0xD, "   ejecting the installation disk now, then reinserting it later.", 0xA, 0xA, 0xA, 0xA, 0xA, 0xA, 0xA, 0xA, 0xA, 0xA, 0xA, 0xD, 0


	align 4
HDDZEROPACKET:
	db 0x10
	db 0
BK_:dw 1
	dw ZeroedBuffer - D_OFFSET			;offset
	dw 0x7C0							;segment
RDF:	dd 0
	dd 0

		align 4
HDDZEROPACKET2:
	db 0x10
	db 0
BLK2:	dw 4
BLK2OFF	dw 0			;offset
BLK2SEG	dw 0x700		;segment
RDF2:	dd 0
	dd 0

;[in AX=LBA Sector]
;[out DX,CX]

LBACHS:
          xor     dx, dx                              ; prepare dx:ax for operation
          div     WORD [bpbSectorsPerTrack - D_OFFSET]           ; calculate
          inc     dl                                  ; adjust for sector 0
          mov     BYTE [absoluteSector - D_OFFSET], dl
          xor     dx, dx                              ; prepare dx:ax for operation
          div     WORD [bpbHeadsPerCylinder - D_OFFSET]          ; calculate
          mov     BYTE [absoluteHead - D_OFFSET], dl
          mov     BYTE [absoluteTrack - D_OFFSET], al
          ret

bpbSectorsPerTrack dw 18
bpbHeadsPerCylinder dw 2
absoluteHead db 0
absoluteTrack db 0
absoluteSector db 0

LBAtoCHS:
	xor cx, cx
	xor dx, dx
	div word [sectorspertrack - D_OFFSET]
	inc dx
	mov cl, dl
	xor dx, dx
	div word [heads - D_OFFSET]
	mov dh, dl
	mov ch, al
	xor dl, dl
	ret


DiskErrorCDROM:
	push ax

	call ResetScreen
	mov si, ErrorMessageCDROM - D_OFFSET
	jmp ErrorCommon
	
DiskErrorHDDA:
	push ax
	call ResetScreen
	mov si, ErrorMessageHarddriveA - D_OFFSET
	jmp ErrorCommon

DiskErrorHDD:
DiskErrorHDDB:
	push ax
	call ResetScreen
	mov si, ErrorMessageHarddriveB - D_OFFSET
	jmp ErrorCommon
	
DiskErrorReset:
	push ax
	
	call ResetScreen
	mov si, ErrorMessageReset - D_OFFSET
	jmp ErrorCommon
	
ErrorCommon:
	call puts

	pop ax
	mov al, ah
	mov ah, 0

	cmp ax, 0
	je .noLoop

.looping:
	push ax
	mov si, Dot - D_OFFSET
	call puts
	pop ax

	dec ax
	cmp ax, 0

	je .noLoop
	jmp .looping
	
.noLoop:
	mov si, Bracket - D_OFFSET
	call puts
	jmp $

sectorspertrack dw 18
heads dw 2

FirstHDD:
	mov si, FirstHDDMsg - D_OFFSET
	call puts

	mov byte [HDDNumber - D_OFFSET], 0x80
	jmp JumpBacktoStage3Loop

SecondHDD:
	mov si, SecondHDDMsg - D_OFFSET
	call puts

	mov byte [HDDNumber - D_OFFSET], 0x81
	jmp JumpBacktoStage3Loop

ThirdHDD:
	mov si, ThirdHDDMsg - D_OFFSET
	call puts

	mov byte [HDDNumber - D_OFFSET], 0x82
	jmp JumpBacktoStage3Loop

FourthHDD:
	mov si, FourthHDDMsg - D_OFFSET
	call puts

	mov byte [HDDNumber - D_OFFSET], 0x83
	jmp JumpBacktoStage3Loop

InitDisk:
	pusha

	mov ah, 9
	mov dl, [HDDNumber - D_OFFSET]
	int 0x13

	popa
	ret


align 4
HDDZEROPACKET3:
	db 0x10
	db 0
BLK3:	dw 1
	dw 0			;offset
SEG3:	dw 0x700		;segment
RDF3:	dd 0
	dd 0
	

		 
align 4
PACKET:
	db	0x10
	db	0
Ablkcnt:	dw	1		; int 13 resets this to # of blocks actually read/written
Adb_add:	dw	0x200		; memory buffer destination address (0:7c00)
Adb_seg:	dw	0		; in memory page zero
Ad_lba:	dd	0		; put the lba to read in this spot
	dd	0		; more storage bytes only for big lbas ( > 4 bytes )

	
BOOTNOW:
	pusha
	mov di, 5
.RETRYC:
	mov ah, 0x42
	mov dl, 0x80
	mov [BLK3 - D_OFFSET], dword 1
	mov si, HDDZEROPACKET3 - D_OFFSET
	mov ebx, [debugSectorNumber - D_OFFSET]
	mov [RDF3 - D_OFFSET], dword ebx
	mov [SEG3 - D_OFFSET], word 0x7C0
	int 0x13
	jnc .DONEC

	xor ax, ax
	int 0x13

	dec di
	cmp di, 0
	je DiskErrorHDDB
	jmp .RETRYC
.DONEC:
	popa
	
	mov dl, 0x80
	jmp 0x7C0:0x0



%include "include/productkey.inc"
%include "include/license.inc"
%include "include/partitions.inc"

	
		;************************************************;
; Reads a series of sectors
; CX=>Number of sectors to read
; EAX=>Starting sector
; ES:EBX=>Buffer to read to
;************************************************;

WriteSectors:
	call ResetScreen
	jmp $


WriteSectorsForZeroing:
	cmp cx, 0x3F
	jl .MAIN
	mov cx, 0x3F
     .MAIN:
          mov     di, 0x0005                          ; five retries for error
     .SECTORLOOP:
          push    eax
          push    bx
          push    cx
		  
		  ;mov [blkcnt], word cx
		  ;mov [d_lba ], dword eax
		  ;mov [db_add], word bx
		  ;mov [db_seg], word es

		  mov [RDF - D_OFFSET], eax
	
		  pusha
		  mov ah, 0x43
		  mov al, 0
		  mov dl, [HDDNumber - D_OFFSET]
		  mov si, HDDZEROPACKET - D_OFFSET
		 
		  int 0x13
		  popa

          jnc     .SUCCESS                            ; test for read error
		  
          xor     eax, eax                              ; BIOS reset disk
          int     0x13                                ; invoke BIOS
          dec     di                                  ; decrement error counter
		  cmp di, 0
		  je .FAIL
          pop     cx
          pop     bx
          pop     eax
          jnz     .SECTORLOOP                         ; attempt to read again
          int     0x18
     .SUCCESS:
          pop     cx
          pop     bx
          pop     eax
          add     bx, 512							 ; queue next buffer
          inc     eax                                  ; queue next sector
          loop    .MAIN                               ; read next sector
          ret
	.FAIL:
		jmp DiskErrorHDD


sysctrlstr db "FIRMWARE.LIB", 0
cdReturnSpot db 0
StartSysctrl:
	mov ebx, sysctrlstr
	mov cx, 12				;must include null terminator
	mov [cdReturnSpot], byte 1
	call readFromCD

	jmp $

cdR:
	sti
	mov sp, 0		;'cheat'
	mov bx, es
	mov fs, bx
	mov [blkcnt - D_OFFSET], word 8	;read one sector from the CDROM
	mov [db_add - D_OFFSET], word 0xC000		;stick it at 0x8000:0
	mov [db_seg - D_OFFSET], word 0x000	
	mov [d_lba  - D_OFFSET], eax 		;the HDD image is stored at sector 60 on the CDROM
	mov si, DAPACK - D_OFFSET		; address of "disk address packet"
	mov ah, 0x42		; AL is unused
	mov al, 0
	mov dl, [driveNumber - D_OFFSET]		; drive number 0 (OR the drive # with 0x80)
	int 0x13
	jc DiskErrorCDROM

	mov dl, byte [driveNumber]
	mov dh, 0

	jmp $

	push word 0x0
	push word 0xC000	;0xC000
	retf

%include "include/isowrapper.inc"

%include "include/define.inc"

;SECTOR 60 - ??? (15360 * 2 CDROM SECTORS)

times 2048 - 512 db 0
;times (60 * 0x800) - ($-$$) db 0


align 64
isoDriver:
