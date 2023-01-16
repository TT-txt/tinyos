#include "utils.h"

u32 str_len(char *str)
{
    u32 result = 0;
    while(str[result] != '\0') {
        result++;
    }
    return result;
}

i8 str_cmp(char *str1, char *str2)
{
    while ((*str1 != '\0' && *str2 != '\0') && *str1 == *str2) {
        *str1+=1;
        *str2+=1;
    }
    if (*str1 == *str2)
        return 0;
    else
        return *str1 - *str2;
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

u32 wordCount(char *str, char del)
{
    if (*str == '\0')
        return 0;
    
    u32 result = 1;
    bool stringDetected = false;
    while(*str++ != '\0') {
        if (*str == '\"')
            stringDetected = !stringDetected;
        if (*str == del && *(str+1) != del && !stringDetected)
            result++;
    }
    return result;
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

void append(char *str, char n) 
{
    u32 appendPoint = str_len(str);
    str[appendPoint] = n;
    str[appendPoint + 1] = '\0';
}