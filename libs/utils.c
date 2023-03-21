#include "utils.h"

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

f64 powk(f64 base, i64 exp)
{
    if (exp < 0) return 1 / powk(base, -exp);
    else if (exp == 1) return base;
    else if (exp == 0) return 1;
    else return base * powk(base, exp-1);
}