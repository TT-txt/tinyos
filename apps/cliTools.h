/**
 * @file cliTools.h
 * @author Théodore MARTIN
 * @brief function containing usefull command line tools & function
 * @version 0.1
 * @date 2023-03-22 
 */
#ifndef __CLITOOLS__
#define __CLITOOLS__
#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "../libs/utils.h"

/**
 * @brief function to display on screen a cool banner
 */
void printBanner();

/**
 * @brief 
 * 
 * @param[in] buff the keyboard content buffer
 * 
 * @return void
 */
void userInputHandler(char *);

#endif