#include "memory.h"

/* Global variable */
/* This is where we have some free memory, as the kernel starts at 0x1000 */
u32 freeMemPosition = 0x10000;

/* Functions */
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

/* currently: we're pointing to some free space and we keep growing */
u32 malloc_t(u32 size, int align, u32 *addr)
{
    if (align == 1 && (freeMemPosition & 0xFFFFF000)) {
        freeMemPosition &= 0xFFFFF000;
        freeMemPosition += 0x1000;
    }
    if (addr)
        *addr = freeMemPosition;
    u32 result = freeMemPosition;
    freeMemPosition += size;
    return result;
}