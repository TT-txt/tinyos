/**
 * @file kernel.c
 * @author Théodore MARTIN
 * @brief OS Entry point
 * @version 0.1
 * @date 2023-03-22
 */

#include "../drivers/screen.h"
#include "../apps/cliTools.h"
#include "isr.h"
#include "idt.h"
#include "timer.h"
#include "../drivers/keyboard.h"
#include "../libs/memory.h"

//https://github.com/cfenollosa/os-tutorial

/**
 * @brief the kernel entry point
 * 
 * @return void
 */
void main()
{
    /* Inits */
    ISRInstall();
    initTimer(50);
    KBInit();
    __asm__ volatile("sti");
    clearScreen();
    printStr("Hello, and Welcome to\n");
    printBanner();
    printStr("The future of the operating system, living like it's 1984\n");
    printStr("user@JuniOs:~$");
}