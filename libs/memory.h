#ifndef __MEMORY__
#define __MEMORY__
#include "utils.h"
#define __NEWMALLOC__ 1

void mem_cpy(char *, char *, u32);
void mem_set(u8 *, u8, u32);

#if __NEWMALLOC__ == 0
u32 mallok(u32);
#else
typedef struct memBlock {
    u32 allocatedSize;
    u32 usedSize;
    int index;
    struct memBlock *next;
    struct memBlock *prev;
    struct memBlock *splitLeft;
    struct memBlock *splitRight;
} memBlock;

void *mallok(u32);
void *reallok(void *, u32);
void *callok(u32, u32);
void freek(void *);
#endif
#endif