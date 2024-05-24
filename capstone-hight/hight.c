#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t u8;

u8 add_standard(u8 a, u8 b) {
  return a + b;
}

u8* genWK(u8* MK) {
  u8* WK;
  *(WK + 0) = *(MK + 12);
  *(WK + 1) = *(MK + 13);
  *(WK + 2) = *(MK + 14);
  *(WK + 3) = *(MK + 15);
  *(WK + 4) = *(MK +  0);
  *(WK + 5) = *(MK +  1);
  *(WK + 6) = *(MK +  2);
  *(WK + 7) = *(MK +  3);
    return WK;
}

int main() {
    u8 MK[16] = {
      0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
      0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F
    };

    u8* WK = genWK(MK);

    for (int i = 0; i < 16; i++)
      printf("0x%2x:", MK[i]);


    for (int i = 0; i < 8; i++)
      printf("0x%2x:", WK[i]);


    return 0;
}