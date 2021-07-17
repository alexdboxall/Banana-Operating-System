align 256			;just to be safe, I don't think it needs any alignment, but you never know
MODEINFO:
ModeAttrib dw 0
WinAAttrib db 0
WinBAttrib db 0
WinGrand   dw 0
WinSize    dw 0
WinASeg    dw 0
WinBSeg    dw 0
WinFuncPtr dd 0
ByteScan   dw 0
XRes       dw 0
YRes       dw 0
XCharSize  db 0
YCharSize  db 0
PlaneNo    db 0
Bpp        db 0
NoBanks    db 0
MemModel   db 0
BankSize   db 0
NoImgPage  db 0
ResPage    db 0
RedMaskS   db 0
RedMaskP   db 0
GreenMaskS db 0
GreenMaskP db 0
BlueMaskS  db 0
BlueMaskP  db 0
ResMaskS   db 0
ResMaskP   db 0
DirColMode db 0
PhysBasPtr dd 0
OffScrMO   dd 0
OffScrMS   dw 0
times 206 db 0

times 10 dd 0 ;just to be safe

findBestMode:
	mov ax, 0x0118
	jmp getModeInfo

videoMode:
	xor ax, ax
	mov fs, ax
	mov ax, [fs:0x7001]
	cmp ax, 0
	je findBestMode
getModeInfo:
	mov cx, ax			;the video mode
	or cx, 0x4000		;framebuffer mode

	push cx
	mov ax, 0x4F01
	mov bx, ds
	mov es, bx
	mov di, MODEINFO
	int 0x10

	cmp ah, 0
	jne .error

	mov dx, 0
	mov ax, [ByteScan]			;replace the X res value with the scanline length value (includes bytes between lines)
	movzx cx, [Bpp]				;bits per pixel
	shr cx, 3					;convert to bytes per pixel
	div cx
	mov [fs:0x500], ax

	mov ax, [YRes]
	mov [fs:0x502], ax

	mov [fs:0x505], byte 0			;not safe mode

	mov eax, [PhysBasPtr]
	mov [fs:0x506], eax

	mov al, [Bpp]
	mov [fs:0x50C], al

	mov [fs:0x50D], byte 0

	mov ax, [XRes]
	mov [fs:0x50E], ax

	mov [fs:0x510], byte 1
	mov [fs:0x511], byte 0
	mov [fs:0x512], byte 0

	pop bx				;get video mode back, into BX this time
	mov ax, 0x4F02
	int 0x10			;set video mode
	ret

.error:
	mov si, modefinderr
	call puts
	jmp $

modefinderr db "Error getting video mode information."