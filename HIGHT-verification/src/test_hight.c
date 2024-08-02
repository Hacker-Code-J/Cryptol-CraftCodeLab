#include <stdint.h>
#include "../include/hight.h"
#ifdef CRUCIBLE
#include <crucible.h>
#endif

#ifdef CRUCIBLE

int main() {
    uint8_t plaintext[8];
    uint8_t key[16];
    uint8_t ciphertext[8];
    uint8_t decrypted[8];

    // Initialize test variables using Crucible
    for (int i = 0; i < 8; ++i) {
        plaintext[i] = crucible_uint8_t("plaintext[i]");
    }
    for (int i = 0; i < 16; ++i) {
        key[i] = crucible_uint8_t("key[i]");
    }

    // Set assumptions for the test case
    for (int i = 0; i < 8; ++i) {
        assuming(plaintext[i] < 256);
    }
    for (int i = 0; i < 16; ++i) {
        assuming(key[i] < 256);
    }

    // Test the encryption function
    HIGHT_Encrypt(ciphertext, plaintext, key);

    // Ensure the ciphertext is different from the plaintext (basic check)
    int different = 0;
    for (int i = 0; i < 8; ++i) {
        different |= (ciphertext[i] != plaintext[i]);
    }
    check(different);

    // Test the decryption function
    HIGHT_Decrypt(decrypted, ciphertext, key);

    // Check if the decrypted text matches the original plaintext
    for (int i = 0; i < 8; ++i) {
        check(decrypted[i] == plaintext[i]);
    }

    return 0;
}

#else

int main(int argc, char **argv) {
    // Normal execution path for non-Crucible build
    return 0;
}

#endif