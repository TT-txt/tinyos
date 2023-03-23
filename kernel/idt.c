/**
 * @file idt.c
 * @author Théodore MARTIN
 * @brief function linked to the Interrupt descriptor table
 * @version 0.1
 * @date 2023-03-23
 */

#include "idt.h"

IDTGate IDT[IDTNB];
IDTRegister IDTReg;

void setIDTGate(u8 n, u32 handler)
{
    /*  filling the struct with the values
        explained here https://wiki.osdev.org/Interrupt_Descriptor_Table
        ("Structure on x86-64") */
    IDT[n].lOffset = low16(handler);
    IDT[n].sel = KERNCS;
    IDT[n].zero = 0;
    IDT[n].flags = 0x8E; /* p=1, dpl=0b00, type=0b1110 => type_attributes=0b1000_1110=0x8E */
    IDT[n].hOffset = high16(handler);
}

void setIDT()
{
    /*  retrieving the adresses of the idt 
        It will then be stored inside the IDTR (r for register) */
    IDTReg.base = (u32) &IDT;
    IDTReg.limit = IDTNB * sizeof(IDTGate) - 1;
    /* loading the idt */
    __asm__ __volatile__("lidt (%0)" : : "r"(&IDTReg));
    /* remember: never load &IDT, always work with &IDTReg*/
}