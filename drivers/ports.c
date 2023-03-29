/**
 * @file ports.c
 * @author Théodore MARTIN
 * @brief function library containing everything related to ports
 * @version 0.1
 * @date 2023-03-22
 */

#include "ports.h"

u8 portByteIn(u16 port)
{
    u8 result;
    /* Quick tutorial on __ASM__ syntax */
    /* based on AT&T, so in those case: source, destination */
    /* "=a" sets the variable result to the value contained in eax */
    /* "d" (port) sets the register edx to the value contained in port*/
    /* "instruciton src, destination" : output : input */
    __asm__("in %%dx, %%al": "=a"(result) : "d"(port));
    return result;
}

void portByteOut(u16 port, u8 data)
{
    __asm__("out %%al, %%dx": :"a"(data), "d"(port));
}

u16 portWordIn(u16 port)
{
    u16 result;
    __asm__("in %%dx, %%al": "=a"(result) : "d"(port));
    return result;
}

void portWordOut(u16 port, u16 data)
{
    __asm__("out %%al, %%dx": :"a"(data), "d"(port));
}