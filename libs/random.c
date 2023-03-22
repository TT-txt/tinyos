/**
 * @file random.c
 * @author Théodore MARTIN
 * @brief function library to get pseudo random numbers
 * @version 0.1
 * @date 2023-03-22 
 */
#include "random.h"

u8 rngTable[256] = {
	121, 137, 85, 187, 232, 188, 91, 133, 178, 93, 101, 208, 40, 162, 
	148, 84, 253, 62, 132, 19, 122, 246, 14, 240, 223, 115, 52, 159, 
	141, 30, 80, 254, 193, 114, 21, 213, 37, 249, 156, 29, 197, 237, 
	252, 63, 86, 73, 225, 39, 248, 120, 194, 128, 196, 131, 67, 34, 
	221, 60, 176, 220, 24, 192, 104, 113, 10, 157, 139, 81, 78, 23, 
	2, 174, 212, 224, 11, 108, 143, 79, 72, 218, 82, 69, 216, 111, 
	27, 76, 145, 44, 107, 83, 173, 105, 36, 219, 71, 177, 142, 230, 
	167, 242, 222, 119, 26, 239, 48, 180, 245, 25, 0, 33, 153, 140, 
	125, 170, 235, 147, 244, 169, 9, 151, 116, 59, 179, 127, 12, 250, 
	96, 228, 203, 241, 149, 4, 20, 247, 61, 163, 118, 58, 202, 226, 
	56, 171, 185, 199, 110, 22, 100, 68, 57, 152, 182, 158, 103, 189, 
	175, 165, 77, 47, 43, 3, 89, 38, 161, 35, 135, 64, 209, 55, 
	160, 99, 183, 31, 210, 211, 238, 217, 8, 92, 42, 201, 74, 1, 
	181, 155, 205, 66, 6, 200, 144, 243, 13, 215, 45, 186, 236, 94, 
	28, 184, 109, 102, 54, 126, 49, 17, 251, 138, 117, 136, 123, 65, 
	146, 150, 97, 5, 75, 41, 198, 154, 95, 229, 129, 16, 98, 195, 
	46, 15, 234, 32, 18, 227, 255, 88, 206, 190, 53, 70, 50, 166, 
	112, 164, 90, 51, 168, 207, 130, 87, 124, 7, 191, 106, 233, 214, 
	231, 172, 204, 134
};

int rngIndex = 0;

u8 randomK()
{
    rngIndex = (rngIndex+1)&0xFF;
    return rngTable[rngIndex];
}

f32 randK()
{
	rngIndex = (rngIndex+1)&0xFF;
	return rngTable[rngIndex] / 255;
}

void resetRandom() 
{
    rngIndex = 0;
}