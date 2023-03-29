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

/**
 * @brief standard malloc
 * 
 * @param[in] size the size that should allocated
 * 
 * @return u32 free memory localisation
 */
u32 mallok(u32);

/**
 * @brief recreation of the standard calloc
 * 
 * @param[in] nbObj the number of object to alloc
 * @param[in] size the size of 1 object
 * 
 * @return the position of the allocated memory
 */
u32 callok(u32, u32);
#endif