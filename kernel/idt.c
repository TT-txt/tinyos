#include "idt.h"

IDTGate IDT[IDTNB];
IDTRegister IDTReg;

void setIDTGate(u8 n, u32 handler)
{
    IDT[n].lOffset = low16(handler);
    IDT[n].sel = KERNCS;
    IDT[n].zero = 0;
    IDT[n].flags = 0x8E; /* p=1, dpl=0b00, type=0b1110 => type_attributes=0b1000_1110=0x8E */
    IDT[n].hOffset = high16(handler);
}

void setIDT()
{
    IDTReg.base = (u32) &IDT;
    IDTReg.limit = IDTNB * sizeof(IDTGate) - 1;
    __asm__ __volatile__("lidt (%0)" : : "r"(&IDTReg));
    /* remember: never load &IDT, always work with &IDTReg*/
}