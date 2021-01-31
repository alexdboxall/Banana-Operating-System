bits 64

global avxDetect
global avxSave
global avxLoad
global avxInit
global avxClose

extern sseInit

avxDetect:          ;RETURNS A SIZE_T, 0 OR 1
    mov rax, 0x1
    cpuid
    test rcx, 1<<28        ;AVX
    jz .noAVX

    mov rax, 0x1
    cpuid
    test rcx, 1<<26        ;XSAVE
    jz .noAVX

    mov rax, 1
    ret
.noAVX:
    mov rax, 0
    ret

avxSave:            ;TAKES IN A SIZE_T
    xsave [rdi]
    ret

avxLoad:            ;TAKES IN A SIZE_T
    xrstor [rdi]
    ret

avxInit:
    call sseInit

    push rax
    push rcx

    xor ecx, ecx
    xgetbv            ;Load XCR0 register
    or eax, 7         ;Set AVX, SSE, X87 bits
    xsetbv            ;Save back to XCR0

    pop rcx
    pop rax

    ret

avxClose:
    ret
