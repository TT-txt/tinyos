#include "memory.h"

/* Global variable */
/* This is where we have some free memory, as the kernel starts at 0x1000 */
u32 freeMemPosition = 0x10000;
/*allocated needs to be sorted by position */
linkedMemList allocatedMem = {.len = 0, .head = NULL, .tail = NULL};
/* free needs to be sorted by size */
linkedMemList freeMem = {.len = 0, .head = NULL, .tail = NULL};


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

u32 malloc_t(u32 size, int align, u32 *addr)
{
    u32 result;
    if (freeMem.len) {
        /* checking if we can't use a freed position */
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
    /* find the position inside the allocatedMem */
    linkedMemBlock *toRemove = allocatedMem.head;
    if (toRemove == NULL)
        return;
    while (toRemove != NULL) {
        if (toRemove->position != position)
            toRemove = toRemove->next;
    }
    /* temp store it */
    if (toRemove->position == position) {
        /* remove it from the allocatedMem */
        removeMemBlock(&allocatedMem, toRemove);
        /* insert into the free memory */
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
    base->len--; /* we might want to put it down inside the ifs */
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
}



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