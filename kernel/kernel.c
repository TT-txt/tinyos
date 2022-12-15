#include "../drivers/screen.h"
#include "../libs/utils.h" /* technicaly not necessary but we're certain it's here */

void main()
{
    clearScreen();
    for (int i = 0; i < 4000; ++i) {
        printChr('F');
    }
    printStr("A\nB");
}