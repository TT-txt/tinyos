#include "../drivers/screen.h"
#include "../apps/cliTools.h"
#include "isr.h"
#include "idt.h"
#include "timer.h"
#include "../drivers/keyboard.h"

//https://github.com/cfenollosa/os-tutorial

void main()
{
    /* Inits */
    ISRInstall();
    initTimer(50);
    KBInit();
    clearScreen();
    ISRInstall();
    __asm__ volatile("sti");
    printStr("Hello, and Welcome to\n");
    printBanner();
    printStr("The future of the operating system, living like it's 1984\n");
}