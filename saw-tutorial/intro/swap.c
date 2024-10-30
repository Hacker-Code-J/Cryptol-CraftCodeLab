#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

void swap(uint32_t *x, uint32_t *y) {
    uint32_t tmp = *x;
    *x = *y;
    *y = tmp;
}

bool swap_spec(uint32_t a, uint32_t b) {
    uint32_t x = a, y = b;
    swap(&x, &y);
    return x == b && y == a;
}

void xor_swap(uint32_t *x, uint32_t *y) {
    *x ^= *y;
    *y ^= *x;
    *x ^= *y;
}

bool xor_swap_spec(uint32_t a, uint32_t b) {
    uint32_t a1 = a, a2 = a;
    uint32_t b1 = b, b2 = b;
    xor_swap(&a1, &b1);
    swap(&a2, &b2);
    return a1 == a2 && b1 == b2;
}


bool general_swap_spec(void (*fun)(uint32_t *, uint32_t *), uint32_t a, uint32_t b) {
    uint32_t x = a, y = b;
    (*fun)(&x, &y);
    return x == b && y == a;
}

void swap_broken1(uint32_t *x, uint32_t *y) {
    uint32_t tmp = *x;
    *x = tmp;
    *y = *y;
}

bool swap_broken1_spec(uint32_t a, uint32_t b) {
    uint32_t x = a, y = b;
    swap_broken1(&x, &y);
    return x == b && y == a;
}


void swap_broken2(uint32_t *x, uint32_t *y) {
    uint32_t tmp = *x;
    if (*x != 4142351) {
        *x = *y;
        *y = tmp;
    }
}

bool swap_broken2_spec(uint32_t a, uint32_t b) {
    uint32_t x = a, y = b;
    swap_broken2(&x, &y);
    return x == b && y == a;
}


void swap_broken3(uint32_t *x, uint32_t *y) {
    uint32_t tmp = *x;
    if (*x && *x == (*y << 5)) {
        y = NULL;
    }
    *x = *y;
    *y = tmp;
}

bool swap_broken3_spec(uint32_t a, uint32_t b) {
    uint32_t x = a, y = b;
    swap_broken3(&x, &y);
    return x == b && y == a;
}



void test_swap_function(void (*fun)(uint32_t *, uint32_t *), char *descr, uint32_t x, uint32_t y) {
    printf("[%s] Testing with %u and %u... ", descr, x, y);
    if (general_swap_spec(fun, x, y)) {
        printf("OK\n");
    } else {
        printf("FAILED\n");
    }
}

void test_swap(char *descr, uint32_t x, uint32_t y) {
    test_swap_function(&swap, descr, x, y);
}

void chosen_value_test(void (*fun)(uint32_t *, uint32_t *)) {
    test_swap_function(fun, "Chosen", 1, 2);
    test_swap_function(fun, "Chosen", 2429, 98423);
    test_swap_function(fun, "Chosen", 8347853, 0);
    test_swap_function(fun, "Chosen", 5, 5);
    // ...
}

void random_value_test(void (*fun)(uint32_t *, uint32_t *)) {
    srand(time(NULL));

    for (int i = 0; i < 100; i ++) {
        test_swap_function(fun, "Random", rand(), rand());
    }
}

int main() {
    printf("Beginning chosen-value tests for swap\n");
    chosen_value_test(&swap);
    printf("\n");
    printf("Ending chosen-value tests for swap\n");

    printf("Beginning random tests for swap\n");
    random_value_test(&swap);
    printf("Ending random tests for swap\n");


}
