#ifndef __STRINGS__
#define __STRINGS__

#include "utils.h"
#include "memory.h"

/*Functions related to strings (no joke)*/
u32 str_len(char *);
i8 str_cmp(char *, char *);
void strReverse(char *);
void append(char *, char);
u32 wordCount(char *, char);
u32 nthWordSize(char *, char, u32);
char *getNthWord(char *, char , u32);

void hex_to_ascii(int ,char *);

#endif