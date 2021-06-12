bits 32

global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr96
global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15
global irq16
global irq17
global irq18
global irq19
global irq20
global irq21
global irq22
global irq23

isr0:
    cli
    push 0
    push 0
    jmp int_common_stub

isr1:
    cli
    push byte 0
    push byte 1
    jmp int_common_stub

isr2:
    cli
    push byte 0
    push byte 2
    jmp int_common_stub

isr3:
    cli
    push byte 0
    push byte 3
    jmp int_common_stub

isr4:
    cli
    push byte 0
    push byte 4
    jmp int_common_stub

isr5:
    cli
    push byte 0
    push byte 5
    jmp int_common_stub

isr6:
	cli
    push byte 0
    push byte 6
    jmp int_common_stub

isr7:
    cli
    push byte 0
    push byte 7
    jmp int_common_stub

isr8:
    cli
    push byte 8
    jmp int_common_stub

isr9:
    cli
    push byte 0
    push byte 9
    jmp int_common_stub

isr10:
	cli
    push byte 10
    jmp int_common_stub

isr11:
    cli
    push byte 11
    jmp int_common_stub

isr12:
    cli
    push byte 12
    jmp int_common_stub

isr13:
    cli
    push byte 13
    jmp int_common_stub

isr14:
    cli
    push byte 14
    jmp int_common_stub

isr15:
    cli
    push byte 0
    push byte 15
    jmp int_common_stub

isr16:
    cli
    push byte 0
    push byte 16
    jmp int_common_stub

isr17:
    cli
    push byte 0
    push byte 17
    jmp int_common_stub

isr18:
    cli
    push byte 0
    push byte 18
    jmp int_common_stub

irq3:
    cli
    push byte 0
    push byte 35
    jmp int_common_stub

irq4:
    cli
    push byte 0
    push byte 36
    jmp int_common_stub

irq5:
    cli
    push byte 0
    push byte 37
    jmp int_common_stub

irq6:
    cli
    push byte 0
    push byte 38
    jmp int_common_stub

irq7:
    cli
    push byte 0
    push byte 39
    jmp int_common_stub

irq8:
    cli
    push byte 0
    push byte 40
    jmp int_common_stub

irq9:
    cli
    push byte 0
    push byte 41
    jmp int_common_stub

irq10:
    cli
    push byte 0
    push byte 42
    jmp int_common_stub

irq11:
    cli
    push byte 0
    push byte 43
    jmp int_common_stub

irq12:
    cli
    push byte 0
    push byte 44
    jmp int_common_stub

irq13:
    cli
    push byte 0
    push byte 45
    jmp int_common_stub

irq14:
    cli
    push byte 0
    push byte 46
    jmp int_common_stub

irq15:
    cli
    push byte 0
    push byte 47
    jmp int_common_stub

irq1:
    cli
    push byte 0
    push byte 33
    jmp short int_common_stub

irq2:
    cli
    push byte 0
    push byte 34
    jmp short int_common_stub

isr96:
    push byte 0
    push byte 96
    sti
    jmp short syscall_common_stub

global int_common_stub
global syscall_common_stub
extern int_handler

irq0:
    cli
    push byte 0
    push byte 32

int_common_stub:
    pushad

    push ds
    push es
    push fs
    push gs

    mov ax, 0x10   ; Load the Kernel Data Segment descriptor!
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push esp
    cld             ; the kernel will "have a fit" if userspace has the direction flag set when we interrupt
    call int_handler
    add esp, 4

	pop gs
    pop fs
    pop es
    pop ds

	popa
    add esp, 8     ; Cleans up the pushed error code and pushed ISR number

    iret


extern KiCheckSignalZ
syscall_common_stub:
    pushad

    push ds
    push es
    push fs
    push gs

    mov ax, 0x10   ; Load the Kernel Data Segment descriptor!
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push esp
    cld             ; the kernel will "have a fit" if userspace has the direction flag set when we interrupt
    call int_handler
    add esp, 4

	pop gs
    pop fs
    pop es
    pop ds

    call KiCheckSignalZ
    cmp eax, 0
	je .skipSignals

    mov [esp + 8 * 4], 0xDEADBEEF
    popa
    jmp $
    
    ;unsigned int gs, fs, es, ds;
	;unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
	;unsigned int int_no, err_code;
	;unsigned int eip, cs, eflags, useresp, ss;
	;unsigned int v86es, v86ds, v86fs, v86gs;

.skipSignals:

	popa
    add esp, 8     ; Cleans up the pushed error code and pushed ISR number

    iret






irq16:
    cli
    push byte 0
    push byte 48
    jmp int_common_stub

irq17:
    cli
    push byte 0
    push byte 49
    jmp int_common_stub

irq18:
    cli
    push byte 0
    push byte 50
    jmp int_common_stub

irq19:
    cli
    push byte 0
    push byte 51
    jmp int_common_stub

irq20:
    cli
    push byte 0
    push byte 52
    jmp int_common_stub

irq21:
    cli
    push byte 0
    push byte 53
    jmp int_common_stub

irq22:
    cli
    push byte 0
    push byte 54
    jmp int_common_stub

irq23:
    cli
    push byte 0
    push byte 55
    jmp int_common_stub