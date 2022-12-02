BITS 16 ;setting up 16bits mode, requiered by the legacy mode
GLOBAL _start ;entrypoint of the program 

_start: ;elf entry point
    jmp main ;going to the main func

;begin of the print func,
;param: ds:si pointing to the string
puts:
    push si ;pushing the message to print to the stack
    push ax ;adding the ax to save it 
    push bx ;same for bx, we're editing it later so we save it here

.loop:
    lodsb ;loads DS:SI into AL, and increments SI by the number of bytes loaded
    or al, al ;modify the flex register, if the result is 0 then we're done as no more bytes are loaded
    jz .done ;exiting
    mov ah, 0x0E ;setting up the bios interrupt to AH, writing char in tty mode
    mov bh, 0 ;bh contains the page number, here 0
    int 0x10 ;calling interrupt 0x10
    jmp .loop ;zoof looping

.done:
    pop bx ;putting back the saved register into the stack
    pop ax ;same
    pop si ;same
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
    mov sp, 0x7C00 ;pushing 0x7C00 to the stack, pointing the start of our prog
    mov si, msg_hello ;preparing the call to print, pushing our message to the SI, general purpose reg
    call puts ;calling the print function
    hlt ;stoping

;---INFINITE LOOP
.halt:
    jmp .halt


msg_hello: db "IT IS ASSEMBLY TIME - JUNIOS BOOTING", 0x0D, 0x0A, 0 ;0x0D, 0x0A is ENDL

times 510-($-$$) db 0
dw 0AA55h
