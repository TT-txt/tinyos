/**
 * @file idt.h
 * @author Théodore MARTIN
 * @brief library containing everything related to the Interrupt Descriptor Table
 * @version 0.1
 * @date 2023-03-22
 */
#ifndef __IDT__
#define __IDT__
#include "../libs/utils.h"
/* Interrupt description table - storing interrupts
 * Table containing telling the CPU where the ISR (interrupt service routines)
 * are stored, one per interrupt.
 * https://wiki.osdev.org/IDT
*/

#define KERNCS 0x08 /* kernel selector */
#define IDTNB 256 /* number of interrupts - we need 256 else the kernel may panic */

typedef struct {
    u16 lOffset;
    u16 sel; /*always KERNCS*/
    u8 zero;
    u8 flags;
    u16 hOffset;
} __attribute__((packed)) IDTGate; /*using packed to get a fixed size*/

typedef struct {
    u16 limit;
    u32 base;
} __attribute__((packed)) IDTRegister;

/* Global variables */
extern IDTGate IDT[IDTNB];
extern IDTRegister IDTReg;

/**
 * @brief initialize the IDT Register (or gate)
 * 
 * @param[in] n the gate number
 * @param[in] handler the function handling the interrupt
 * 
 */
void setIDTGate(u8, u32);

/**
 * @brief Loads the lidt command, to load the IDT
 * https://c9x.me/x86/html/file_module_x86_id_156.html
 */
void setIDT();

#endif