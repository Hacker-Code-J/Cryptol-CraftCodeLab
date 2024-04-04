#include <stdint.h>

void void_add(uint16_t a, uint16_t b, uint32_t *result) {
    *result = (uint32_t)a + (uint32_t)b;
}

// clang -O2 -emit-llvm -c arithmetic.c -o arithmetic.bc
