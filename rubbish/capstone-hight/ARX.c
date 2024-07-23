#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t u8;

u8 add_standard(u8 a, u8 b) {
  return a + b;
}

u8 rot_standard(u8 a, u8 b) {
  return (a >> b) | (a << (8-b));
}

u8 xor_standard(u8 a, u8 b) {
  return a ^ b;
}

int main() {
  printf("Main Function\n");
  return 0;
}

// u8 ROTL(u8 byte, u8 shift) {
//     return (byte << shift) | (byte >> (8 - shift));
// }