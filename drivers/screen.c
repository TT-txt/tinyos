#include "screen.h"

/* private functions */
u32 getOffset(u8 row, u8 column);
u8 getCols(u32 offset);
u8 getRows(u32 offset);

/* general functions */
u32 getVGAOffset() {
    portByteOut(0x3D4, 14); /* asking vga control register */
    u16 position = portByteIn(0x3D5); /* retrieving the position high bytes*/
    position = position << 8; /* shifting to the top bytes */
    portByteOut(0x3D4, 15); /*requesting low bytes*/
    position += portByteIn(0x3D5); /*adding the low bytes*/ 
    /* 1 vga cell is made of the char & its data (color & background) */
    /* We have to multiply the position by 2 to know where to write */
    return (u32) (position * 2);
}

void setVGAOffset(u32 offset)
{
    /* same as prior, but writing instead of reading */
    offset /= 2;
    portByteOut(0x3D4, 14);
    portByteOut(0x3D5, (u8)(offset >> 8));
    portByteOut(0x3D4, 15);
    portByteOut(0x3D5, (u8)(offset & 0xFF));
}

void clearScreen()
{
    u16 screenSize = MAX_COLS * MAX_ROWS;
    u8 *vga = (u8 *) VIDEO_MEMORY;
    for(u16 i = 0; i < screenSize; ++i) {
        vga[i * 2] = ' ';
        vga[i * 2 + 1] = WHITE_TEXT_BLACK_BACKGROUND;
    }
    setVGAOffset(getOffset(0,0));
}

void printChr(char chr)
{
    i32 offset = getVGAOffset();
    if (chr == '\n') {
        i32 missingColsToNewLine = (MAX_COLS - getCols(offset)) * 2;
        offset += missingColsToNewLine;
    } else if (chr == '\t') {
        offset += 8;
    } else {
        u8 *vga = (u8 *) VIDEO_MEMORY;
        vga[offset] = chr;
        vga[offset + 1] = WHITE_TEXT_BLACK_BACKGROUND;
        offset += 2;
    }
    /* scrolling the screen */
    if (offset >= MAX_COLS * MAX_ROWS * 2) {
        for (u8 i = 1; i < MAX_ROWS; ++i) {
            mem_cpy(getOffset(i, 0) + VIDEO_MEMORY,
                    getOffset(i-1, 0) + VIDEO_MEMORY,
                    MAX_COLS * 2);
        }
        char *lastLine = getOffset(MAX_ROWS - 1, 0) + VIDEO_MEMORY;
        for (u8 i = 0; i < MAX_COLS * 2; ++i) 
            lastLine[i] = 0;
        offset -= 2 * MAX_COLS;
    }
    setVGAOffset(offset);
}

void printChrAtPos(char chr, u8 x, u8 y) 
{
    i32 offset = getOffset(y, x);
    setVGAOffset(offset);
    u8 *vga = (u8 *) VIDEO_MEMORY;
    vga[offset] = chr;
    vga[offset + 1] = WHITE_TEXT_BLACK_BACKGROUND;
}

/* print text at the next position*/
void printStr(char *str)
{
    u32 size = str_len(str);
    for (u32 i = 0; i < size; ++i) {
        printChr(str[i]);
    }
}

void printStrAtPos(char *str, u8 x, u8 y)
{
    u32 size = str_len(str);
    for (u32 i = 0; i < size; ++i) {
        printChrAtPos(str[i], (x + i) % MAX_COLS, y + (x + i) / MAX_COLS);
    }
}

/* private functions */
u32 getOffset(u8 row, u8 column)
{
    return 2 * (row * MAX_COLS + column);
}

u8 getCols(u32 offset)
{
    return (offset / 2) % MAX_COLS;
}

u8 getRows(u32 offset)
{
    return (offset / 2) / MAX_COLS;
}