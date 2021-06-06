bits 32

_START_OF_KERNEL:

jmp start
extern KeEntryPoint

start:
    cli

    mov	ax, 0x10		;set data segments to data selector (0x10)
    mov	ds, ax
    mov	ss, ax
    mov	es, ax
    mov	esp, 0xC2010000

    ;set the flags to a known state
    push byte 2
    popf

	call KeEntryPoint