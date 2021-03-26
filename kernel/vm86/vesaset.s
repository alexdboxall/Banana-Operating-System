org 0x900
bits 16

cli

mov ax, sp
mov gs, ax

mov ax, 0x90
mov ds, ax
mov es, ax
mov fs, ax

;GS has mode number

mov ax, 0x4F02
mov bx, gs
or bx, 0x4000				;want LFB
mov di, crtcInfoBlock
int 0x10

;send back the data we got through the virtual communications port
mov dx, 0xFEFE

;uint16_t width;
;uint16_t height;
;uint16_t pitch;
;uint8_t bpp;
;uint8_t reserved;
;uint32_t lfb;

mov ax, [width]
out dx, al
xchg al, ah
out dx, al

mov ax, [height]
out dx, al
xchg al, ah
out dx, al

mov ax, [pitch]
out dx, al
xchg al, ah
out dx, al

mov al, [bpp]
out dx, al
xor al, al
out dx, al

mov al, [framebuffer]
out dx, al
mov al, [framebuffer + 1]
out dx, al
mov al, [framebuffer + 2]
out dx, al
mov al, [framebuffer + 3]
out dx, al

xor eax, eax
int 0xEE			;terminate (0xFF used by APIC spurious)

crtcInfoBlock:
attributes dw 0x0
windowA db 0
windowB db 0
gran dw 0
winsize dw 0x0
segA dw 0
segB dw 0
winFuncPtr dd 0
pitch dw 0
width dw 0
height dw 0
wchar db 0
ychar db 0
planes db 0
bpp db 0
banks db 0
memmodel db 0
banksize db 0
imagePages db 0
reserved0 db 0
_red dw 0
_green dw 0
_blue dw 0
_reserved dw 0
directColAttrib db 0x0
framebuffer dd 0
offscreenMemOff dd 0
offscreenMemSize dw 0
times 206 db 0