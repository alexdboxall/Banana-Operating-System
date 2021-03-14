org 0x900
bits 16

cli

mov ax, sp
mov gs, ax

mov ax, 0x90
mov ds, ax
mov es, ax
mov fs, ax

mov bx, gs

mov ax, 0x0C00
mov ss, ax
mov sp, 0x0

mov ax, bx
int 0x10

mov eax, 0
int 0xFF			;soft terminate

hlt					;hard terminate
jmp $				;the backup
