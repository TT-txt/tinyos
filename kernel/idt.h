#ifndef __IDT__
#define __IDT__
#include "../libs/utils.h"
/* Interrupt description table - storing interrupts */

#define KERNCS 0x08 /* kernel selector */
#define IDTNB 256 /* number of interrupts */

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

/* functions */
void setIDTGate(u8, u32);
void setIDT();

#endif