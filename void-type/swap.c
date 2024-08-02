#include <stdint.h>
#include <stdlib.h>

void swap(uint32_t *x, uint32_t *y) {
    uint32_t tmp = *x;
    *x = *y;
    *y = tmp;
}

void xor_swap(uint32_t *x, uint32_t *y) {
    *x ^= *y;
    *y ^= *x;
    *x ^= *y;
}

void swap_array(uint32_t *a, size_t i, size_t j) {
    swap(a+i, a+j);
}