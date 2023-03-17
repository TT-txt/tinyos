#include "strings.h"

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

void append(char *str, char n) 
{
    u32 appendPoint = str_len(str);
    str[appendPoint] = n;
    str[appendPoint + 1] = '\0';
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

u32 biggestWord(char *str, char del)
{
    u32 biggest = 0;
    u32 temp = 0;
    while (*str++ != '\0') {
        if (*str == del) {
            if (temp > biggest)
                biggest = temp;
            temp = 0;
        } else {
            temp++;
        }
    }
    return biggest;
}

/* ⚠️ -- UNDER CONSTRUCTION -- ⚠️ */
char **str_split(char *str, char del)
{
    u32 memPos;
    char **result = (char **) malloc_t(sizeof(char *), 1, &memPos);
    u32 maxWordSize = biggestWord(str, del);
    u32 i = 0;
    char *temp = (char *) malloc_t(maxWordSize, 1, &memPos);
    while (*str++ != '\0') {
        if (*str == del) {
            result[i] = (char *) malloc_t((++i) * sizeof(char), 1, &memPos);
            mem_cpy(result[i-1], temp, i);
            i = 0;
            temp[0] = '\0';
            /* TODO: reset here temp */
        } else {
            temp[i++] = *str;
        }
    }
    return result;
}

void hex_to_ascii(int n, char *str) {
    append(str, '0');
    append(str, 'x');
    char zeros = 0;

    u32 tmp;
    int i;
    for (i = 28; i > 0; i -= 4) {
        tmp = (n >> i) & 0xF;
        if (tmp == 0 && zeros == 0) continue;
        zeros = 1;
        if (tmp > 0xA) append(str, tmp - 0xA + 'a');
        else append(str, tmp + '0');
    }

    tmp = n & 0xF;
    if (tmp >= 0xA) append(str, tmp - 0xA + 'a');
    else append(str, tmp + '0');
}