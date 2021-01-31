bits 64

global x87Detect
global x87Save
global x87Load
global x87Init
global x87Close

value_37F dw 0x37F
value_37E dw 0x37E
value_37A dw 0x37A

x87Detect:          ;RETURNS A SIZE_T, 0 OR 1
    mov rax, 0x1
    cpuid
    test rdx, 1<<0
    jz .nox87
    mov rax, 1
    ret
.nox87:
    mov rax, 0
    ret

x87Save:            ;TAKES IN A SIZE_T
    fsave [rdi]
    ret

x87Load:            ;TAKES IN A SIZE_T
    frstor [rdi]
    ret

x87Init:
    finit
    mov rax, cr0
    and ax, 0xFFFB        ;clear coprocessor emulation CR0.EM
    or ax, 0x22           ;set coprocessor monitoring  CR0.MP + numeric errors (CRO.NE)
    mov cr0, rax

    clts                  ;clear task switched bit

    ;allow interrupts for div by zero and invalid operands
    fldcw [value_37A]     ; writes 0x37a, both division by zero and invalid operands cause exceptions.

    ret

x87Close:
    ret
