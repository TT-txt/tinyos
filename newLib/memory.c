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

#if __NEWMALLOC__ == 0
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
#else

#define MAXEXP 32
#define MINEXP 8
#define MAXCOMPLETE 5
memBlock *freePages[MAXEXP];
i32 completePages[MAXEXP];
static bool memInit = 0;
static u16 pageSize = 4096;
static u16 pageCount = 16;
u32 blockSize = sizeof(memBlock);

// utilities to manage memory 
static inline void lockMemory()
{
    __asm__ volatile("cli");
}

static inline void unlockMemory()
{
    __asm__ volatile("sti");
}

static inline u32 *alloc(i32 page)
{
    //TODO: add a way to check overflow ?
    return (u32 *) freeMemPosition + page * pageSize;
}

static inline void freePage(u32 pageLoc, i32 numerOfPages)
{
    //TODO
}

static inline i32 getExp(u32 size)
{
    if (size < (1<<MINEXP)) {
        return -1; //shouldn't happened
    }
    i32 shift = MINEXP;
    while (shift < MAXEXP) {
        if ((1<<(++shift)) > (i32) size) break;
    }
    return shift - 1;
}

static inline void removeBlock(memBlock *block)
{
    if (freePages[block->index] == block)
        freePages[block->index] = block->next;
    if (block->next != NULL) block->next->prev = block->prev;
    if (block->prev != NULL) block->prev->next = block->next;
    block->next = block->prev = NULL;
    block->index = -1;
}

static inline void insertBlockAt(memBlock *block, i32 index)
{
    i32 realIndex;
    if (index < 0) {
        realIndex = getExp(block->allocatedSize - blockSize);
        if (realIndex < MINEXP) realIndex = MINEXP;
    } else {
        realIndex = index;
    }
    block->index = index;
    if (freePages[realIndex] != NULL) {
        block->next = freePages[realIndex];
        freePages[realIndex]->prev = block;
    }
    freePages[realIndex] = block;
}

static inline memBlock *split(memBlock *block)
{
    u32 rest = block->allocatedSize - block->usedSize - blockSize;
    memBlock *newBlock = (memBlock *)((u32)block + blockSize + block->usedSize);
    newBlock->allocatedSize = rest;
    newBlock->next = NULL;
    newBlock->prev = NULL;
    newBlock->splitLeft = block;
    newBlock->splitRight = block->splitRight;
    if (newBlock->splitRight != NULL) newBlock->splitRight->splitLeft = newBlock;
    block->splitRight = newBlock;
    block->allocatedSize -= newBlock->allocatedSize;
    insertBlockAt(newBlock, -1);
    return newBlock;
}

static inline memBlock *absorbRight(memBlock *block)
{
    memBlock *toAbsorb = block->splitRight;
    removeBlock(toAbsorb);
    block->allocatedSize += toAbsorb->allocatedSize;
    if (toAbsorb->splitRight != NULL)
        toAbsorb->splitRight->splitLeft = block;
    return block;
}

static inline memBlock *meltLeft(memBlock *block)
{
    memBlock *toMelt = block->splitLeft;
    toMelt->allocatedSize += block->allocatedSize;
    toMelt->splitRight = block->splitRight;
    if (block->splitRight != NULL) block->splitRight->splitLeft = toMelt;
    return toMelt;
}

static memBlock *createNewBlock(u32 size)
{
    u32 page;
    u32 usedSize;
    memBlock *block;
    usedSize = size + blockSize;
    page = usedSize / pageSize;
    if ((usedSize % pageSize) != 0) page++;
    page = (page < pageCount) ? pageCount : page;
    block = (memBlock *) alloc(page);
    if (block == NULL) return NULL;
    block->allocatedSize = page * pageSize;
    block->usedSize = size;
    block->index = -1;
    block->next = block->prev = NULL;
    block->splitRight = block->splitLeft = NULL;
    return block;
}

void *mallok(u32 size)
{
    i32 index;
    memBlock *block = NULL;
    void *ptr;
    lockMemory();
    if (!memInit) {
        for(index = 0; index < MAXEXP; ++index) {
            freePages[index] = NULL;
            completePages[index] = 0;
        }
        memInit = true;
    }
    index = getExp(size);
    index = (index < MINEXP) ? MINEXP : index;
    block = freePages[index];
    while (block != NULL) {
        if ((block->allocatedSize - blockSize) >= (size + blockSize))
            break;
        block = block->next;
    }
    if (block == NULL) {
        if ((block = createNewBlock(size)) != NULL) {
            unlockMemory();
            return NULL;
        }
        index = getExp(block->allocatedSize - blockSize);
    } else {
        removeBlock(block);
        if (block->splitLeft == NULL && block->splitRight == NULL)
            completePages[index]--;
    }
    block->usedSize = size;
    u32 rest = block->allocatedSize - size - blockSize * 2;
    if ((int) rest > 0) {
        int childIdx = getExp(rest);
        if (childIdx >= 0) {
            memBlock *newBlock = split(block);
            newBlock = newBlock; //warning bypass 101
        }
    }
    ptr = (void *)((unsigned int)block + blockSize);
    unlockMemory();
    return ptr;
}

void freek(void *ptr)
{
    int index;
    memBlock *block;
    if (ptr == NULL) return;
    lockMemory();
    block = (memBlock *)((u32)ptr - blockSize);
    while ((block->splitLeft != NULL) && (block->splitLeft->index >= 0)) {
        block = meltLeft(block);
        removeBlock(block);
    }
    while ((block->splitRight != NULL) && (block->splitRight->index >= 0)) {
        block = absorbRight(block);
    }
    index = getExp(block->allocatedSize - blockSize);
    index = (index < MINEXP) ? MINEXP : index;
    if (block->splitLeft == NULL && block->splitRight == NULL) {
        if (completePages[index] == MAXCOMPLETE) {
            u32 page = block->allocatedSize / pageSize;
            if (block->allocatedSize % pageSize != 0) page +=1;
            if (page < pageCount) page = pageCount;
            freePage(block, page);
            unlockMemory();
            return;
        }
        completePages[index] += 1;
    }
    insertBlockAt(block, index);
    unlockMemory();
}
#endif