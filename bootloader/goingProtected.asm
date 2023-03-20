[BITS 16]
goingProtected:
    cli ; disable interrupts
    lgdt [gdtDescriptor] ;loading the gdt
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax
    jmp CODE_SEGMENT:initProtected

[BITS 32]
initProtected:
    mov ax, DATA_SEGMENT
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ebp, 0x900000 ;updating the stack position to free space
    mov esp, ebp
    call MAIN_PROTECTED