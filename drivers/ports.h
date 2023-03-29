/**
 * @file ports.h
 * @author Théodore MARTIN
 * @brief function header library related to ports writing and reading
 * @version 0.1
 * @date 2023-03-22
 */
#ifndef __PORTS__
#define __PORTS__
#include "../libs/utils.h"
/**
 * @brief Read byte value from a port
 * 
 * @param[in] port the desired port to read
 * @return u8 the value held in the port
 */
u8 portByteIn(u16);

/**
 * @brief Write a byte to a port
 * 
 * @param[in] port the desired port to write to
 * @param[in] data the desired value that sould be written
 */
void portByteOut(u16, u8);

/**
 * @brief Read a full word to a port
 * 
 * @param[in] port the desired port to read
 * @return u16 the value held in the port
 */
u16 portWordIn(u16);

/**
 * @brief write a word to a port
 * 
 * @param[in] port the desired port to write to
 * @param[in] data the data that should be written
 */
void portWordOut(u16, u16);

#endif