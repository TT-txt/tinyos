/**
 * @file keyboard.h
 * @author Théodore MARTIN
 * @brief function library header related to keyboard and inputs
 * @version 0.1
 * @date 2023-03-22
 */

#ifndef __KEYBOARD__
#define __KEYBOARD__

#define SCMAX 57
#define ENTER 0x1C /* Ascii definition */
#define BACKSPACE 0x0E /*Ascii definition */
#define USER_BUFF_SIZE 256 /* WARNING: TYPE USED FOR buffLength should match*/
#define UP_ARROW 27
/**
 * @brief function linking the bios keyboard interrupt to the callback
 * This function links the bios keyboard interrupt obtained with IRQs
 * to our keyboard callback. It allows us to setup a buffer and obtain
 * user input. It allows us to retrieve the keycode pressed that we then 
 * convert in the KBCallback to ascii char, using an hard coded table.
 */
void KBInit();

#endif