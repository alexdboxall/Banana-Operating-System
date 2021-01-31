
; Banana Bootloader
; Copyright Alex Boxall 2020 All Rights Reserved

; This bootloader loads and runs C:/BANANA/FIRMWARE.LIB at 0000:C000
; AND loads in C:/BANANA/BANANABT somewhere else in memory
; This uses some nasty tricks to save space, and it used to use every byte,
; but I've kept optimising it (including much better usage of the BPB area),
; and now there are 95 bytes to spare!

; Some interesting optimisations:
;	Using BPB area for storing filenames (the OEM string and the bootfile string)
;	Replacing cmp ebx, 0 with test ebx, ebx
;	Removing (e.g.) add eax, 2 with inc eax; inc eax
;	Using one byte memory operations on high bytes instead of using two byte operations
;	Much smaller 'getNext' code, with better register use, less pushing, better ANDing / shifting, etc. 
;	Removed a COMPLETELY USELESS 'mov esi, eax', as si got overwritten two instructions later (and wasn't used in between!)
;	Doing some trickery to remove the 'getFAT' function call, only used twice, and one time was straight after a call to the function which called it the other time, which happens to leave the getFAT value intact for us to use 
;	We no longer tell the next stage bootloader the FS information in registers, they have to read it from 0x7C00
;	The use of the stack pointer and parity flag as an index for a loop which runs twice

org 0
bits 16

jmp short _main
nop

;	mov eax, [_bpb.logicalSectorsPerFAT]
;	mov dh, [_bpb.totalFATs]
;	mov cx, [_bpb.reservedSectors]
;	mov ebx, [_bpb.hiddenSectors]


_bpb:
	filename:						db "BANANA"			; OEM name or version
	filenamex:						db "  "				;THIS ONLY CREATES A 10 BYTE STRING, SO WE NEED TO
														;SET THE LOW BYTE OF 'BYTES PER SECTOR' TO 0x20
														;AND SET SECTORS PER CLUSTER TO 0x20

	;RERFERENCE ONLY! OVERWRITTEN BY JOIN.PY
	_bpb.bytesPerSector				dw 0x0200			; Bytes per Sector (512)
	_bpb.sectorsPerCluster			db 0x01				; Sectors per cluster (usually 1)
	_bpb.reservedSectors			dw 0x187E			; Reserved sectors
	_bpb.totalFATs					db 0x0002			; FAT copies
	_bpb.rootEntries				dw 0x0				; Root directory entries
	_bpb.fat12.totalSectors			dw 0				; Sectors in filesystem (0 for FAT16)
	_bpb.mediaDescriptor			db 0xf8				; (should be 0xF8 for a HDD)		Media descriptor type (f0 for floppy or f8 for HDD)
	_bpb.sectorsPerFAT				dw 0				;0x0009			; Sectors per FAT

	_bpb.sectorsPerTrack			dw 0x3F				; Sectors per track
	_bpb.headsPerCylinder			dw 0x20				; Heads per cylinder
	_bpb.hiddenSectors				dd 0x00000001		; Number of hidden sectors (0)
	_bpb.totalSectors				dd 0x20000			; Number of sectors in the filesystem

	;FAT32 EBPB
	_bpb.logicalSectorsPerFAT		dd 0x3C1
	_bpb.driveDescription			dw 0
	_bpb.version					dw 0
	_bpb.clusterOfRootDir			dd 2
	_bpb.fsInfoSectorSector			dw 1
	_bpb.sectorOfBootsectorCopy		dw 6
	
	filename2: db "FIRMWARELIB "			;this 12 (not 11) byte spot is actually reserved for boot filename, and I've updated join.py and INSTALLER.C to put this string here for us

	_bpb.driveNumber				db 0x80				; Sectors per FAT
	driveNumber db 0									; WE'RE NOT USING THE VALUE HERE, ONLY THE MEMORY ADDRESS
	_bpb_signature					db 0x28				; Extended signature (indicates we have serial, label, and type)
	_bpb_serial						dd 0xb3771b01		; Serial number of partition
	
DAPACK:
		db	0x10
		db	0
blkcnt:	dw	1		; int 13 resets this to # of blocks actually read/written
d_add:	dw	0x0500	; memory buffer destination address (0:7c00)
db_seg:	dw	0x0000	; in memory page zero
d_lba:	dd	0		; put the lba to read in this spot
		dd	0		; more storage bytes only for big lbas ( > 4 bytes )

_main:
	cli										;no interrupts
	cld
	mov ax, 0x07C0							; we're at 07C0:0000, so set our segment registers to that
	mov ds, ax
	mov ss, ax

	xor bp, bp								;needed for stuff later on...
	mov es, bp
	mov sp, bp

	jmp 0x7C0:setcs							;set CS so we know we're at 07C0:0000 instead of, e.g. 0000:7C00 or even 049B:3250

setcs:
	mov [_bpb.bytesPerSector - 1], dword 0x20202020		;this overwrites bytesPerSector and sectorsPerCluster

	mov [driveNumber], dl
	push es									;es is zero here. used just before we jump to stage two
	push dx									;used to reload DL at the end, will trash DH, but we set that after the pop

	xor ax, ax								;go into a text mode
	int 0x10

	;THIS SECTOR MANAGES TO USE ALL 8 GENERAL PURPOSE REGISTERS AT ONCE
	;INCLUDING THE STACK POINTE ITSELF, AND THE PARITY FLAG!

	; STACK PARITY MUST BE **EVEN** HERE, OVERWISE THE WORLD IMPLODES
	; (in reality, just replace 'jnp' with 'jp')

fileLoad:
	call getRoot							;puts in EAX
	
.retryNext:
	call readSectors						;read root

	;sector number in EAX

	mov di, 0x0500
.nextentry:
	mov si, filename
	add si, bp
	mov cx, 11

	push di
	repe cmpsb 
	pop di
	je .found
	add di, 32								;go to next entry

	cmp di, 0x8000
	jne short .nextentry

.nextsector:
	call getNext
	jmp short .retryNext

.found:
	mov [filenamex], word 0x5442			;change filename
	cmp [file2], byte 1
	jne short .sk
	mov bp, (filename2-filename)

.sk:
	;get root of directory
	xor eax, eax
	mov ax, [es:di + 0x14]					;get high start cluster
	shl eax, 16								;move to high word
	mov ax, [es:di + 0x1A]					;get low start cluster

	push eax
	call getRoot
	pop ebx
	add eax, ebx
	dec eax									;strange FAT32 thing 
	dec eax	

	dec sp									;the stack pointer is being used as a general purpose register here
	jnp short .retryNext 					;yes, we are using the parity flag (based on the stack pointer! to perform the loop twice)
	pop bx									;quicker way to add 2 to SP to clean up our mess

rootdone:
	mov ebx, [es:di + 0x1C]					;get file size
	shr ebx, 9

.readFileLoop:
	; FILE START: EAX
	; FILE SIZE  (IN SECTORS): EBX

	mov cx, [addstore]
	mov [d_add], cx
	call readSectors
	mov [d_add], word 0x500
	test ebx, ebx
	jz short fileReadDone

	push ebx
	call getNext
	pop ebx
	dec ebx
	
	add byte [addstore + 1], 0x2			;move over 512 bytes
	
	jmp short .readFileLoop

fileReadDone:
	mov bx, 0xC000
	mov [addstore], bx
	mov [filenamex], word 0x2020			;change filename
	
	inc byte [file2]
	cmp byte [file2], 2
	jne fileLoad

	pop dx									;we already pushed DX at the start with the drive number in it
											;this sets DL correctly here, trashes DH, but we set it anyway in a few lines

											;0x0000 was already pushed at the very start when we pushed ES!
	push bx									;contains 0xC000

	retf

readSectors:
	pushad
	mov [d_lba], eax
	mov ah, 0x42
	mov si, DAPACK
	mov dl, byte [driveNumber]				; The drive to read from
	int 0x13
	jc short err
	popad
	ret

addstore dw 0x7E00
file2 db 0

err:
	mov bx, 0x4			;make it red
	mov ah, 0xB
	int 0x10
	jmp short $

getRoot:
	mov eax, [_bpb.logicalSectorsPerFAT]
	mov cl, [_bpb.totalFATs]				;hopefully either 1 or 2
	dec cl									;hopefully either 0 or 1
	shl eax, cl								;multiply by 2 if cl is 1 (2 FATs)
	
	;getFAT
	movzx ebx, word [_bpb.reservedSectors]	;covert reserved sectors to 32 bit
	add ebx, [_bpb.hiddenSectors]			;add hidden sectors, WE MUST LEAVE THE FAT ADDRESS IN EBX FOR getNext TO WORK CORRECTLY

	add eax, ebx
	ret

getNext:
	;input eax
	;output: looks at FAT, finds entry number eax and returns next sector in eax

	mov edx, eax							;relies on the fact that EDX isn't used at all in getRoot/getFAT
	call getRoot
	sub edx, eax							;remove root (still in EDX)
	inc edx									;add 2 to reverse the strange '- 2' from earlier
	inc edx

	;The FAT address is STILL IN EBX, because if how getFAT and getRoot work

	mov eax, edx							;save a copy for the offset
	shr edx, 7								;SHL 2, SHR 9: 4 byte entries (<< 2) then divide by 512 to give sector offset (>> 9) (hopefully we have 512 byte sectors and 1 cluster per sector)
	add edx, ebx							;we now have the sector it is in

	mov bx, ax								;copy input offset, we only need BX cause we're going to AND off everything but 9 bits
	
	;Shorter way of doing it
	shl bx, 1								;shifting by 1 uses shorter opcode
	xor bh, bh								;instead of ANDING with 0xFF, just clear the high byte
	shl bx, 1								;do the second shift

	mov eax, edx
	call readSectors
	
	add bh, 5								;"add ebx, 0x500" (only 9 bits in ebx used due to the and statement below)

	push dword [es:bx]						;preserve it (es has zero)
	call getRoot
	pop ebx									;and restore it into a register instead of memory
	and ebx, 0x0FFFFFFF						;remove high 4 bits								
	add eax, ebx
	dec eax									;strange FAT32 thing 
	dec eax									;double dec takes less space than 32 bit subtract because it needs to have a 4 byte immediate

	ret
	
times 510 - ($-$$) db 1						;Banana thinks it is a partition table if these are 0x00, because we have a 64 byte section blank section at the end of the bootloader
											;this wouldn't be a problem usually, but because this bootsector so optimised, it leaves this massive gap at the end.
dw 0xAA55