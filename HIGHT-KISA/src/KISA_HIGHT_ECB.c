/***************************************************************************
 *
 * Created July, 2005
 * Modified Dec, 2013
 * File : KISA_HIGHT_ECB.c
 *
 * Description : Core routines for the enhanced HIGHT
 *
 **************************************************************************/

/*************** Header files *********************************************/
#include "../include/KISA_HIGHT_ECB.h"

/*************** Macros ***************************************************/

/*************** Function *************************************************/

void    HIGHT_KeySched(
            BYTE    *UserKey,       
            DWORD   UserKeyLen,     
            BYTE    *RoundKey)      
{
    int     i, j;

    for( i=0; i<4; i++) {
        RoundKey[i  ] = UserKey[i+12];
        RoundKey[i+4] = UserKey[i   ];
    }

    for( i=0; i<8; i++) {
        for( j=0; j<8; j++)
            RoundKey[8+16*i+j  ] = (BYTE) (UserKey[(j-i)&7    ] + Delta[16*i+j  ]);	
// Use "&7"  instead of the "%8" for Performance

        for( j=0; j<8; j++)
            RoundKey[8+16*i+j+8] = (BYTE) (UserKey[((j-i)&7)+8] + Delta[16*i+j+8]);
    }
}

/*************** Encryption*************************************************/

void    HIGHT_Encrypt(
            BYTE    *RoundKey,      
            BYTE    *Data)
{
    DWORD   XX[8];

    // First Round
    XX[1] = Data[1];
    XX[3] = Data[3];
    XX[5] = Data[5];
    XX[7] = Data[7];

    XX[0] = (Data[0] + RoundKey[0]) & 0xFF;
    XX[2] = (Data[2] ^ RoundKey[1]);
    XX[4] = (Data[4] + RoundKey[2]) & 0xFF;
    XX[6] = (Data[6] ^ RoundKey[3]);

    // Encryption Round 
    #define HIGHT_ENC(k, i0,i1,i2,i3,i4,i5,i6,i7) {                         \
        XX[i0] = (XX[i0] ^ (HIGHT_F0[XX[i1]] + RoundKey[4*k+3])) & 0xFF;    \
        XX[i2] = (XX[i2] + (HIGHT_F1[XX[i3]] ^ RoundKey[4*k+2])) & 0xFF;    \
        XX[i4] = (XX[i4] ^ (HIGHT_F0[XX[i5]] + RoundKey[4*k+1])) & 0xFF;    \
        XX[i6] = (XX[i6] + (HIGHT_F1[XX[i7]] ^ RoundKey[4*k+0])) & 0xFF;    \
    }

	HIGHT_ENC( 2,  7,6,5,4,3,2,1,0);
    HIGHT_ENC( 3,  6,5,4,3,2,1,0,7);
    HIGHT_ENC( 4,  5,4,3,2,1,0,7,6);
    HIGHT_ENC( 5,  4,3,2,1,0,7,6,5);
    HIGHT_ENC( 6,  3,2,1,0,7,6,5,4);
    HIGHT_ENC( 7,  2,1,0,7,6,5,4,3);
    HIGHT_ENC( 8,  1,0,7,6,5,4,3,2);
    HIGHT_ENC( 9,  0,7,6,5,4,3,2,1);
    HIGHT_ENC(10,  7,6,5,4,3,2,1,0);
    HIGHT_ENC(11,  6,5,4,3,2,1,0,7);
    HIGHT_ENC(12,  5,4,3,2,1,0,7,6);
    HIGHT_ENC(13,  4,3,2,1,0,7,6,5);
    HIGHT_ENC(14,  3,2,1,0,7,6,5,4);
    HIGHT_ENC(15,  2,1,0,7,6,5,4,3);
    HIGHT_ENC(16,  1,0,7,6,5,4,3,2);
    HIGHT_ENC(17,  0,7,6,5,4,3,2,1);
    HIGHT_ENC(18,  7,6,5,4,3,2,1,0);
    HIGHT_ENC(19,  6,5,4,3,2,1,0,7);
    HIGHT_ENC(20,  5,4,3,2,1,0,7,6);
    HIGHT_ENC(21,  4,3,2,1,0,7,6,5);
    HIGHT_ENC(22,  3,2,1,0,7,6,5,4);
    HIGHT_ENC(23,  2,1,0,7,6,5,4,3);
    HIGHT_ENC(24,  1,0,7,6,5,4,3,2);
    HIGHT_ENC(25,  0,7,6,5,4,3,2,1);
    HIGHT_ENC(26,  7,6,5,4,3,2,1,0);
    HIGHT_ENC(27,  6,5,4,3,2,1,0,7);
    HIGHT_ENC(28,  5,4,3,2,1,0,7,6);
    HIGHT_ENC(29,  4,3,2,1,0,7,6,5);
    HIGHT_ENC(30,  3,2,1,0,7,6,5,4);
    HIGHT_ENC(31,  2,1,0,7,6,5,4,3);
    HIGHT_ENC(32,  1,0,7,6,5,4,3,2);
    HIGHT_ENC(33,  0,7,6,5,4,3,2,1);

    // Final Round
    Data[1] = (BYTE) XX[2];
    Data[3] = (BYTE) XX[4];
    Data[5] = (BYTE) XX[6];
    Data[7] = (BYTE) XX[0];

    Data[0] = (BYTE) (XX[1] + RoundKey[4]);
    Data[2] = (BYTE) (XX[3] ^ RoundKey[5]);
    Data[4] = (BYTE) (XX[5] + RoundKey[6]);
    Data[6] = (BYTE) (XX[7] ^ RoundKey[7]);
}

/***************Decryption *************************************************/

// Same as encrypt, except that round keys are applied in reverse order

void    HIGHT_Decrypt(
            BYTE    *RoundKey,     
            BYTE    *Data)          
{
    DWORD   XX[8];

    XX[2] = (BYTE) Data[1];
    XX[4] = (BYTE) Data[3];
    XX[6] = (BYTE) Data[5];
    XX[0] = (BYTE) Data[7];

    XX[1] = (BYTE) (Data[0] - RoundKey[4]);
    XX[3] = (BYTE) (Data[2] ^ RoundKey[5]);
    XX[5] = (BYTE) (Data[4] - RoundKey[6]);
    XX[7] = (BYTE) (Data[6] ^ RoundKey[7]);

    #define HIGHT_DEC(k, i0,i1,i2,i3,i4,i5,i6,i7) {                         \
        XX[i1] = (XX[i1] - (HIGHT_F1[XX[i2]] ^ RoundKey[4*k+2])) & 0xFF;    \
        XX[i3] = (XX[i3] ^ (HIGHT_F0[XX[i4]] + RoundKey[4*k+1])) & 0xFF;    \
        XX[i5] = (XX[i5] - (HIGHT_F1[XX[i6]] ^ RoundKey[4*k+0])) & 0xFF;    \
        XX[i7] = (XX[i7] ^ (HIGHT_F0[XX[i0]] + RoundKey[4*k+3])) & 0xFF;    \
    }
    
    HIGHT_DEC(33,  7,6,5,4,3,2,1,0);
    HIGHT_DEC(32,  0,7,6,5,4,3,2,1);
    HIGHT_DEC(31,  1,0,7,6,5,4,3,2);
    HIGHT_DEC(30,  2,1,0,7,6,5,4,3);
    HIGHT_DEC(29,  3,2,1,0,7,6,5,4);
    HIGHT_DEC(28,  4,3,2,1,0,7,6,5);
    HIGHT_DEC(27,  5,4,3,2,1,0,7,6);
    HIGHT_DEC(26,  6,5,4,3,2,1,0,7);
    HIGHT_DEC(25,  7,6,5,4,3,2,1,0);
    HIGHT_DEC(24,  0,7,6,5,4,3,2,1);
    HIGHT_DEC(23,  1,0,7,6,5,4,3,2);
    HIGHT_DEC(22,  2,1,0,7,6,5,4,3);
    HIGHT_DEC(21,  3,2,1,0,7,6,5,4);
    HIGHT_DEC(20,  4,3,2,1,0,7,6,5);
    HIGHT_DEC(19,  5,4,3,2,1,0,7,6);
    HIGHT_DEC(18,  6,5,4,3,2,1,0,7);
    HIGHT_DEC(17,  7,6,5,4,3,2,1,0);
    HIGHT_DEC(16,  0,7,6,5,4,3,2,1);
    HIGHT_DEC(15,  1,0,7,6,5,4,3,2);
    HIGHT_DEC(14,  2,1,0,7,6,5,4,3);
    HIGHT_DEC(13,  3,2,1,0,7,6,5,4);
    HIGHT_DEC(12,  4,3,2,1,0,7,6,5);
    HIGHT_DEC(11,  5,4,3,2,1,0,7,6);
    HIGHT_DEC(10,  6,5,4,3,2,1,0,7);
    HIGHT_DEC( 9,  7,6,5,4,3,2,1,0);
    HIGHT_DEC( 8,  0,7,6,5,4,3,2,1);
    HIGHT_DEC( 7,  1,0,7,6,5,4,3,2);
    HIGHT_DEC( 6,  2,1,0,7,6,5,4,3);
    HIGHT_DEC( 5,  3,2,1,0,7,6,5,4);
    HIGHT_DEC( 4,  4,3,2,1,0,7,6,5);
    HIGHT_DEC( 3,  5,4,3,2,1,0,7,6);
    HIGHT_DEC( 2,  6,5,4,3,2,1,0,7);

    Data[1] = (BYTE) (XX[1]);
    Data[3] = (BYTE) (XX[3]);
    Data[5] = (BYTE) (XX[5]);
    Data[7] = (BYTE) (XX[7]);

    Data[0] = (BYTE) (XX[0] - RoundKey[0]);
    Data[2] = (BYTE) (XX[2] ^ RoundKey[1]);
    Data[4] = (BYTE) (XX[4] - RoundKey[2]);
    Data[6] = (BYTE) (XX[6] ^ RoundKey[3]);
}

/*************** END OF FILE **********************************************/