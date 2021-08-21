bits 32

global avxDetect
global avxSave
global avxLoad
global avxInit
global avxClose

extern sseInit

avxDetect:          ;RETURNS A SIZE_T, 0 OR 1
    mov eax, 0x1
    cpuid
    test ecx, 1<<28        ;AVX
    jz .noAVX

    mov eax, 0x1
    cpuid
    test ecx, 1<<26        ;XSAVE
    jz .noAVX

    mov eax, 1
    ret
.noAVX:
    mov eax, 0
    ret

avxSave:            ;TAKES IN A SIZE_T
    push ebx
    push edx
    xor eax, eax
    dec eax
    mov edx, eax

    mov ebx, [esp + 4 + 8]
    xsave [ebx]

    pop edx
    pop ebx
    ret

avxLoad:            ;TAKES IN A SIZE_T
    push ebx
    push edx
    xor eax, eax
    dec eax
    mov edx, eax

    mov ebx, [esp + 4 + 8]
    xrstor [ebx]

    pop edx
    pop ebx
    ret

avxInit:
    call sseInit

    push eax
    push ecx

    mov eax, cr4
    or eax, (1 << 18)
    mov cr4, eax

    xor ecx, ecx
    xgetbv            ;Load XCR0 register
    or eax, 7         ;Set AVX, SSE, X87 bits
    xsetbv            ;Save back to XCR0

    pop ecx
    pop eax

    ret

avxClose:
    ret
