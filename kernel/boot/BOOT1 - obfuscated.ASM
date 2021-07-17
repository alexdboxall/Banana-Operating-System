
; Banana Bootloader - Obfuscated
; Copyright Alex Boxall 2020 All Rights Reserved

org 0
bits 16

jmp short _main
nop

_bpb:
	filename:					db "BANANA"
	filenamex:					db "  "
	_bpb.bytesPerSector			dw 0x0200
								db 0
	_bpb.reservedSectors		dw 0x187E
	_bpb.totalFATs				db 0x0002
								times 11 db 0
	_bpb.hiddenSectors			dd 0x00000001
								dd 0
	_bpb.logicalSectorsPerFAT	dd 0x3C1
								times 12 db 0
	filename2:					db "FIRMWARELIB "
								db 0x80
	driveNumber					db 0
								times 5 db 0

DAPACK:
		db	0x10
		db	0
blkcnt:	dw	1	
d_add:	dw	0x0500
		dw	0
d_lba:	dd	0
		dd	0

_main:
	cli	
	cld
	mov ax, 0x07C0	
	mov ds, ax
	mov ss, ax
	xor bp, bp	
	mov es, bp
	mov sp, bp
	jmp 0x7C0:setcs	

setcs:
	mov [_bpb.bytesPerSector - 1], dword 0x20202020		
	mov [driveNumber], dl
	push es					
	push dx		
	xor ax, ax	
	int 0x10
fileLoad:
	call getRoot
.retryNext:
	call readSectors
	mov di, 0x0500
.nextentry:
	mov si, filename
	add si, bp
	mov cx, 11
	push di
	repe cmpsb 
	pop di
	je .found
	add di, 32
	cmp di, 0x8000
	jne short .nextentry
.nextsector:
	call getNext
	jmp short .retryNext
.found:
	mov [filenamex], word 0x5442
	cmp [file2], byte 1
	jne short .sk
	mov bp, (filename2-filename)
.sk:
	xor eax, eax
	mov ax, [es:di + 0x14]	
	shl eax, 16	
	mov ax, [es:di + 0x1A]
	push eax
	call getRoot
	pop ebx
	add eax, ebx
	dec eax	
	dec eax	
	dec sp	
	jnp short .retryNext 
	pop bx
rootdone:
	mov ebx, [es:di + 0x1C]	
	shr ebx, 9
.readFileLoop:
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
	add byte [addstore + 1], 0x2
	jmp short .readFileLoop

fileReadDone:
	mov bx, 0xC000
	mov [addstore], bx
	mov [filenamex], word 0x2020
	inc byte [file2]
	cmp byte [file2], 2
	jne fileLoad
	pop dx
	push bx
	retf

readSectors:
	pushad
	mov [d_lba], eax
	mov ah, 0x42
	mov si, DAPACK
	mov dl, byte [driveNumber]
	int 0x13
	jc short err
	popad
	ret

err:
	mov bx, 0x4
	mov ah, 0xB
	int 0x10
	jmp short $

getRoot:
	mov eax, [_bpb.logicalSectorsPerFAT]
	mov cl, [_bpb.totalFATs]
	dec cl
	shl eax, cl	
	movzx ebx, word [_bpb.reservedSectors]
	add ebx, [_bpb.hiddenSectors]
	add eax, ebx
	ret

getNext:
	mov edx, eax
	call getRoot
	sub edx, eax
	inc edx	
	inc edx
	mov eax, edx
	shr edx, 7	
	add edx, ebx
	mov bx, ax	
	shl bx, 1
	xor bh, bh	
	shl bx, 1
	mov eax, edx
	call readSectors
	add bh, 5		
	push dword [es:bx]
	call getRoot
	pop ebx	
	and ebx, 0x0FFFFFFF						
	add eax, ebx
	dec eax	
	dec eax	

	ret

addstore dw 0x7E00
file2 db 0

times 510 - ($-$$) db 1
dw 0xAA55