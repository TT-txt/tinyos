#include "cliTools.h"
#define CALCPRES 10

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
    string *words = strSplit(buff, ' ');
    char *firstWord = words[0];
    if(!str_cmp(firstWord, "HELP")) {
        printStr("WIKI");
    } else if(str_cmp(firstWord, "ADD")) {
        if ((wordNumber) != 3) {
            printStr("Pour utiliser la commande ADD, entrez ADD ainsi que deux nombres.\n");
            printStr("Exemple: ADD 8.3 -5.6");
        } else {
            i64 num1 = (i64) strToL(words[1]);
            i64 num2 = (i64) strToL(words[2]);
            i64 res = num1 + num2;
            char *buff = mallok(10 * sizeof(CALCPRES));
            //gcvt(res, CALCPRES-1, buff);
            printStr("\n");
            printStr(words[1]);
            printStr(" + ");
            printStr(words[2]);
            printStr(" = ");
            printStr(buff);
            printStr("\n");
        }
    }
    else {
        printStr("JuniOs: commande inconnue: ");
        printStr(buff);
        printStr("\nPour obtenir une liste des commandes disponnibles, entrez \"HELP\"");
    }
}