#include <stdint.h>
#ifdef CRUCIBLE
#include <crucible.h>
#endif

// Declare a global variable for demonstration
volatile int8_t global_var = 0;

// Function that modifies a global variable
void modify_global(int8_t delta) {
    global_var += delta;
}

// Simple function to increment the input
int8_t f(int8_t x) {
    return x + 1;
}

#ifdef CRUCIBLE

int main() {
    // Introduce a test variable
    int8_t x = crucible_int8_t("x");
    // Set assumptions for the test case
    assuming(x < 100);
    // Check the result of the function 'f'
    check(f(x) < 101);
    
    // Test the void function by observing the effects on the global variable
    modify_global(x);
    check(global_var == x);  // Check if global_var has been modified correctly by 'modify_global'
    
    // Reset global_var for potential further tests or to ensure clean state
    global_var = 0;

    return 0;
}
#else

int main(int argc, char **argv) {
    return f(argc);
}
#endif