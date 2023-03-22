/**
 * @file timer.h
 * @author Théodore MARTIN
 * @brief function headers library related to timers, date and time 
 * @version 0.1
 * @date 2023-03-22
 */
#ifndef __TIMER__
#define __TIMER__
#include "../libs/utils.h"
/**
 * @brief Function linking our timer callback to the IRQ interruption to setup our timer.
 * Everytime a tick passes, it will call our callback that will then increase the timer value
 * 
 * @param[in] freq the frequency of the timer. used to make it faster or slower
 */
void initTimer(u32);

/**
 * @brief Get the current tick value
 * 
 * @return u32 the tick value
 */
u32 getTick();

#endif