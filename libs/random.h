/**
 * @file random.c
 * @author Théodore MARTIN
 * @brief function library to get pseudo random numbers
 * @version 0.1
 * @date 2023-03-22 
 */
#ifndef __K_RANDOM__
#define __K_RANDOM__
#include "utils.h"
/**
 * @brief get a pseudo random integer between [0; 255]
 * 
 * @return u8 the random
 */
u8 randomK();

/**
 * @brief get a pseudo random value between [0; 1]
 * 
 * @return f32 the random
 */
f32 randK();

/**
 * @brief function to reset the pseudo random generator
 * 
 */
void resetRandom();

#endif