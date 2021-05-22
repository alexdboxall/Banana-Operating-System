org 0x900
bits 16

cli

mov ax, sp;
mov gs, ax;

mov ax, 0x90
mov ds, ax
mov es, ax
mov fs, ax
mov ss, ax

mov sp, stack

mov bx, gs

mov ax, 0x0C00
mov ss, ax
mov sp, 0x0

mov ax, 0x3
int 0x10

xor eax, eax
int 0xEE			;terminate (0xFF used by APIC spurious)

times 128 db 0
stack:
