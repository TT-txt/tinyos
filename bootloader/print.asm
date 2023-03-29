[BITS 16]
;function printing and ENDL
printENDL:
    mov al, 0x0A
    int 10h
    mov al, 0x0D
    int 10h
    ret

;Function printing message contained in bx on screen and adds a newline
printStr:
    pusha ;saving all purposes register
strStart:
    mov al, [bx]
    cmp al, 0 ;is it the end string ?
    je done
    mov ah, 0x0E;setting tty mode
    int 10h ;printing content of al
    inc bx
    jmp strStart

done:
    call printENDL
    popa
    ret

;Print the hex value of dx and adds a newLine
printHex:
    pusha
    mov cx, 0 ;will be used as the index
hexLoop:
    cmp cx, 4
    je hexEnd
    mov ax, dx ;ax will be the working register
    and ax, 0x000F ;only keeping the last one
    add al, 0x30 ;converting 0 to ASCII '0'
    cmp al, 0x39 ;if > 9, we need to add stuff 
    jle hexStep2 ;jmp lower equal
    add al, 7 ;setting values over 10 by adding the ascii padding requiered
hexStep2:
    ;bx = base address + string lenght - char index
    mov bx, HEX_OUT + 5
    sub bx, cx
    mov [bx], al ;copying the ascii char in al to the position pointed by bx
    ror dx, 4 ;0x1234 -> 0x4123 -> 0x3412 -> 0x2341 -> 0x1234
    inc cx
    jmp hexLoop
hexEnd:
    mov bx, HEX_OUT
    call printStr
    popa
    ret

;data
HEX_OUT: ;reserving memory for our string
    db "0x0000", 0

[BITS 32]
;usesful constants
videoMemory equ 0xb8000 ;begining of the vga memory
white equ 0x0f

;prints the content of ebx
printStr32:
    pusha
    mov edx, videoMemory
printStr32Loop:
    mov al, [ebx] ;with ebx the address of the char
    mov ah, white
    cmp al, 0 ;is it the end ?
    je printStr32Done
    mov [edx], ax ;stores the char and attribute video memory
    add ebx, 1 ;next char
    add edx, 2 ;next video position
    jmp printStr32Loop
printStr32Done:
    popa
    ret