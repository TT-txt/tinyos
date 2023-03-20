#ifndef __MEMORY__
#define __MEMORY__
#include "utils.h"

void mem_cpy(char *, char *, u32);
void mem_set(u8 *, u8, u32);
u32 mallok(u32);

/* CANT BE USED DUE TO SPACE ISSUES
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
*/
/* __OLD__
typedef struct {
    void *prev;
    void *next;
    u32 position;
    u32 size;
} linkedMemBlock;

typedef struct {
    linkedMemBlock *head;
    linkedMemBlock *tail;
    u32 len;
} linkedMemList;

u32 malloc_t(u32, int, u32 *);
void free_t(u32);
linkedMemBlock *getMemBlockAt(linkedMemList, u32 );
void appendMemBlock(linkedMemList *, linkedMemBlock *);
void removeMemBlock(linkedMemList *, linkedMemBlock *);
linkedMemBlock *craftMemBlock(u32, u32);
void insertAllocatedMemBlock(linkedMemList *, linkedMemBlock *);
void insertFreeMemBlock(linkedMemList *, linkedMemBlock *);
*/
#endif