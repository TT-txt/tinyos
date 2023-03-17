#include "cliTools.h"

void printBanner()
{
    printStr("    .---.                              .-'''-.        \n");
    printStr("    |   |                             '   _    \\      \n");
    printStr("    '---'              _..._   .--. /   /` '.   \\     \n");
    printStr("    .---.            .'     '. |__|.   |     \\  '     \n");
    printStr("    |   |           .   .-.   ..--.|   '      |  '    \n");
    printStr("    |   |           |  '   '  ||  |\\    \\     / /     \n");
    printStr("    |   |   _    _  |  |   |  ||  | `.   ` ..' / _    \n");
    printStr("    |   |  | '  / | |  |   |  ||  |    '-...-'`.' |   \n");
    printStr("    |   | .' | .' | |  |   |  ||  |           .   | / \n");
    printStr("    |   | /  | /  | |  |   |  ||__|         .'.'| |// \n");
    printStr(" __.'   '|   `'.  | |  |   |  |           .'.'.-'  /  \n");
    printStr("|      ' '   .'|  '/|  |   |  |           .'   \\_.'   \n");
    printStr("|____.'   `-'  `--' '--'   '--'                       \n");
}

void userInputHandler(char *buff)
{
    u32 wordNumber = wordCount(buff, ' ');
    if (wordNumber == 0) {
        printStr("No command entered...\n");
    }
    char *firstWord = getNthWord(buff, ' ', 0);
    /*TODO: implement str split or something */
    if(!str_cmp(firstWord, "HELP")) {
        printStr("WIKI");
    } else {
        printStr("JuniOs: commande inconnue: ");
        printStr(buff);
        printStr("\nPour obtenir une liste des commandes disponnibles, entrez \"HELP\"");
    }
}