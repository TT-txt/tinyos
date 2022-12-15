[org 0x7C00]
KERNEL_OFFSET equ 0x1000
;saving up the drive number
mov [BOOT_DRIVE], dl ;dl stores the boot drive number
;setting up the stack
mov bp, 0x9000 ;putting the base of the stack far away
mov sp, bp ;stack pointer to the bottom of the stack
;welcome msg
mov bx, bootingMessage;putting the begin adress of the message in bx
call printStr
;loading kernel in memory
call loadKernel
;going in protected mode
mov bx, protectedModeMessage
call printStr
call goingProtected

jmp $ ;infinite loop, shouldn't execute
;includes
%include "bootloader/print.asm"
%include "bootloader/readDisk.asm"
%include "bootloader/gdt.asm"
%include "bootloader/goingProtected.asm"

[BITS 16]
loadKernel:
    mov bx, KERNEL_OFFSET
    ;AHAHAHAHAHAHA I'M SO DUMB
    mov dh, 54;the number of sectors to read, 54 is max val
    mov dl, [BOOT_DRIVE]
    call diskLoad
    ret

[BITS 32]
MAIN_PROTECTED:
    mov ebx, intoProtectedMessage
    call printStr32 ;printing fancy msg
    call KERNEL_OFFSET ;giving control to the kernel
    jmp $

;data
BOOT_DRIVE db 0 ;used to store drive number, useful later
;strings
bootingMessage db "Booting JUNIOS, please wait...", 0
protectedModeMessage db "switching to protected (32bits) mode...", 0
intoProtectedMessage db "Successfully entered 32 bits mode.", 0
times 510-($-$$) db 0 ;filling
dw 0xAA55 ;bootable
;--END OF SECTOR 1--