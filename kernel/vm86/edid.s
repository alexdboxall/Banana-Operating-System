org 0x900
bits 16

times 128 db 0x90

nop
nop

cli

mov ax, sp;
mov gs, ax;

mov ax, 0x90
mov ds, ax
mov es, ax
mov fs, ax
mov ss, AX
mov sp, stack

mov ax, 0x4F15
mov bl, 0x01
xor cx, cx
xor dx, dx
int 0x10

;ES:DI has EDID
;AX has error data

mov bx, es
mov fs, bx
mov si, di

;FS:SI has EDID

mov bx, 0x90
mov es, bx
xor di, di

;DEST is 0x90:0

mov cx, 128
cld
rep fs movsb 

mov [0x80], ax		;store status code

mov eax, 0
int 0xEE			;soft terminate


times 128 db 0
times 64 db 0
stack: