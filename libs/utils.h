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

/* boolean recreation */
typedef u8 bool;
#define true (1)
#define false (0)
/* you know why... */
#define NULL (0)

/* stuff to get lsb and msb */
#define low16(addr) (u16)((addr) & 0xFFFF)
#define high16(addr) (u16)(((addr) >> 16) & 0xFFFF)

/* std lib functions remade */
u32 str_len(char *);
void mem_cpy(char *src, char *dest, u32 nbBytes);
void strReverse(char *);
void iToA(i32, char*);
void append(char *, char *);

#endif