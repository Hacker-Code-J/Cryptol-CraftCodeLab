#include <stdint.h>
#include <stdio.h>
#ifdef CRUCIBLE
#include <crucible.h>
#endif

void update_value(uint8_t *a, uint8_t b, uint8_t c) {
  *a = (*a + b) ^ c;
}

#ifdef CRUCIBLE

int main() {
  uint8_t *a = crucible_alloc_uint8_t();
  uint8_t b = crucible_uint8_t("b");
  uint8_t c = crucible_uint8_t("c");
  uint8_t original_a = *a;

  update_value(a, b, c);

  // Debug prints
  printf("original_a: %u, b: %u, c: %u, updated a: %u\n", original_a, b, c, *a);

  // Verification check
  check(*a == ((original_a + b) ^ c));

  return 0;
}

#else

int main(int argc, char **argv) {
  uint8_t a = 1, b = 2, c = 3;
  update_value(&a, b, c);
  return 0;
}

#endif
