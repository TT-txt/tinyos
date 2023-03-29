#ifndef __UTILS__
#define __UTILS__

/* stdint definitions */
typedef unsigned char u8;/* max: FF*/
typedef unsigned short u16;/* max: FFFF*/
typedef unsigned int u32;/*max FFFF FFFF*/
typedef unsigned long long u64;/*max FFFF FFFF FFFF FFFF*/
typedef char i8;
typedef short i16;
typedef int i32;
typedef long long i64;
typedef u32 size_t;
typedef u32 uintptr_t;
typedef float f32;
typedef double f64;
/*string imitation*/
typedef char* string;

/* boolean recreation */
typedef u8 bool;
#define true (1)
#define false (0)
/* you know why... */
#define NULL (0)

/**
 * @brief function to get the 16 lowest bits of a word
 * 
 * @param[in] addr the value that should be retrieved
 * 
 * @return u16 the lowest 16 bits
 */
#define low16(addr) (u16)((addr) & 0xFFFF)

/**
 * @brief function to get the 16 highest bits of a word
 * 
 * @param[in] addr the value that should be retrieved
 * 
 * @return u16 the highest 16 bits
 */
#define high16(addr) (u16)(((addr) >> 16) & 0xFFFF)

/**
 * @brief function converting an int to a string
 * 
 * @param[in] n the value that should be stringified
 * @param[out] str the char* that will contain the result
 * 
 * @return void
 */
void iToA(i32, char*);

/**
 * @brief computes the value of the power of a number
 * 
 * @param[in] base the number that will be elevated
 * @param[in] exp the exponent. It must be integer.
 * 
 * @return f64 the result of the power
 */
f64 powk(f64, i64);

#endif