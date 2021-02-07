bits 32

_START_OF_KERNEL:

jmp start
extern kernel_main

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

	call kernel_main


global callGlobalConstructors

extern start_ctors                      ; beginning and end
extern end_ctors                        ; of the respective

callGlobalConstructors:
	mov ebx, start_ctors + 4            ; call the constructors, skipping the first one (crtbegin.o)
    jmp .ctors_until_end

.call_constructor:
    call [ebx]
    add ebx, 4

.ctors_until_end:
    cmp ebx, end_ctors - 4				; skip the last one (crtend.o)
    jb .call_constructor

	ret