[BITS 32]
[extern main]
section .text
global _start
_start:
    call main ;magic linker is finding it in memory
    jmp $