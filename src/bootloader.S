BITS 16
GLOBAL start

start:
    hlt

.halt:
    jmp .halt

times 510-($-$$) db 0
dw 0AA55h
