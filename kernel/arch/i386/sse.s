bits 32

global sseDetect
global sseSave
global sseLoad
global sseInit
global sseClose

extern x87Init

sseDetect:          ;RETURNS A SIZE_T, 0 OR 1
    mov eax, 0x1
    cpuid
    test edx, 1<<25
    jz .noSSE
    mov eax, 1
    ret
.noSSE:
    xor eax, eax
    ret

sseSave:
    mov eax, [esp + 4]
    fxsave [eax]        ;no ebp so plus 4
    ret

sseLoad:            
    mov eax, [esp + 4]
    fxrstor [eax]        ;no ebp so plus 4
    ret

sseInit:
    call x87Init

    mov eax, cr4
    or ax, 3 << 9        ;set CR4.OSFXSR and CR4.OSXMMEXCPT at the same time
    mov cr4, eax

    ret

sseClose:
    ret
