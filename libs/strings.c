#include "strings.h"

u32 str_len(char *str)
{
    u32 result = 0;
    while(str[result] != '\0') {
        result++;
    }
    return result;
}