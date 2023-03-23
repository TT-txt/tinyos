[extern ISRHandler]
[extern IRQHandler]

; thanks to https://wiki.osdev.org/ISR
isrWrapper:
    ; 1. Save CPU state
	pusha ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax
	mov ax, ds ; Lower 16-bits of eax = ds.
	push eax ; save the data segment descriptor
	mov ax, 0x10  ; kernel data segment descriptor
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
    ; 2. Call C handler
	call ISRHandler
    ; 3. Restore state
	pop eax 
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	popa
	add esp, 8 ; Cleans up the pushed error code and pushed ISR number
	sti
	iret ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP

;same as for isr
irqWrapper:
    pusha 
    mov ax, ds
    push eax
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    call IRQHandler; calls the handler stored in the array. See kernel/isr.c
    pop ebx  ;Different than the ISR code
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx
    popa
    add esp, 8
    sti
    iret 

; We don't get information about which interrupt was caller
; when the handler is run, so we will need to have a different handler
; for every interrupt.
; Furthermore, some interrupts push an error code onto the stack but others
; don't, so we will push a dummy error code for those which don't, so that
; we have a consistent stack for all of them.

; ISR globals
global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31
;IRQs global
global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15

; 0: Divide By Zero Exception
isr0:
    cli
    push byte 0
    push byte 0
    jmp isrWrapper

; 1: Debug Exception
isr1:
    cli
    push byte 0
    push byte 1
    jmp isrWrapper

; 2: Non Maskable Interrupt Exception
isr2:
    cli
    push byte 0
    push byte 2
    jmp isrWrapper

; 3: Int 3 Exception
isr3:
    cli
    push byte 0
    push byte 3
    jmp isrWrapper

; 4: INTO Exception
isr4:
    cli
    push byte 0
    push byte 4
    jmp isrWrapper

; 5: Out of Bounds Exception
isr5:
    cli
    push byte 0
    push byte 5
    jmp isrWrapper

; 6: Invalid Opcode Exception
isr6:
    cli
    push byte 0
    push byte 6
    jmp isrWrapper

; 7: Coprocessor Not Available Exception
isr7:
    cli
    push byte 0
    push byte 7
    jmp isrWrapper

; 8: Double Fault Exception (With Error Code!)
isr8:
    cli
    push byte 8
    jmp isrWrapper

; 9: Coprocessor Segment Overrun Exception
isr9:
    cli
    push byte 0
    push byte 9
    jmp isrWrapper

; 10: Bad TSS Exception (With Error Code!)
isr10:
    cli
    push byte 10
    jmp isrWrapper

; 11: Segment Not Present Exception (With Error Code!)
isr11:
    cli
    push byte 11
    jmp isrWrapper

; 12: Stack Fault Exception (With Error Code!)
isr12:
    cli
    push byte 12
    jmp isrWrapper

; 13: General Protection Fault Exception (With Error Code!)
isr13:
    cli
    push byte 13
    jmp isrWrapper

; 14: Page Fault Exception (With Error Code!)
isr14:
    cli
    push byte 14
    jmp isrWrapper

; 15: Reserved Exception
isr15:
    cli
    push byte 0
    push byte 15
    jmp isrWrapper

; 16: Floating Point Exception
isr16:
    cli
    push byte 0
    push byte 16
    jmp isrWrapper

; 17: Alignment Check Exception
isr17:
    cli
    push byte 0
    push byte 17
    jmp isrWrapper

; 18: Machine Check Exception
isr18:
    cli
    push byte 0
    push byte 18
    jmp isrWrapper

; 19: Reserved
isr19:
    cli
    push byte 0
    push byte 19
    jmp isrWrapper

; 20: Reserved
isr20:
    cli
    push byte 0
    push byte 20
    jmp isrWrapper

; 21: Reserved
isr21:
    cli
    push byte 0
    push byte 21
    jmp isrWrapper

; 22: Reserved
isr22:
    cli
    push byte 0
    push byte 22
    jmp isrWrapper

; 23: Reserved
isr23:
    cli
    push byte 0
    push byte 23
    jmp isrWrapper

; 24: Reserved
isr24:
    cli
    push byte 0
    push byte 24
    jmp isrWrapper

; 25: Reserved
isr25:
    cli
    push byte 0
    push byte 25
    jmp isrWrapper

; 26: Reserved
isr26:
    cli
    push byte 0
    push byte 26
    jmp isrWrapper

; 27: Reserved
isr27:
    cli
    push byte 0
    push byte 27
    jmp isrWrapper

; 28: Reserved
isr28:
    cli
    push byte 0
    push byte 28
    jmp isrWrapper

; 29: Reserved
isr29:
    cli
    push byte 0
    push byte 29
    jmp isrWrapper

; 30: Reserved
isr30:
    cli
    push byte 0
    push byte 30
    jmp isrWrapper

; 31: Reserved
isr31:
    cli
    push byte 0
    push byte 31
    jmp isrWrapper

irq0:
	cli
	push byte 0
	push byte 32
	jmp irqWrapper

irq1:
	cli
	push byte 1
	push byte 33
	jmp irqWrapper

irq2:
	cli
	push byte 2
	push byte 34
	jmp irqWrapper

irq3:
	cli
	push byte 3
	push byte 35
	jmp irqWrapper

irq4:
	cli
	push byte 4
	push byte 36
	jmp irqWrapper

irq5:
	cli
	push byte 5
	push byte 37
	jmp irqWrapper

irq6:
	cli
	push byte 6
	push byte 38
	jmp irqWrapper

irq7:
	cli
	push byte 7
	push byte 39
	jmp irqWrapper

irq8:
	cli
	push byte 8
	push byte 40
	jmp irqWrapper

irq9:
	cli
	push byte 9
	push byte 41
	jmp irqWrapper

irq10:
	cli
	push byte 10
	push byte 42
	jmp irqWrapper

irq11:
	cli
	push byte 11
	push byte 43
	jmp irqWrapper

irq12:
	cli
	push byte 12
	push byte 44
	jmp irqWrapper

irq13:
	cli
	push byte 13
	push byte 45
	jmp irqWrapper

irq14:
	cli
	push byte 14
	push byte 46
	jmp irqWrapper

irq15:
	cli
	push byte 15
	push byte 47
	jmp irqWrapper