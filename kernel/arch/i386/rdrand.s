global _i386_getRDRAND

_i386_getRDRAND:
    mov ecx, 100
retry:
    rdrand eax
    jc .done
    loop retry
.fail:
    xor eax, eax
    ret
.done:
    ret