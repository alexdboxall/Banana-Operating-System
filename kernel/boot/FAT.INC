
align 16
DAPACK:
		db	0x10
		db	0
blkcnt:	dw	1		; int 13 resets this to # of blocks actually read/written
d_add:	dw	0x7E00	; memory buffer destination addressd
db_seg:	dw	0x0000	; in memory page zero
d_lba:	dd	0		; put the lba to read in this spot
		dd	0			; more storage bytes only for big lbas ( > 4 bytes )

taketwo db 0
write db 0
writenow db 0
pmode db 0
times 16 db 0
pmodeReadOffset dd 0
pmodeWriteOffset dd 0x100000

;
;	QUESTION:
;		Why aren't things working?
;
;	ANSWER:
;		The file reader/writer DOESN'T LOOK AT THE FINAL SECTOR OF THE FILE
;
;	SOLUTION:
;		Pad all files with at least 512 zeroes.
;

readFileIntoProtectedMode:
	pushad
	mov eax, 0
	mov ax, [fsOutputSeg]
	shl eax, 4
	mov ebx, 0
	mov bx, [fsOutputOff]
	add eax, ebx
	mov [pmodeReadOffset], eax
	popad
	mov [pmodeWriteOffset], dword 0x100000

	mov [write], byte 0
	mov [pmode], byte 1
	jmp short dofile

readFile:
	mov [pmode], byte 0
	mov [write], byte 0
	jmp short dofile
writeFile:
	mov [pmode], byte 0
	mov [write], byte 1
dofile:
	mov [writenow], byte 0

	call getRoot		;puts in EAX
	;EAX = 0x2DE6		@@@

	mov [taketwo], byte 0
	mov bp, 2			;1 after first time, 0 after second time
.retryNext:
	call readSectors	;read root

	;sector number in EAX

	mov di, 0x7E00
.nextentry:
	mov si, fsInputFilepathA
	cmp [taketwo], byte 1
	jne .skip

	mov si, fsInputFilepathB
.skip:
	mov cx, 11
	cld
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
	jmp short .retryNext

.found:
	mov [taketwo], byte 1

	;get root of directory
	xor eax, eax
	mov ax, [es:di + 0x14]					;get high start cluster
	shl eax, 16							;move to high word
	mov ax, [es:di + 0x1A]					;get low start cluster

	mov ebx, eax
	push ebx
	call getRoot
	pop ebx
	add eax, ebx
	sub eax, 2		;strange FAT32 thing 
					;e.g.
					;	(first_sector_of_cluster = ((cluster - 2) * fat_boot->sectors_per_cluster) + first_data_sector;)
	dec bp								;set flag
	jz short rootdone 					;if so, do something else

	
    jmp short .retryNext						;if first time, check for file again

rootdone:
	mov ebx, [es:di + 0x1C]				;get file size
	shr ebx, 9

.readFileLoop:
	; FILE START: EAX
	; FILE SIZE  (IN SECTORS): EBX

	mov dx, [fsOutputOff]
	mov [d_add], dx
	mov dx, [fsOutputSeg]
	mov [db_seg], dx

	mov [writenow], byte 1
	call readSectors
	mov [writenow], byte 0
	mov [db_seg], word 0x0
	mov [d_add], word 0x7E00
	cmp ebx, 0
	jz .done

	push ebx
	call getNext
	pop ebx

	dec ebx
	pushad
	call pmodeAdjust
	popad
	jmp .readFileLoop
.done:
	ret

pmodeAdjust:
	cmp [pmode], byte 0
	je .not

	mov eax, [pmodeReadOffset]
	mov ebx, [pmodeWriteOffset]
	mov ecx, 512
	call dodgeyPModeCopy

	add [pmodeWriteOffset], dword 512

	ret

.not:
	add word [fsOutputOff], 0x200		;move over 0x20 segments or 512 bytes
	ret


readSectors:
	pushad
	mov [d_lba], eax
	cmp [write], byte 1
	je .writeSectors
.justRead:
	mov ah, 0x42
.finishReadWrite:
	mov si, DAPACK
	mov al, 0
	mov dl, byte [driveNumber]			; The drive to read from
	cld
	int 0x13
	jc short err
	popad
	ret

.writeSectors:
	cmp [writenow], byte 0
	je .justRead
	mov ah, 0x43
	xor al, al
	jmp .finishReadWrite

err:
	popad 

	pushf
	push EAX

	mov bx, 0x4			;make it red
	mov ah, 0xB
	int 0x10

	mov si, diskerror
	call puts

	pop eax
	popf
	cli
	hlt
	jmp $

diskerror db "Disk error. The error code is stored in AH. FLAGS has also been saved.", 0
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



; 0xA74 sectors / FAT		(CORRECT)
; 2 FATs					(CORRECT)
; 0x187E reserved sectors	(CORRECT)
; 0x80 hidden sectors		(CORRECT)
; Drive = 0x80				(CORRECT)

getNext:
	;EAX = 0x2DE7

	;input eax
	;output: looks at FAT, finds entry number eax and returns next sector in eax

	;EAX has a sector number (in this case 0x17B67)
	;but we need it as a cluster number

	mov ecx, eax

	push ecx
	call getRoot			;get root
	pop ecx

	;EAX = 0x2DE6		;ROOT
	;ECX = 0x2DE7		;INPUT

	sub ecx, eax			;remove root
	add ecx, 2				;add 2 to reverse the strange '- 2' from earlier

	;ECX = 0x3

	push ecx
	call getFAT			;return FAT address in EBX
	pop ecx

	;EBX = 0x18FE

	mov eax, ecx		;save a copy for the offset
	shr ecx, 7			;SHL 2, SHR 9: 4 byte entries (<< 2) then divide by 512 to give sector offset (>> 9) (hopefully we have 512 byte sectors and 1 cluster per sector)
	add ecx, ebx		;we now have the sector it is in

	;ECX = 0x1959

	mov ebx, eax			;copy input offset
	shl ebx, 2				;4 byte entries
	and ebx, 0b111111111	;get low 9 bytes (offset into sector)

	;ECX = sector
	;EBX = offset

	mov eax, ecx 
	call readSectors
	
	add ebx, 0x7E00
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
	sub eax, 2		;strange FAT32 thing 

	ret


spSave dw 0

%include "PMODEWRAP.INC"

dodgeyPModeCopy:
	;copy ECX bytes at EAX to EBX

	cli
	mov [spSave], sp

	jmp real32BitCopy


returnPMCopy:
	cli
	xor	ax, ax
	mov	ds, ax
	mov	es, ax
	mov	ss, ax
	mov sp, [spSave]
	sti

	ret