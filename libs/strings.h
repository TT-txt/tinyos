/**
 * @file strings.h
 * @author Théodore MARTIN
 * @brief functions header library to imitate strings.c from the stdlib
 * @version 0.1
 * @date 2023-03-22
 */

#ifndef __STRINGS__
#define __STRINGS__

#include "utils.h"
#include "memory.h"

/**
 * @brief computing the length of a string
 * 
 * @param[in] str the string we want the length of
 * 
 * @return u32 the string size 
 */
u32 str_len(char *);

/**
 * @brief compares 2 string
 * 
 * @param[in] str1 the first string
 * @param[in] str2 the second string
 * 
 * @return i8 0 if the strings are equals, else some magic int.
 */
i8 str_cmp(char *, char *);

/**
 * @brief reverses a string
 * 
 * @param[out] str the string that should and will be reversed
 * 
 * @return void
 */
void strReverse(char *);

/**
 * @brief adds the given char to the end of a string
 * 
 * @param[out] str the string where we should append the char
 * @param[in] chr the char that should be added
 * 
 * @return void
 */
void append(char *, char);

/**
 * @brief counts the number of word separated by a delimitor in a string
 * 
 * @param[in] str the string that should be parsed
 * @param[in] del the delimitor
 * 
 * @return u32 the word number
 */
u32 wordCount(char *, char);

/**
 * @brief Split a string in an array of substrings
 * 
 * @param[in] toSplit the string that should be splitted
 * @param[in] del the char separating each word
 * @param[out] wordNb the length of the returned array
 * 
 * @return string* an array containing the extracted substrings 
 */
string *strSplit(string, char, u32*);

/**
 * @brief converts a string to a float
 * 
 * @param[in] str the string containing the number
 * 
 * @return f64 the extracted float
 */
f64 strToL(char *);

/**
 * @brief converts a int to its hexadecimal value in a string
 * 
 * @param[in] n the number
 * @param[out] str where the result will be stored
 * 
 * @return void
 */
void hexToAscii(int ,char *);

#endif