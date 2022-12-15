#include "../drivers/screen.h"
#include "../libs/strings.h" /* technicaly not necessary but we're certain it's here */
#include "../libs/utils.h" /* technicaly not necessary but we're certain it's here */

void main()
{
    clearScreen();
    printStr("Hello, Kernel world\nTesting all\n\tFunctions");
    printChrAtPos('X', 10, 10);
    printStrAtPos("Wow!", 20, 12);
}