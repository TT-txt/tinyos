#ifndef __MEMORY__
#define __MEMORY__
#include "utils.h"

void mem_cpy(char *, char *, u32);
void mem_set(u8 *, u8, u32);

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
//u32 mallok(u32);
#endif