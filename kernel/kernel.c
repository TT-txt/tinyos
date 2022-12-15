#include "../drivers/screen.h"
#include "../apps/cliTools.h"
#include "isr.h"
#include "idt.h"
#include "timer.h"


void main()
{
    clearScreen();
    ISRInstall();
    printStr("Hello, and Welcome to\n");
    printBanner();
    printStr("The future of the operating system, living like it's 1984\n");
}