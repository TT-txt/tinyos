/**
 * @file memory.c
 * @author Théodore MARTIN
 * @brief rewritten function related to memory model to replace the one in stdlib
 * @version 0.1
 * @date 2023-03-22
 */
#include "memory.h"

/* Global variable */
/* This is where we have some free memory, as the kernel starts at 0x1000 */
u32 freeMemPosition = 0x10000;

/* Utilities - functions of the libc */
void mem_cpy(char *src, char *dest, u32 nbBytes)
{
    for (u32 i = 0; i < nbBytes; ++i) {
        *dest++ = *src++;
    }
}

/* used to fill space of size len from dest as value */
void mem_set(u8 *dest, u8 value, u32 len)
{
    u8 *temp = (u8 *)dest;
    for (; len != 0; --len) {
        *temp++ = value;
    }
}

u32 mallok(u32 size /*int align, u32 *physicalPos*/) {
    if (freeMemPosition & 0xFFFFF000) {
        freeMemPosition &= 0xFFFFF000;
        freeMemPosition += 0x1000;
    }
    //if (physicalPos) *physicalPos = freeMemPos;
    u32 position = freeMemPosition;
    freeMemPosition += size;
    return position;
}

u32 calloc(u32 nbObj, u32 size)
{
    i32 realSize = nbObj * size;
    u32 baseAddr = mallok(realSize);
    mem_set((char *)baseAddr, 0, nbObj);
    return baseAddr;
}