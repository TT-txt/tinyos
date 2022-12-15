#include "utils.h"

u32 str_len(char *str)
{
    u32 result = 0;
    while(str[result] != '\0') {
        result++;
    }
    return result;
}

void mem_cpy(char *src, char *dest, u32 nbBytes)
{
    for (u32 i = 0; i < nbBytes; ++i) {
        *dest++ = *src++;
    }
}

void strReverse(char *str)
{
    char temp;
    u32 size = str_len(str);
    for (u32 i = 0; i < size/2; ++i) {
        temp = str[i];
        str[i] = str[size - i - 1];
        str[size - i - 1] = temp;
    }
}

void iToA(i32 n, char *str) {
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    /* TODO: implement "reverse" */
}

void append(char *str, char *appendix) 
{
    u32 appendPoint = str_len(str);
    u32 size = str_len(appendix);
    for (u32 i = 0; i < size; ++i) {
        str[appendPoint + i] = appendix[i];
    }
    str[appendPoint + size - 1] = '\0';
}