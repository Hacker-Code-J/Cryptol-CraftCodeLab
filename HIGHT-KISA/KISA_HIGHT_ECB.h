/***************************************************************************
 *
 * File : KISA_HIGHT_ECB.h
 *
 * Description : header file for KISA_HIGHT_ECB.c
 *
 **************************************************************************/

#ifndef _HIGHT_H_
#define _HIGHT_H_

/*************** Header files *********************************************/


/*************** Definitions **********************************************/

#define CT_LITTLE_ENDIAN

/*************** Constants ************************************************/

/*************** Macros ***************************************************/
////
#define ROTL_BYTE(x, n) ( (BYTE)((x) << (n)) | (DWORD)((x) >> (8-(n))) )
#define ROTR_BYTE(x, n) ( (BYTE)((x) >> (n)) | (DWORD)((x) << (8-(n))) )

#if defined(_MSC_VER)
    #define ROTL_DWORD(x, n) _lrotl((x), (n))
    #define ROTR_DWORD(x, n) _lrotr((x), (n))
#else
    #define ROTL_DWORD(x, n) ( (DWORD)((x) << (n)) | (DWORD)((x) >> (32-(n))) )
    #define ROTR_DWORD(x, n) ( (DWORD)((x) >> (n)) | (DWORD)((x) << (32-(n))) )
#endif

////    reverse the byte order of DWORD(DWORD:4-bytes integer).
#define ENDIAN_REVERSE_DWORD(dwS)   ( (ROTL_DWORD((dwS),  8) & 0x00ff00ff)  \
                                    | (ROTL_DWORD((dwS), 24) & 0xff00ff00) )

////
#if defined(CT_BIG_ENDIAN)      ////    Big-Endian machine
    #define BIG_B2D(B, D)       D = *(DWORD *)(B)
    #define BIG_D2B(D, B)       *(DWORD *)(B) = (DWORD)(D)
    #define LITTLE_B2D(B, D)    D = ENDIAN_REVERSE_DWORD(*(DWORD *)(B))
    #define LITTLE_D2B(D, B)    *(DWORD *)(B) = ENDIAN_REVERSE_DWORD(D)
#elif defined(CT_LITTLE_ENDIAN) ////    Little-Endian machine
    #define BIG_B2D(B, D)       D = ENDIAN_REVERSE_DWORD(*(DWORD *)(B))
    #define BIG_D2B(D, B)       *(DWORD *)(B) = ENDIAN_REVERSE_DWORD(D)
    #define LITTLE_B2D(B, D)    D = *(DWORD *)(B)
    #define LITTLE_D2B(D, B)    *(DWORD *)(B) = (DWORD)(D)
#else
    #error ERROR : Invalid DataChangeType
#endif

#if defined(_MSC_VER)
    #define INLINE  _inline
#else
    #define INLINE  inline
#endif

/*************** New Data Types *******************************************/
#define BYTE    unsigned char       //  1-byte data type
#define WORD    unsigned short int  //  2-byte data type
#define DWORD   unsigned int        //  4-byte data type
/*************** Prototypes ***********************************************/
void    HIGHT_KeySched(
            BYTE    *UserKey,       
            DWORD   UserKeyLen,     
            BYTE    *RoundKey);     
void    HIGHT_Encrypt(
            BYTE    *RoundKey,      
            BYTE    *Data);         
                                    
void    HIGHT_Decrypt(
            BYTE    *RoundKey,      
            BYTE    *Data);         
                                    


#endif  /* _HIGHT_H_ */