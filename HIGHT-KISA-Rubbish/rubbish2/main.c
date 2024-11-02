#include "KISA_HIGHT_ECB.h"

#include <stdio.h>

int main(void)
{
	BYTE pdwRoundKey[136] = {0,};																									// Round keys for encryption or decryption
	// BYTE pbUserKey[16] = { 0x00, };
    BYTE pbUserKey[16] = {0x88, 0xE3, 0x4F, 0x8F, 0x08, 0x17, 0x79, 0xF1, 0xE9, 0xF3, 0x94, 0x37, 0x0A, 0xD4, 0x05, 0x89 }; 		// User secret key
	// BYTE pbData[8] = { 0x00, };
    BYTE pbData[8]    = {0xD7, 0x6D, 0x0D,0x18, 0x32, 0x7E, 0xC5, 0x62}; 															// input plaintext to be encrypted

	int i;

// Print user secret key
	printf ("Key        : ");
	for (i=0;i<16;i++)	
		printf("%02X ",pbUserKey[i]);

// Print plaintext to be encrypted
	printf ("\nPlaintext  : ");
	for (i=0;i<8;i++)	
		printf("%02X ",pbData[i]);
		
// Derive roundkeys from user secret key
	HIGHT_KeySched( pbUserKey, 16, pdwRoundKey );
// Encryption
	printf ("\n\nEncryption....\n");
	HIGHT_Encrypt( pdwRoundKey, pbData );

// print encrypted data(ciphertext)
	printf ("Ciphertext : ");
	for (i=0;i<8;i++)	
		printf("%02X ",pbData[i]);
	
// // Decryption
// 	printf ("\n\nDecryption....\n");
// 	HIGHT_Decrypt( pdwRoundKey, pbData );
	
// // Print decrypted data(plaintext)
// 	printf ("Plaintext  : ");
// 	for (i=0;i<8;i++)	
// 		printf("%02X ",pbData[i]);
	
// // Print round keys at round i
// 	printf ("\n\nRound Key  : \n");
// 	for (i=0;i<16;i++) {
// 		printf("K%2d,0 : %08X\t", i+1, pdwRoundKey[2*i]);
// 		printf("K%2d,1 : %08X\n", i+1, pdwRoundKey[2*i+1]);
// 	}
    // puts("");
    return 0;
}
