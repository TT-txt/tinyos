/**
 * @file memory.h
 * @author Théodore MARTIN
 * @brief File where the memory model is defined
 * @version 0.1
 * @date 2023-03-22
 */
#ifndef __MEMORY__
#define __MEMORY__
#include "utils.h"
#define __NEWMALLOC__ 1

/**
 * @brief standard memory copy
 * 
 * @param[in] src the source of the copy
 * @param[out] dest the destination of the copy
 * @param[in] how many things should be copied
 * 
 * return void
 */
void mem_cpy(char *, char *, u32);

/**
 * @brief standard memory set
 * 
 * @param[out] dest where the data should be set
 * @param[in] value what is used to initialize the data
 * @param[in] len how many data should be set
 * 
 * @return void
 */
void mem_set(u8 *, u8, u32);

#if __NEWMALLOC__ == 0
/**
 * @brief standard malloc
 * 
 * @param[in] size the size that should allocated
 * 
 * @return u32 free memory localisation
 */
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