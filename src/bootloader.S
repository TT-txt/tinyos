BITS 16
global _start

section .text
_start: ;elf entry point
    jmp main ;going to the main func

;print function, param: ds:si pointing to the string
print:
    pusha ;pushing all purpose reg to the stack
.loop:
    lodsb ;loads DS:SI into AL, and increments SI by the number of bytes loaded
    cmp al, 0 ;if al is not 0 (string end char), we skip
    je .done ;exiting
    mov ah, 0x0E ;setting up the bios interrupt to AH, writing char in tty mode
    mov bh, 0 ;bh contains the page number, here 0
    int 0x10 ;calling interrupt 0x10
    jmp .loop ;zoof looping
.done:
    popa ;restoring general purpose reg
    ret ;returning to the main code
;end of the printing func

;---MAIN---
main:
    ;setting up the register
    mov ax, 0 ;putting 0 into AX
    mov ds, ax ;setting ds as 0, containing the memory segment of the data
    mov es, ax ;setting es as 0, containing the memory segment of extra data
    ;setting up the stack
    mov ss, ax ;setting the stack segment as 0
    mov sp, 0x7C00 ;stack pointer set to the begining of the prog
    mov si, msg_hello ;preparing the call to print, pushing our message to the SI, general purpose reg
    call print ;calling the print function
    hlt ;stoping
    jmp $ ;infinite loop, for safety

msg_hello: db "IT IS ASSEMBLY TIME - JUNIOS BOOTING", 0x0D, 0x0A, 0 ;0x0D, 0x0A is ENDL

times 510-($-$$) db 0 ;filling the rest of the sector with blanks
dw 0AA55h ;setting the disk as bootable
