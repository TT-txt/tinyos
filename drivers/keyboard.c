#include "keyboard.h"
#include "../kernel/isr.h"
#include "ports.h"
#include "screen.h"

/* global variabel */
static char userInput[256];

const char keycodeToAscii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 
        'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G', 
        'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V', 
        'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};

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
    u8 keycode = portByteIn(0x60);
    if (keycode > SCMAX)
        return;
    if (keycode == BACKSPACE) {
        /* TODO remove last shit from buffer */
    } else if (keycode == ENTER) {
        /*Todo : submit command I guess */
    } else if (keycode <= 0x39 + 0x80) {
        /* TODO Implement history ?, up key */
    } else {
        char chr = keycodeToAscii[keycode];
        char str[2] = {chr, '\0'};
        append(userInput, str);
    }
}