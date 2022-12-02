BITS 16
GLOBAL _start

_start:
    hlt

.halt:
    jmp .halt

times 510-($-$$) db 0
dw 0AA55h
