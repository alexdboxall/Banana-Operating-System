bits 32

global sseDetect
global sseSave
global sseLoad
global sseInit
global sseClose

extern x87Init
global probablyNot
probablyNot:
sseDetect:          ;RETURNS A SIZE_T, 0 OR 1
    mov eax, 0x1
    cpuid
    test edx, 1<<25
    jz .noSSE
    mov eax, 1
    ret
.noSSE:
    mov eax, 0
    ret

sseSave:            ;TAKES IN A SIZE_T
;WARNING: NOTICE WE ARE NOT USING A STACK FRAME FOR THIS, DO NOT CHANGE EBP WITHOUT PUSHING IT FIRST!
    fxsave [esp + 8]
    ret

sseLoad:            ;TAKES IN A SIZE_T
;WARNING: NOTICE WE ARE NOT USING A STACK FRAME FOR THIS, DO NOT CHANGE EBP WITHOUT PUSHING IT FIRST!
    fxrstor [esp + 8]
    ret

sseInit:
    call x87Init

    mov eax, cr4
    or ax, 3 << 9        ;set CR4.OSFXSR and CR4.OSXMMEXCPT at the same time
    mov cr4, eax

    ret

sseClose:
    ret
