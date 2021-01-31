
DISK_IMAGE_SECTOR equ 33
ZEROS_SECTOR equ 2633
FIRMWARE_SECTOR equ 2665
APPLICATION_SECTOR equ 2670

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
														;SET THE LOW BYTE OF BYTES PER SECTOR TO 0x20
														;AND SET SECTORS PER CLUSTER TO 0x20

	;THIS IS THE REAL DEAL, BECAUSE ITS A FLOPPY AND 
	;THERE IS ONLY ONE LAYOUT (IT DOES NOT CHANGE DEPENDING ON PARTITION SIZE!)

	_bpb.bytesPerSector				dw 0x0200			; OFFSET 0xB   Bytes per Sector (512)
	_bpb.sectorsPerCluster			db 0x01				; Sectors per cluster (usually 1)
	_bpb.reservedSectors			dw 1				; Reserved sectors
	_bpb.totalFATs					db 0x0002			; FAT copies
	_bpb.rootEntries				dw 0xE0				; Root directory entries
	_bpb.fat12.totalSectors			dw 0xB40				; Sectors in filesystem (0 for FAT16)
	_bpb.mediaDescriptor			db 0xf0				;f0 for floppy or f8 for HDD
	_bpb.sectorsPerFAT				dw 9				; OFFSET 0x16	0x0009			; Sectors per FAT

	_bpb.sectorsPerTrack			dw 0x12				; OFFSET 0x18   Sectors per track
	_bpb.headsPerCylinder			dw 0x02				; OFFSET 0x1A   Heads per cylinder
	
	;OFFSET 0x1C  
	dd 0			;hidden sectors
	dd 0

	;OFFSET 0x24
	dd 9				;sectors per FAT, needed for rest of boot code which expects FAT32


	driveNumber db 0									; WERE NOT USING THE VALUE HERE, ONLY THE MEMORY ADDRESS


_main:
	cli										;no interrupts
	cld
	mov ax, 0x07C0							; were at 07C0:0000, so set our segment registers to that
	mov ds, ax
	mov ss, ax

	xor bp, bp								;needed for stuff later on...
	mov es, bp
	mov sp, bp

	jmp 0x7C0:setcs							;set CS so we know were at 07C0:0000 instead of, e.g. 0000:7C00 or even 049B:3250

setcs:
	mov [driveNumber], dl

	mov ax, 3
	int 0x10

	mov si, .bootmsg
	call bios_print

	jmp .doneprint
	.bootmsg db 0xA, 0xD, "  Please wait...", 0

.doneprint:
	call resetDisk

	;FIRMWARE.LIB TO BE LOADED AT 0xC000 (4KB loaded)
	;FLOPPY.EXE TO BE LOADED AT 0x80000 (32KB loaded)
	;ZEROS.SYS TO BE LOADED AT 0x8000 (16KB LOADED)


	
	xor eax, eax
	mov ax, ZEROS_SECTOR
	mov di, 0x800
	mov cx, 32
.zerosRead:
	call readSector
	add di, 0x20
	inc ax
	loop .zerosRead



	xor eax, eax
	mov ax, APPLICATION_SECTOR
	mov di, 0x5000
	mov cx, 64
.appRead:
	call readSector
	add di, 0x20
	inc ax
	loop .appRead



	xor eax, eax
	mov ax, FIRMWARE_SECTOR
	mov di, 0xC00
	mov cx, 8

.firmwareRead:
	call readSector
	add di, 0x20
	inc ax
	loop .firmwareRead


	mov dl, [driveNumber]
	push word 0x0000
	push word 0xC000

	retf
	jmp $


;AX = LBA
;DI = SEGMENT (OFFSET = 0)

readSector:
	push es
	pushad

	call LBACHS

	mov si, 5

.retry:
	mov es, di
	xor bx, bx
	mov ah, 2
	mov al, 1
	mov ch, [absoluteTrack]
	mov cl, [absoluteSector]
	mov dh, [absoluteHead]
	mov dl, [driveNumber]
	pushad
	int 0x13
	popad

	jc .err

	popad
	pop es
	ret

.err:
	dec si
	jz fatal
	call resetDisk
	jmp .retry


fatal:
	mov eax, 0xDEADDEAD
	mov ebx, eax
	cli
	hlt
	jmp short fatal

resetDisk:
	pushad
	mov ah, 0
	mov dl, [driveNumber]
	int 0x13
	popad
	ret


LBACHS:
    xor     dx, dx                              ; prepare dx:ax for operation
    div     WORD [_bpb.sectorsPerTrack]           ; divide by sectors per track
    inc     dl                                  ; add 1 (absolute sector formula)
    mov     BYTE [absoluteSector], dl
  
    xor     dx, dx                              ; prepare dx:ax for operation
    div     WORD [_bpb.headsPerCylinder]          ; mod by number of heads (absolute head formula)
    mov     BYTE [absoluteHead], dl             ; everything else was already done from the first formula
 
    mov     BYTE [absoluteTrack], al            ; not much else to do :)
    ret
	
bios_print:
   lodsb
   or al, al  ;zero=end of str
   jz done    ;get out
   mov ah, 0x0E
   mov bh, 0
   int 0x10
   jmp bios_print
done:
   ret

absoluteSector db 0
absoluteHead db 0
absoluteTrack db 0

times 510 - ($-$$) db 1						;Banana thinks it is a partition table if these are 0x00, because we have a 64 byte section blank section at the end of the bootloader
											;this wouldnt be a problem usually, but because this bootsector so optimised, it leaves this massive gap at the end.
dw 0xAA55