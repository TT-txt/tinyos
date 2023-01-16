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
    /*TODO: implement str split or something */
    if(!str_cmp(buff, "HELP")) {
        printStr("WIKI");
    } else {
        printStr("JuniOs: commande inconnue: ");
        printStr(buff);
        printStr("\nPour obtenir une liste des commandes disponnibles, entrez \"HELP\"");
    }
}