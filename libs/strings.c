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

char *getNthWord(char *str, char del, u32 pos) {
    u32 startIndex = 0;
    u32 wordNb = 0;
    u32 size = 0;
    /*first, we're retrieving the starting index of the wanted word*/
    while (wordNb < pos && *(str+startIndex) != '\0') {
        if (*(str+startIndex) == del) {
            wordNb+=1;
        }
        startIndex+=1;
    }
    /*then, we retrieve the size of the said word*/
    while (*(str+startIndex+size) != del && *(str+startIndex+size) != '\0') {
        size+=1;
    }
    /*allocating memory to save the word*/
    u32 temp;
    printStr("Before malloc");
    char *result = (char *) malloc_t(size, 1, &temp);
    printStr("after");
    /*copying it*/
    for (u32 i = startIndex; i < startIndex + size; ++i) {
        result[i - startIndex] = str[i];
    }
    return result;
}

/* ⚠️ -- UNDER CONSTRUCTION -- ⚠️ */
/*
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
        } else {
            temp[i++] = *str;
        }
    }
    return result;
}*/