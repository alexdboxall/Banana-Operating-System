org 0
bits 16

jmp short _main
nop

;	mov eax, [_bpb.logicalSectorsPerFAT]
;	mov dh, [_bpb.totalFATs]
;	mov cx, [_bpb.reservedSectors]
;	mov ebx, [_bpb.hiddenSectors]

;RESERVED SECTORS 0x187E
;2 FATS
;0x80 HIDDEN SECTORS
;0x1FCF sectors per FAT

_bpb:
	_bpb.oem						db "BANANAOS"		; OEM name or version
	
	;RERFERENCE ONLY! OVERWRITTEN BY JOIN.PY
	_bpb.bytesPerSector				dw 0x0200			; Bytes per Sector (512)
	_bpb.sectorsPerCluster			db 0x01				; Sectors per cluster (usually 1)
	_bpb.reservedSectors			dw 0x187E			; Reserved sectors
	_bpb.totalFATs					db 0x0002			; FAT copies
	_bpb.rootEntries				dw 0x0			; Root directory entries
	_bpb.fat12.totalSectors			dw 0			; Sectors in filesystem (0 for FAT16)
	_bpb.mediaDescriptor			db 0xf8				; (should be 0xF8 for a HDD)		Media descriptor type (f0 for floppy or f8 for HDD)
	_bpb.sectorsPerFAT				dw 0				;0x0009			; Sectors per FAT

	_bpb.sectorsPerTrack			dw 0x3F				; Sectors per track
	_bpb.headsPerCylinder			dw 0x20			; Heads per cylinder
	_bpb.hiddenSectors				dd 0x00000001		; Number of hidden sectors (0)
	_bpb.totalSectors				dd 0x20000				; Number of sectors in the filesystem

	;FAT32 EBPB
	_bpb.logicalSectorsPerFAT		dd 0x3C1
	_bpb.driveDescription			dw 0
	_bpb.version					dw 0
	_bpb.clusterOfRootDir			dd 2
	_bpb.fsInfoSectorSector			dw 1
	_bpb.sectorOfBootsectorCopy		dw 6
	times 12 db 0
	_bpb.driveNumber				db 0x80				; Sectors per FAT
	_bpb.currentHead				db 0x00				; Reserved (used to be current head)
	_bpb.signature					db 0x29				; Extended signature (indicates we have serial, label, and type)
	_bpb.serial						dd 0xb3771b01		; Serial number of partition
	_bpb.filename					db "VOLUMELABEL"	; Volume label
	_bpb.fileSystem					db "FAT32   "  ;	; Filesystem type

	filename: db "BANANA"
	filenamex: db "     "
	filename2: db "FIRMWARELIB"

align 4

DAPACK:
		db	0x10
		db	0
blkcnt:	dw	1		; int 13 resets this to # of blocks actually read/written
d_add:	dw	0x0500	; memory buffer destination address (0:7c00)
db_seg:	dw	0x0000	; in memory page zero
d_lba:	dd	0		; put the lba to read in this spot
		dd	0		; more storage bytes only for big lbas ( > 4 bytes )

driveNumber db 0 

_main:
	cli					;no interrupts
	mov ax, 0x07C0		; we're at 0000:7c00, so set our segment registers to that
	mov ds, ax

	xor sp, sp
	mov es, sp
	mov ss, ax

	mov [driveNumber], dl

fileLoad:
	call getRoot		;puts in EAX

	mov bp, 2			;1 after first time, 0 after second time
.retryNext:
	call readSectors	;read root

	;sector number in EAX

	mov di, 0x0500
.nextentry:
	mov si, filename
	add si, [fileNameOffset]
	mov cx, 11

	push di
	repe cmpsb 
	pop di
	je .found
	add di, 32			;go to next entry
	cmp di, 0x8000
	je short .nextsector
	jmp short .nextentry

.nextsector:
	call getNext
	;cmp [fileNameOffset], word 11
	;je $
	jmp short .retryNext

.found:
	mov [filenamex], word 0x5442		;change filename
	cmp [file2], byte 1
	jne .sk
	mov [fileNameOffset], byte 11		;I know it's a WORD, but we're saving space here!
.sk:
	;get root of directory
	xor eax, eax
	mov ax, [es:di + 0x14]					;get high start cluster
	shl eax, 16								;move to high word
	mov ax, [es:di + 0x1A]					;get low start cluster

	mov ebx, eax
	push ebx
	call getRoot
	pop ebx
	add eax, ebx
	dec eax		;strange FAT32 thing 
	dec eax				;e.g.
					;	(first_sector_of_cluster = ((cluster - 2) * fat_boot->sectors_per_cluster) + first_data_sector;)
	dec bp								;set flag
	jz short rootdone 					;if so, do something else

    jmp short .retryNext						;if first time, check for file again

addstore dw 0x7E00
rootdone:
	mov ebx, [es:di + 0x1C]				;get file size
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
	
	add byte [addstore + 1], 0x2		;move over 512 bytes
	;add word [addstore], 0x200		;move over 512 bytes
	
	jmp short .readFileLoop

fileReadDone:
	mov [addstore], word 0xC000
	mov [filenamex], word 0x2020		;change filename
	
	inc byte [file2]
	cmp byte [file2], 2
	jne fileLoad

	mov dl, byte [driveNumber]

	mov eax, [_bpb.logicalSectorsPerFAT]
	mov dh, [_bpb.totalFATs]
	mov cx, [_bpb.reservedSectors]
	mov ebx, [_bpb.hiddenSectors]

	push word 0x0
	push word 0xC000	;0xC000
	;push di
	retf

readSectors:
	pushad
	mov [d_lba], eax
	mov ax, 0x4200
	mov si, DAPACK
	mov dl, byte [driveNumber]			; The drive to read from
	;cld
	int 0x13
	
	;jc short err
	popad

	ret


err:
	;xor ax, ax			;go into a text mode
	;int 0x10
	;mov bx, 0x4			;make it red
	;mov ah, 0xB
	;int 0x10
	;hlt

getRoot:
	mov eax, [_bpb.logicalSectorsPerFAT]
	mov cl, [_bpb.totalFATs]				;hopefully either 1 or 2
	dec cl									;hopefully either 0 or 1
	shl eax, cl								;multiply by 2 if cl is 1 (2 FATs)
	
	call getFAT
	add eax, ebx
	ret

getFAT:
	movzx ebx, word [_bpb.reservedSectors]	;covert reserved sectors to 32 bit
	add ebx, [_bpb.hiddenSectors]			;add hidden sectors
	ret

file2 db 0
fileNameOffset dw 0

getNext:
	;input eax
	;output: looks at FAT, finds entry number eax and returns next sector in eax

	;EAX has a sector number (in this case 0x17B67)
	;but we need it as a cluster number

	mov ecx, eax

	push ecx
	call getRoot			;get root
	pop ecx

	sub ecx, eax			;remove root
	inc ecx
	inc ecx				;add 2 to reverse the strange '- 2' from earlier

	call getFAT			;return FAT address in EBX

	mov eax, ecx		;save a copy for the offset
	shr ecx, 7			;SHL 2, SHR 9: 4 byte entries (<< 2) then divide by 512 to give sector offset (>> 9) (hopefully we have 512 byte sectors and 1 cluster per sector)
	add ecx, ebx		;we now have the sector it is in

	mov ebx, eax			;copy input offset
	shl ebx, 2				;4 byte entries
	and ebx, 0b111111111	;get low 9 bytes (offset into sector)

	;ECX = sector
	;EBX = offset

	mov eax, ecx
	call readSectors
	
	add ebx, 0x500
	xor ax, ax
	mov fs, ax
	mov eax, [fs:bx]
	and eax, 0b1111111111111111111111111111	;get low 28 bits

	;now reverse the process

	mov ebx, eax
	push ebx
	call getRoot
	pop ebx
	add eax, ebx
	dec eax
	dec eax		;strange FAT32 thing 

	ret

times 510 - ($-$$) db 0
dw 0xAA55