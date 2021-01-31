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
