#ifndef __SCREEN__
#define __SCREEN__
#include "./ports.h"
#include "../libs/memory.h"
#include "../libs/strings.h"

/* Constants definitions */
#define VIDEO_MEMORY 0xb8000
#define WHITE_TEXT_BLACK_BACKGROUND 0x0F
#define MAX_ROWS 25
#define MAX_COLS 80

/* Functions */
u32 getVGAOffset();
void setVGAOffset(u32);
void clearScreen();
void printChr(char);
void printChrAtPos(char, u8, u8);
void printStr(char *);
void printStrAtPos(char *, u8, u8);
void removeLastChar();

#endif