/**
 * @file strings.c
 * @author Théodore MARTIN
 * @brief function library to imitate strings.c from the stdlib
 * @version 0.1
 * @date 2023-03-22
 */
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

u32 str_cpy(string in, string out) 
{
    if (in == NULL || out == NULL)
        return -1;
    while (*in != '\0') {
        *out++ = *in++;
    }
    return 0;
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
    char *result = (char *) mallok(size);
    /*copying it*/
    for (u32 i = startIndex; i < startIndex + size; ++i) {
        result[i - startIndex] = str[i];
    }
    return result;
}

static void strLenBiggestWordAndWordNb(char *str, char del, u32 *size, u32 *biggest, u32 *wordNb)
{
    u32 temp = 0;
    bool wordPreviouslyFound = false;
    *biggest = *size = *wordNb = 0;
    do {
        if (*str == del || *str == '\0') {
            if (temp > *biggest)
                *biggest = temp;
            if (wordPreviouslyFound) 
                *(wordNb) += 1;
            wordPreviouslyFound = false;
            temp = 0;
        } else {
            wordPreviouslyFound = true;
            temp++;
        }
        *(size) += 1;
    } while (*str++ != '\0');
}

string *strSplit(string toSplit, char del, u32 *wordNb)
{
    if (toSplit == NULL)
        return NULL;
    u32 splitLen, biggestWordLen;
    *wordNb = 0;
    strLenBiggestWordAndWordNb(toSplit, del, &splitLen, &biggestWordLen, wordNb);
    string *res = NULL;
    res = (string *) mallok(*wordNb * sizeof(string));
    u32 count, index, individualSize;
    count = index = individualSize = 0;
    string buff = (string) mallok(biggestWordLen * sizeof(char));
    while (index <= splitLen && count < *wordNb) {
        if ((toSplit[index] == del && str_len(buff) != 0) || toSplit[index] == '\0') {
            res[count] = (string) mallok(individualSize * sizeof(char));
            if (res[count] == NULL)
                return NULL;
            str_cpy(buff, res[count]);
            count += 1;
            individualSize = 0;
            buff[0] = '\0';
        } else if(toSplit[index] != del) {
            individualSize++;
            append(buff, toSplit[index]);
        }
        index++;
    }
    //freek(buff); //TODO: implement free
    return res;
}

static i32 charIndex(char *str, char searched)
{
    i32 res = 0;
    while(str[res] != searched && str[res] != '\0') {
        res++;
    }
    return str[res] == '\0' ? -1 : res;
}

f64 strToL(char *str)
{
    if (str == NULL || str[0] == '\0')
        return 0;
    f64 res = 0;
    bool neg = str[0] == '-';
    u32 index = neg ? 1 : 0;
    i32 wholePart = charIndex(str, '.');
    if (wholePart == -1) wholePart = str_len(str);
    while (str[index] != '\0') {
        if (str[index] == '.') {
            wholePart++;
        } else {
            
            res += (str[index] - 48) * powk(10, wholePart - 1 - index);
        }
        index++;
    }
    res = neg ? res * -1 : res;
    return res;
}

void hexToAscii(int n, char *str) {
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