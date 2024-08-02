#ifndef HIGHT_H
#define HIGHT_H

#include <stdint.h>

typedef uint8_t u8;

void HIGHT_Encrypt(u8 dst[8], const u8 src[8], const u8 MK[16]);
void HIGHT_Decrypt(u8 dst[8], const u8 src[8], const u8 MK[16]);

#endif // HIGHT_H
