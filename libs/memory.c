#include "memory.h"

/* CANT BE USED - size issues
#define MAXEXP 32
#define MINEXP 8
#define MAXCOMPLETE 5
memBlock *freePages[MAXEXP];
i32 completePages[MAXEXP];
static bool memInit = 0;
static u16 pageSize = 4096;
static u16 pageCount = 16;
blockSize = sizeof(memBlock);
*/

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


/* CANT BE USED - RIP */
/*
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
        realIndex = getExp(block->usedSize - blockSize);
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
    block->allocatedSize -= newBlock->usedSize;
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
    unlockMemory;
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
            if (block->allocatedSize % pageSize != 0) page = pageCount;
            freePage(block, page);
            unlockMemory();
            return;
        }
        completePages[index] += 1;
    }
    unlockMemory();
}

u32 malloc_t(u32 size, int align, u32 *addr)
{
    u32 result;
    if (freeMem.len) {
        linkedMemBlock *temp = freeMem.head;
        while (temp != NULL) {
            if (temp->size <= size) {
                result = temp->position;
                *addr = temp->position;
                if (temp->size == size) {
                    removeMemBlock(&freeMem, temp);
                } else {
                    temp->size -= size;
                    temp->position += size;
                }
                linkedMemBlock *newMemBlock = craftMemBlock(size, result);
                appendMemBlock(&allocatedMem, newMemBlock);
                return result;
            }
            temp = temp->next;
        }
    }
    if (align == 1 && (freeMemPosition & 0xFFFFF000)) {
        freeMemPosition &= 0xFFFFF000;
        freeMemPosition += 0x1000;
    }
    if (addr)
        *addr = freeMemPosition;
    result = freeMemPosition;
    freeMemPosition += size;
    linkedMemBlock *newMemBlock = craftMemBlock(size, result);
    appendMemBlock(&allocatedMem, newMemBlock);
    return result;
}

void free_t(u32 position)
{
    linkedMemBlock *toRemove = allocatedMem.head;
    if (toRemove == NULL)
        return;
    while (toRemove != NULL) {
        if (toRemove->position != position)
            toRemove = toRemove->next;
    }
    if (toRemove->position == position) {
        removeMemBlock(&allocatedMem, toRemove);
        appendMemBlock(&freeMem, toRemove);
    }
}

linkedMemBlock *getMemBlockAt(linkedMemList base, u32 index)
{
    linkedMemBlock *result;
    if (index > base.len) {
        result = NULL;
    } else if (index < base.len / 2) {
        result = base.head;
        for (u32 i = 0; i < index; ++i) {
            if (result == NULL) return NULL;
            result = result->next;
        }
    } else {
        result = base.tail;
        for (u32 i = 0; i < index; ++i) {
            if (result == NULL) return NULL;
            result = result->prev;
        }
    }
    return result;
}

void appendMemBlock(linkedMemList *base, linkedMemBlock *block)
{
    if (base == NULL || block == NULL || base->head == NULL || base->tail == NULL)
        return;
    block->next = NULL;
    base->len++;
    if (base->len == 0) {
        base->head = block;
        base->tail = block;
        block->prev = NULL;
    } else {
        linkedMemBlock *temp = base->tail;
        temp->next = block;
        block->prev = temp;
        block->next = NULL;
    }
}

void removeMemBlock(linkedMemList *base, linkedMemBlock *block)
{
    if (block == NULL || base->len == 0 || base->head == NULL || base->tail == NULL)
        return;
    base->len--;
    if (block == base->head) {
        linkedMemBlock *after = block->next;
        base->head = after;
        if (after != NULL)
            after->prev = NULL;
    } else if (block == base->tail) {
        linkedMemBlock *before = block->prev;
        base->tail = before;
        if (before != NULL)
            before->next = NULL;
    } else {
        linkedMemBlock *before = block->prev;
        linkedMemBlock *after = block->next;
        if (block->next != NULL || block->prev != NULL) {
            after->prev = block->prev;
            before->next = block->next;
        }
    }
}
linkedMemBlock *craftMemBlock(u32 size, u32 position)
{
    u32 physicalAddr;
    linkedMemBlock *result = (linkedMemBlock *) malloc_t(sizeof(linkedMemBlock *), 1, &physicalAddr);
    result->size = size;
    result->position = position;
    result->prev = NULL;
    result->next = NULL;
    return result;
}*/

/* --- RANDOM PROTO CODE - USELESS --- */
/* Inserting while containing the position order
void insertAllocatedMemBlock(linkedMemList *base, linkedMemBlock *block)
{
    if (base == NULL || block == NULL || base->head == NULL || base->tail == NULL)
        return;
    if (base->len == 0) {
        base->len = 1;
        base->head = block;
        base->tail = block;
    } else {
        linkedMemBlock *before = base->head;
        linkedMemBlock *after = before->next;
        for (u32 i = 0; i < base->len; ++i) {
            if (after== NULL) {
                before->next = block;
                base->len+=1;
                break;
            } else if ( (before->position <= block->position) & (after->position > block->position) ) {
                    after->prev = block;
                    before->next = block;
                    base->len++;
                    break;
            } else {
                before = after;
                after = before->next;
            }
        }
    }
}
*/

/* inserting while keeping the memory size order
void insertFreeMemBlock(linkedMemList *base, linkedMemBlock *block)
{
    if (base == NULL || block == NULL || base->head == NULL || base->tail == NULL)
        return;
    if (base->len == 0) {
        base->len = 1;
        base->head = block;
        base->tail = block;
    } else {
        linkedMemBlock *before = base->head;
        linkedMemBlock *after = before->next;
        for (u32 i = 0; i < base->len; ++i) {
            if (after== NULL) {
                before->next = block;
                base->len+=1;
                break;
            } else if ( (before->size <= block->size) & (after->size > block->size) ) {
                    after->prev = block;
                    before->next = block;
                    base->len++;
                    break;
            } else {
                before = after;
                after = before->next;
            }
        }
    }
}
*/