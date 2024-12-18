#include "hight.h"
#include "hight_utils.h"

void viewKeySchedule(u8* SK) {
    for (int i = 0; i < 32; i++) {
        printf("SK[%03d]||SK[%03d]||SK[%03d]||SK[%03d]: %02x%02x%02x%02x\n",
            4*i+3, 4*i+2, 4*i+1, 4*i, SK[4*i+3], SK[4*i+2], SK[4*i+1], SK[4*i]);
    }
}

int main(void) {
    u8 KISA_MK[16] = { 0x62, 0x00, 0x78, 0x00, 
                       0x73, 0xF1, 0x59, 0x53,
                       0xFE, 0x2F, 0x49, 0xFE, 
                       0x02, 0x4B, 0x00, 0xA4 };
    u8 KISA_WK[8] = { 0x00, };
    u8 KISA_SK[128] = { 0x00, };
    encKeySchedule(KISA_WK, KISA_SK, KISA_MK);
    // viewKeySchedule(KISA_SK);

    // const char* keyString = "00000000000000000000000000000000"; // Test Vector
    const char* keyString = "00112233445566778899aabbccddeeff"; // Test Vector 1
    // const char* keyString = "ffeeddccbbaa99887766554433221100"; // Test Vector 2
    // const char* keyString = "000102030405060708090a0b0c0d0e0f"; // Test Vector 3
    // const char* keyString = "28dbc3bc49ffd87dcfa509b11d422be7"; // Test Vector 4
    u8 MK[16] = { 0x00, };
    stringToByte(MK, keyString);

    const char* inputString = "0000000000000000"; // Test Vector 1
    // const char* inputString = "0011223344556677"; // Test Vector 2
    // const char* inputString = "0123456789abcdef"; // Test Vector 3
    // const char* inputString = "b41e6be2eba84a14"; // Test Vector 4
    
    u8 PT[8] = { 0x00, };
    stringToByte(PT, inputString);

    u8 WK[8] = { 0x00, };
    u8 SK[128] = { 0x00, };

    printf("MK | ");
    for (int i = 15; i >= 0; i--) {
        printf("%02X ", MK[i]);
    } puts("");
    printf("PT | ");
    for (int i = 7; i >= 0; i--) {
        printf("%02X ", PT[i]);
    } puts("");

    encKeySchedule(WK, SK, MK);
    printf("WK | ");
    for (int i = 7; i >= 0; i--) {
        printf("%02X:", WK[i]);
    } puts("");
    printf ("SK | \n");
	for (i32 i=0;i<128;i++)	{
        if ((i != 0) && (i % 8 == 0)) puts("");
        printf("%02X ", SK[i]);
    } puts("");

    u8 CT[8] = { 0x00, };
    u8 DT[8] = { 0x00, };
    HIGHT_Encrypt(CT, PT, MK);
    HIGHT_Decrypt(DT, CT, MK);
#if 0
    // printf("PT | ");
    // for (int i = 7; i >= 0; i--) {
    //     printf("%02x:", PT[i]);
    // } puts("");
    printf("CT | ");
    for (int i = 7; i >= 0; i--) {
        printf("%02X ", CT[i]);
    } puts("");
    printf("DT | ");
    for (int i = 7; i >= 0; i--) {
        printf("%02X ", DT[i]);
    } puts("");
#endif
#if 0
    printf("PT | ");
    for (int i = 0; i < 8; i++) {
        printf("%02x:", PT[i]);
    } puts("");
    printf("CT | ");
    for (int i = 0; i < 8; i++) {
        printf("%02x:", CT[i]);
    } puts("");
    printf("DT | ");
    for (int i = 0; i < 8; i++) {
        printf("%02x:", myPT[i]);
    } puts("");
#endif
    return 0;
}