#include "keyboard.h"
#include "../kernel/isr.h"
#include "ports.h"
#include "screen.h"
#include "../apps/cliTools.h"

/* Global variables */
static char userInput[USER_BUFF_SIZE];
static char lastCommand[USER_BUFF_SIZE];
static u16 userInputLength = 0;
static u16 lastInputLength = 0;

/* Edited a bit for azerty */
const char keycodeToAscii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '<', '?', 'A', 'Z', 'E', 'R', 'T', 'Y', 
        'U', 'I', 'O', 'P', '[', ']', '?', '?', 'Q', 'S', 'D', 'F', 'G', 
        'H', 'J', 'K', 'L', 'M', '\'', '`', '?', '\\', 'W', 'X', 'C', 'V', 
        'B', 'N', ',', ';', '.', '/', '?', '?', '?', ' '};


/* private functions defintions */
static void KBCallback();

/* public functions */
void KBInit()
{
    regInterruptHandler(IRQ1, KBCallback);
}

/* Private functions */
static void KBCallback()
{
    /*char temp[129];*/
    u8 keycode = portByteIn(0x60);
    /*iToA(keycode, temp);
    printStr(temp);
    printChr('\n')*/
    if (keycode > SCMAX)
        return;
    if (keycode == BACKSPACE) {
        if (userInputLength != 0) {
            userInput[userInputLength] = ' ';
            userInputLength--;
            removeLastChar();
        }
    } else if (keycode == ENTER) {
        printChr('\n');
        userInputHandler(userInput);
        mem_cpy(userInput, lastCommand, userInputLength);
        lastInputLength = userInputLength;
        userInput[0] = '\0';
        userInputLength = 0;
        printStr("\nuser@JuniOs:~$");
    /*needs a fix*/
    } else if(keycode == UP_ARROW && userInputLength == 0 && lastInputLength != 0) {
        mem_cpy(lastCommand, userInput, lastInputLength);
        userInputLength = lastInputLength;
        printStr(userInput);
    } 
    else {
        char chr = keycodeToAscii[(int)keycode];
        if (userInputLength < USER_BUFF_SIZE) {
            userInput[userInputLength] = chr;
            //append(userInput, chr);
            userInputLength++;
            printChr(chr);
        }
    }
}