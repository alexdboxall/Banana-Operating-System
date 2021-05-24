global i386GetRDRAND

i386GetRDRAND:
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