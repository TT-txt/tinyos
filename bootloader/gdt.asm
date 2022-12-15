gdtStart:
    dd 0x0
    dd 0x0 ;0x00 to ensure no error lmao
gdtCode:
    dw 0xFFFF ;segment lenght bits 0-15
    dw 0x0 ;segment base, bits 0-15
    db 0x0 ;segment base, bits 16-23
    db 10011010b ;flags
    db 11001111b ;flags & segment lenght, 16-19
    db 0x0 ;seg base
gdtData:
    dw 0xFFFF ;same as above
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0
gdtEnd:

gdtDescriptor:
    dw gdtEnd - gdtStart - 1 ;size is always 1 less of true size
    dd gdtStart ;32bit address

CODE_SEGMENT equ gdtCode - gdtStart
DATA_SEGMENT equ gdtData - gdtStart