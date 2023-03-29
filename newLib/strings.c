#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

f64 powk(f64 base, i64 exp)
{
    if (exp < 0) return 1 / powk(base, -exp);
    else if (exp == 1) return base;
    else if (exp == 0) return 1;
    else return base * powk(base, exp-1);
}

u32 str_len(char *str)
{
    u32 result = 0;
    while(str[result] != '\0') {
        result++;
    }
    return result;
}

i8 str_cpy(string in, string out) 
{
    if (in == NULL || out == NULL)
        return -1;
    while (*in != '\0') {
        *out++ = *in++;
    }
    return 0;
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
    if (*str == '\0' || str == NULL)
        return 0;
    
    u32 result = 0;
    bool foundWordBefore = false;
    do {
        if (*str == del || *str == '\0') {
            result = foundWordBefore ? result+1 : result;
            foundWordBefore = false;
        } else {
            foundWordBefore = true;
        }
    } while(*str++ != '\0');
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


/*
 * Function: strSplit
 * -------------------
 * return an array containing the content of the string given,
 * with each word being detected as separated by the char del
 * 
 * toSplit: char *, the string that should be splitted
 * del: what is separating each word
 * wordNb: will be affected to the length of the result
 * 
 * returns: an array of strings, each words.
*/
string *strSplit(string toSplit, char del, u32 *wordNb)
{
    if (toSplit == NULL)
        return NULL;
    u32 splitLen, biggestWordLen;
    *wordNb = 0;
    strLenBiggestWordAndWordNb(toSplit, del, &splitLen, &biggestWordLen, wordNb);
    //printf("size: %d, biggest: %d, WordNb: %d\n", splitLen, biggestWordLen, wordNb);
    string *res = NULL;
    res = (string *) malloc(*wordNb * sizeof(string));
    u32 count, index, individualSize= 0;
    string buff = (string) malloc(biggestWordLen * sizeof(char));
    while (index <= splitLen && count < *wordNb) {
        if ((toSplit[index] == del && str_len(buff) != 0) || toSplit[index] == '\0') {
            res[count] = (string) malloc(individualSize * sizeof(char));
            if (res[count] == NULL)
                return NULL;
            str_cpy(buff, res[count]);
            //printf("Word %d, size %d, \'%s\'\n", count, individualSize, res[count]);
            count += 1;
            individualSize = 0;
            buff[0] = '\0';
        } else if(toSplit[index] != del) {
            individualSize++;
            append(buff, toSplit[index]);
        }
        index++;
    }
    free(buff);
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

int main() {
    string temp = "bonjour      je suis                 theodore     et  ";
    u32 wordNb;
    string *zouf = strSplit(temp, ' ', &wordNb);
    return 0;
}