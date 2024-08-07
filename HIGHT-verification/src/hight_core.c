#include "hight.h"

/* Generate Encryption Key and Encryption Function */

void encKeySchedule(u8 enc_WK[8], 
                    u8 enc_SK[128],
                    const u8 MK[16]) {
    i32 i, j;
    
    // Generate whitening keys
    enc_WK[0] = MK[12];
    enc_WK[1] = MK[13];
    enc_WK[2] = MK[14];
    enc_WK[3] = MK[15];
    enc_WK[4] = MK[0];
    enc_WK[5] = MK[1];
    enc_WK[6] = MK[2];
    enc_WK[7] = MK[3];

    // Generate subkeys
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            enc_SK[16 * i + j + 0] = MK[((j - i) & 7) + 0] + delta_table[16 * i + j + 0];
            // printf("SK[%d] = MK[%d] + delta_table[%d]\n", 16 * i + j + 0, ((j - i) & 7) + 0, 16 * i + j + 0);
        }
        for (j = 0; j < 8; j++) {
            enc_SK[16 * i + j + 8] = MK[((j - i) & 7) + 8] + delta_table[16 * i + j + 8];
            // printf("SK[%d] = MK[%d] + delta_table[%d]\n", 16 * i + j + 8, ((j - i) & 7) + 8, 16 * i + j + 8);
        }
    }
    // printf("Key Scheduling ...\n");
}

void HIGHT_Encrypt(u8 dst[8], const u8 src[8], const u8 MK[16]) {


    // printf("MK | ");
    // for (int i = 0; i < 16; i++) {
    //     printf("%02x:", MK[i]);
    // } puts("");

    u8 WK[8];
    u8 SK[128];
    encKeySchedule(WK, SK, MK);

    // printf("WK | ");
    // for (int i = 0; i < 8; i++) {
    //     printf("%02x:", WK[i]);
    // } puts("");
    // printf("SK | ");
    // for (int i = 0; i < 128; i++) {
    //     if (i % 8 == 0) puts("");
    //     printf("%02x:", SK[i]);
    // } puts("");

    u8 state[8];
    memcpy(state, src, 8);
    
    state[0] += WK[0];
    state[2] ^= WK[1];
    state[4] += WK[2];
    state[6] ^= WK[3];
    
    // printf("state  | ");
    // for (u8 i = 0; i < 8; i++)
    //     printf("%02x:", state[i]);
    // puts("");
    for (u8 i = 0; i < 31; i++) {
        // printf("state%d | ", i);

        u8 t0 = state[7], t1 = state[6];
        state[7] = state[6];
        state[6] = state[5] + (F1(state[4]) ^ SK[i * 4 + 2]);
        state[5] = state[4];
        state[4] = state[3] ^ (F0(state[2]) + SK[i * 4 + 1]);
        state[3] = state[2];
        state[2] = state[1] + (F1(state[0]) ^ SK[i * 4 + 0]);
        state[1] = state[0];
        state[0] = t0       ^ (F0(t1      ) + SK[i * 4 + 3]);

        // for (u8 i = 0; i < 8; i++)
        //     printf("%02x:", state[i]);
        // puts("");
    }

    state[1] += (F1(state[0]) ^ SK[124]);
    state[3] ^= (F0(state[2]) + SK[125]);
    state[5] += (F1(state[4]) ^ SK[126]);
    state[7] ^= (F0(state[6]) + SK[127]);

    state[0] += WK[4];
    state[2] ^= WK[5];
    state[4] += WK[6];
    state[6] ^= WK[7];

    memcpy(dst, state, 8);
}

/* Generate Decryption Key and Decryption Function */

void decKeySchedule(u8 dec_WK[8], u8 dec_SK[128], const u8 MK[16]) {
    i32 i, j;
    
    // Generate whitening keys using direct assignments instead of loop
    dec_WK[0] = MK[12];
    dec_WK[1] = MK[13];
    dec_WK[2] = MK[14];
    dec_WK[3] = MK[15];
    dec_WK[4] = MK[0];
    dec_WK[5] = MK[1];
    dec_WK[6] = MK[2];
    dec_WK[7] = MK[3];

    // u8 delta[128] = { 0x00, };
    // u8 state = 0b01011010; // 0x5a

    // delta[0] = state;
    
    // // Generate δ array and subkeys without s array
    // for (i = 1; i < 128; i++) {
    //     u8 new_bit = ((delta[i-1] >> 3) & 0x01) ^ (delta[i-1] & 0x01);
    //     state = (u8)(new_bit << 7) | (u8)(delta[i-1] & 0x7F);
    //     state >>= 1;

    //     // Assign the new value to delta[i] using the updated state
    //     delta[i] = state & 0x7F;
    // }

    for (i = 7; i >= 0; i--) {
        for (j = 7; j >= 0; j--)
            dec_SK[127 - (16 * i + j + 8)] = MK[((j - i) & 7) + 8] + delta_table[16 * i + j + 8];
        for (j = 7; j >= 0; j--)
            dec_SK[127 - (16 * i + j + 0)] = MK[((j - i) & 7) + 0] + delta_table[16 * i + j + 0];
    }
}

void HIGHT_Decrypt(u8 dst[8], const u8 src[8], const u8 MK[16]) {
    u8 WK[8] = {
        MK[12], MK[13], MK[14], MK[15],
        MK[ 0], MK[ 1], MK[ 2], MK[ 3]
    };
    
    u8 SK[128];
    // decKeySchedule(WK, SK, MK);

    // WK[0] = MK[12];
    // WK[1] = MK[13];
    // WK[2] = MK[14];
    // WK[3] = MK[15];
    // WK[4] = MK[0];
    // WK[5] = MK[1];
    // WK[6] = MK[2];
    // WK[7] = MK[3];

    // u8 delta[128] = { 0x00, };
    // u8 rCon = 0x5a;

    // delta[0] = rCon;
    
    // // Generate δ array and subkeys without s array
    // for (u8 i = 1; i < 128; i++) {
    //     u8 new_bit = ((delta[i-1] >> 3) & 0x01) ^ (delta[i-1] & 0x01);
    //     rCon = (u8)(new_bit << 7) | (u8)(delta[i-1] & 0x7F);
    //     rCon >>= 1;

    //     // Assign the new value to delta[i] using the updated state
    //     delta[i] = rCon & 0x7F;
    // }

    for (i8 i = 7; i >= 0; i--) {
        for (i8 j = 7; j >= 0; j--)
            SK[127 - (16 * i + j + 8)] = MK[((j - i) & 7) + 8] + delta_table[16 * i + j + 8];
        for (i8 j = 7; j >= 0; j--)
            SK[127 - (16 * i + j + 0)] = MK[((j - i) & 7) + 0] + delta_table[16 * i + j + 0];
    }

    u8 state[8] = { 0x00, };
    memcpy(state, src, 8);
    state[0] -= WK[4];
    state[2] ^= WK[5];
    state[4] -= WK[6];
    state[6] ^= WK[7];

    state[1] -= (F1(state[0]) ^ SK[3]); // SK[127- 124]
    state[3] ^= (F0(state[2]) + SK[2]); // SK[127- 125]
    state[5] -= (F1(state[4]) ^ SK[1]); // SK[127- 126]
    state[7] ^= (F0(state[6]) + SK[0]); // SK[127- 127]

    for (i8 i = 1; i < 32; i++) {
        u8 temp0 = state[0];
        u8 temp2 = state[2];
        u8 temp4 = state[4];
        u8 temp6 = state[6];

        state[0] = state[1];
        state[2] = state[3];
        state[4] = state[5];
        state[6] = state[7];

        state[7] = temp0 ^ (F0(state[7]) + SK[i * 4 + 0]);
        state[5] = temp6 - (F1(state[5]) ^ SK[i * 4 + 1]);
        state[3] = temp4 ^ (F0(state[3]) + SK[i * 4 + 2]);
        state[1] = temp2 - (F1(state[1]) ^ SK[i * 4 + 3]);
    }

    state[0] -= WK[0];
    state[2] ^= WK[1];
    state[4] -= WK[2];
    state[6] ^= WK[3];
    
    memcpy(dst, state, 8);
}