#include <stdio.h>
#include <stdint.h>

void side_effect(uint32_t* a) {
    *a = 0;
}

uint32_t foo(uint32_t x) {
    uint32_t b = x;
    side_effect(&b);
    return b;
}

int main(void) {
    // test
}