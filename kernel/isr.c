#include "isr.h"

void ISRInstall()
{
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
    setIDT(); // Load with ASM
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