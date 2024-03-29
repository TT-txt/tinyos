/**
 * @file timer.c
 * @author Théodore MARTIN
 * @brief function library related to timers, date and time
 * @version 0.1
 * @date 2023-03-22
*/
#include "timer.h"
#include "../drivers/ports.h"
#include "isr.h"

/* Global tick count */
u32 tick = 0;

/* private functions */
static void callback()
{
    tick++;
}

/* public functions */
void initTimer(u32 f)
{
    regInterruptHandler(IRQ0, callback);
    u32 d = 1193180 / f; /* hardware clock is at 1193180 Hz*/
    portByteOut(0x43, 0x36);
    portByteOut(0x40, (u8)(d & 0xFF));
    portByteOut(0x40, (u8)((d >> 8) & 0xFF));
}

u32 getTick() {
    return tick;
}