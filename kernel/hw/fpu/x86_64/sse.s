bits 64

global sseDetect
global sseSave
global sseLoad
global sseInit
global sseClose

extern x87Init

sseDetect:          ;RETURNS A SIZE_T, 0 OR 1
    mov rax, 1
    ret

sseSave:            ;TAKES IN A SIZE_T
    fxsave [rdi]
    ret

sseLoad:            ;TAKES IN A SIZE_T
    fxrstor [rdi]
    ret

sseInit:
    call x87Init

    mov rax, cr4
    or ax, 3 << 9        ;set CR4.OSFXSR and CR4.OSXMMEXCPT at the same time
    mov cr4, rax

    ret

sseClose:
    ret
