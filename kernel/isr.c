#include "isr.h"

ISR interruptHandlers[IDTNB];

void ISRInstall()
{
    /* init IDT */
    setIDTGate(0, (u32)isr0);
    setIDTGate(1, (u32)isr1);
    setIDTGate(2, (u32)isr2);
    setIDTGate(3, (u32)isr3);
    setIDTGate(4, (u32)isr4);
    setIDTGate(5, (u32)isr5);
    setIDTGate(6, (u32)isr6);
    setIDTGate(7, (u32)isr7);
    setIDTGate(8, (u32)isr8);
    setIDTGate(9, (u32)isr9);
    setIDTGate(10, (u32)isr10);
    setIDTGate(11, (u32)isr11);
    setIDTGate(12, (u32)isr12);
    setIDTGate(13, (u32)isr13);
    setIDTGate(14, (u32)isr14);
    setIDTGate(15, (u32)isr15);
    setIDTGate(16, (u32)isr16);
    setIDTGate(17, (u32)isr17);
    setIDTGate(18, (u32)isr18);
    setIDTGate(19, (u32)isr19);
    setIDTGate(20, (u32)isr20);
    setIDTGate(21, (u32)isr21);
    setIDTGate(22, (u32)isr22);
    setIDTGate(23, (u32)isr23);
    setIDTGate(24, (u32)isr24);
    setIDTGate(25, (u32)isr25);
    setIDTGate(26, (u32)isr26);
    setIDTGate(27, (u32)isr27);
    setIDTGate(28, (u32)isr28);
    setIDTGate(29, (u32)isr29);
    setIDTGate(30, (u32)isr30);
    setIDTGate(31, (u32)isr31);
    /* Remapping the PIC */
    portByteOut(0x20, 0x11);
    portByteOut(0xA0, 0x11);
    portByteOut(0x21, 0x20);
    portByteOut(0xA1, 0x28);
    portByteOut(0x21, 0x04);
    portByteOut(0xA1, 0x02);
    portByteOut(0x21, 0x01);
    portByteOut(0xA1, 0x01);
    portByteOut(0x21, 0x0);
    portByteOut(0xA1, 0x0); 
    /* Installing IRQs */
    setIDTGate(32, (u32)irq0);
    setIDTGate(33, (u32)irq1);
    setIDTGate(34, (u32)irq2);
    setIDTGate(35, (u32)irq3);
    setIDTGate(36, (u32)irq4);
    setIDTGate(37, (u32)irq5);
    setIDTGate(38, (u32)irq6);
    setIDTGate(39, (u32)irq7);
    setIDTGate(40, (u32)irq8);
    setIDTGate(41, (u32)irq9);
    setIDTGate(42, (u32)irq10);
    setIDTGate(43, (u32)irq11);
    setIDTGate(44, (u32)irq12);
    setIDTGate(45, (u32)irq13);
    setIDTGate(46, (u32)irq14);
    setIDTGate(47, (u32)irq15);
    setIDT();
}

char *exceptionMessages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void ISRHandler(reg r)
{
    printStr("Received interrupt: ");
    char s[3];
    iToA(r.intNo, s);
    printStr(s);
    printStr("\n");
    printStr(exceptionMessages[r.intNo]);
    printStr("\n");
}

void regInterruptHandler(u8 n, ISR handler)
{
    interruptHandlers[n] = handler;
}

void IRQHandler(reg r)
{
    /* After every interrupt we need to send an EOI to the PICs
     * or they will not send another interrupt again */
    if (r.intNo >= 40) portByteOut(0xA0, 0x20); /* slave */
    portByteOut(0x20, 0x20); /* master */

    /* Handle the interrupt in a more modular way */
    if (interruptHandlers[r.intNo] != 0) {
        ISR handler = interruptHandlers[r.intNo];
        handler(r);
    }
}