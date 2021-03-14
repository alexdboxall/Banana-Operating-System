bits 32

global avxDetect
global avxSave
global avxLoad
global avxInit
global avxClose

avxDetect:          ;RETURNS A SIZE_T, 0 OR 1
    mov eax, 0      ;AVX was introducted in 2011, I doubt there would be too many 32 bit machines with AVW
    ret

avxSave:            ;TAKES IN A SIZE_T
    ret

avxLoad:            ;TAKES IN A SIZE_T
    ret

avxInit:
    ret

avxClose:
    ret

nothingToSeeHere:
    dec ecx
    and [edi+ebp*2+0x76],ch
    and gs:[ecx+0x6f],bh
    jne 0x2b
    dec esi
    jns 0x6f
    push 0x2e2e2e 