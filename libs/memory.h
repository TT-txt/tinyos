#ifndef __MEMORY__
#define __MEMORY__
#include "utils.h"

void mem_cpy(char *, char *, u32);
void mem_set(u8 *, u8, u32);
u32 malloc_t(u32, int, u32 *);
void free_t(u32);

/* memory saved list - TODO: maybe remove the prev */
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

linkedMemBlock *getMemBlockAt(linkedMemList, u32 );
void appendMemBlock(linkedMemList *, linkedMemBlock *);
void removeMemBlock(linkedMemList *, linkedMemBlock *);
linkedMemBlock *craftMemBlock(u32, u32);

/*
void insertAllocatedMemBlock(linkedMemList *, linkedMemBlock *);
void insertFreeMemBlock(linkedMemList *, linkedMemBlock *);
*/
#endif