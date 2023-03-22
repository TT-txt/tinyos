/**
 * @file screen.c
 * @brief Header file for the screen & display library
 * @author Théodore MARTIN
 * @version 0.1
 * @date 22/04/2022
*/
#ifndef __SCREEN__
#define __SCREEN__
#include "./ports.h"
#include "../libs/memory.h"
#include "../libs/strings.h"

/* Constants definitions */
#define VIDEO_MEMORY 0xb8000
#define WHITE_TEXT_BLACK_BACKGROUND 0x0F
#define MAX_ROWS 25
#define MAX_COLS 80

/* Functions */

/**
 * @brief Retrieving the current offset of the VGA "cursor"
 * 
 * @return u32, the requested offset
*/
u32 getVGAOffset();

/**
 * @brief Set the current VGA offset value to the input
 * 
 * @param[in] offset The desired offset new value
 * 
 * @return void
*/
void setVGAOffset(u32);

/**
 * @brief Remove everything on screen and place cursor to top left
 * 
 * @return void
 */
void clearScreen();

/**
 * @brief print the char on the screen to the next position (cursor is automatic)
 * 
 * @param chr char that should be printed
 * 
 * @return void
 */
void printChr(char);

/**
 * @brief deletes the last printed char on screen
 * 
 * @return void
 */
void removeLastChar();

/**
 * @brief function printing a char to a certain x/y position on screen
 * 
 * @param chr the char that should be printed
 * @param x the x coordinates (>0)
 * @param y the y coordinates (>0)
 */
void printChrAtPos(char, u8, u8);

/**
 * @brief prints a string to the next position on screen (cursor is auto)
 * 
 * @param str the string that should be printed
 */
void printStr(char *);

/**
 * @brief function printing a string at a certain x/y position
 * 
 * @param str the string that should be printed
 * @param x the x coordinates where the string should be (>0)
 * @param y the y coordinates where the string should be (>0)
 */
void printStrAtPos(char *, u8, u8);

#endif