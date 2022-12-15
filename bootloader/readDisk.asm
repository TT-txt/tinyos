;load dh number of sectors from drive dl into es:bx
;reference: https://stanislavs.org/helppc/int_13-2.html
diskLoad:
    pusha
    push dx
    mov ah, 0x02 ;0x02 = read
    mov al, dh ;number of sectors
    mov cl, 0x02 ;sector, starting at the first available
    mov ch, 0x00 ;the cylinder number
    mov dh, 0x00 ;head number
    int 13h ;reading data, stored by default inside 
    jc diskError
    pop dx
    cmp al, dh ;int 13h sets al to the # read
    jne sectorError
    popa
    ret
sectorError:
    mov bx, sectorErrorMsg
    call printStr
    jmp loop
diskError:
    mov bx, diskErrorMsg
    call printStr
    mov dh, ah ;ah contains the error code
    call printHex
    jmp loop

loop:
    jmp $

sectorErrorMsg:
    db "number of sectors not matching", 0
diskErrorMsg:
    db "Disk read error... (int13h is trash), the error code is:", 0