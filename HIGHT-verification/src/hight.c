#include "hight.h"
#include <string.h>

// Simple XOR-based implementations for illustration
void HIGHT_Encrypt(u8 dst[8], const u8 src[8], const u8 MK[16]) {
    for (int i = 0; i < 8; ++i) {
        dst[i] = src[i] ^ MK[i % 16];
    }
}

void HIGHT_Decrypt(u8 dst[8], const u8 src[8], const u8 MK[16]) {
    for (int i = 0; i < 8; ++i) {
        dst[i] = src[i] ^ MK[i % 16];
    }
}