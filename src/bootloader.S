BITS 16
global _start

section .text
;Setting up fat12
jmp short _start
nop
bpb_oem: db "MSWIN4.1" ;we could set everything, but for max compatibility
bpb_bps: dw 512 ;bytes per sector, default value for floppies
bpb_spc: db 1 ;sector per cluster
bpb_rs: db 1;number of reserved sector
bpb_fc: db 2 ;number of allocation table on sector
bpb_rde: dw 0E0h ;root directory entry
bpb_total_sector: dw 2880 ; 2880 * 512 = 1.44MB
bpb_descriptor:  db 0F0h ; F0 = 3.5" floppy disk
bpb_sectors: dw 9                    ; 9 sectors/fat
bpb_spt: dw 18 ;sectors per tracks
bpb_heads: dw 2;
bpb_hidden_sectors: dd 0
bpb_large_sector_count: dd 0
; extended boot record
ebr_drive_number: db 0; 0x00 floppy, 0x80 hdd, useless
db 0 ; reserved
ebr_signature: db 29h
ebr_volume_id: db 12h, 34h, 56h, 78h   ; serial number, value doesn't matter
ebr_volume_label: db "---JUNIOS----"        ; 11 bytes, padded with spaces
ebr_system_id: db "FAT12   "           ; 8 bytes

_start:
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

;Error handlers
floppyError:
    mov si, msg_disk_error
    call print
    jmp reboot

reboot:
    mov ah, 0
    int 16h ;waiting keypress
    jmp 0FFFFh:0 ;should reboot the device ?

;---MAIN---
main:
    ;setting up the register
    mov ax, 0 ;putting 0 into AX
    mov ds, ax ;setting ds as 0, containing the memory segment of the data
    mov es, ax ;setting es as 0, containing the memory segment of extra data
    ;setting up the stack
    mov ss, ax ;setting the stack segment as 0
    mov sp, 0x7C00 ;stack pointer set to the begining of the prog
    ;trying to read shit
    mov [ebr_drive_number], dl
    mov ax, 1
    mov cl, 1
    mov bx, 0x7E00
    call diskRead
    mov si, msg_hello ;preparing the call to print, pushing our message to the SI, general purpose reg
    call print ;calling the print function
    hlt ;stoping
    jmp $ ;infinite loop, for safety, as interrupts can still pause the program

;LBA TO CHS Conversion
;Sector = (LBA % sectors per tracks) + 1
;head = (LBA / sectors per tracks) % heads
;cylinder = (LBA / sectors per track) / heads
;param: ax, the LBA address
;return:
;cx: sector number, cylinder
;dh: head number
lbaToCHS:
    push ax
    push dx
    mov dx, 0
    div word [bpb_spt] ;dividing LBA by the sectors per track, result in ax
    ;ax = result, dx = rest
    inc dx; dx = (LBA % spt) + 1
    mov cx, dx; cx = sector
    mov dx, 0
    div word [bpb_heads]
    mov dh, dl
    mov ch, al
    shl ah, 6
    or cl, ah
    pop ax
    mov dl, al
    pop ax
    ret

;params:
;ax is the lba adress
;cl is the number of sectors to read
;dl is the drive number
;ex:bx points to where to store the data
diskRead:
    push ax
    push bx
    push cx
    push dx
    push di
    push cx ;will be erased by conversion
    call lbaToCHS ;getting the real adress
    pop ax; retrieving sectors to read in AL
    ;well that is awkward
    ;floppies are shit, so the documentation recommend to try it 3 times
    mov ah, 02h
    mov di, 3
.retry:
    pusha
    stc ;setting the carry flag
    int 13h
    jnc .finishedReading
    ;here we failed reading

    popa
    call diskReset

    dec di
    test di,di
    jnz .retry

.finishedReading:
    popa
    pop di
    pop dx
    pop cx
    pop bx
    pop ax
    ret

;param: dl: drive number
diskReset:
    pusha
    mov ah,0
    stc
    int 13h
    jc floppyError
    popa
    ret


msg_hello: db "IT IS ASSEMBLY TIME - JUNIOS BOOTING", 0x0D, 0x0A, 0 ;0x0D, 0x0A is ENDL
msg_disk_error: db "ERROR WHILE READING FROM THE DISK dumbass", 0x0D, 0x0A, 0

times 510-($-$$) db 0 ;filling the rest of the sector with blanks
dw 0AA55h ;setting the disk as bootable
