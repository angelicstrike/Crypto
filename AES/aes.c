#include <stdlib.h>
#include <stdio.h>
#include "aes.h"

bool 
AES_Subbytes
( uint8_t* input )
{

}


bool 
AES_ShiftRows
( uint8_t* input )
{

}


bool 
AES_MixColumns
( uint8_t* input )
{

}


bool 
AES_AddRoundKey
( uint8_t* input )
{

}

bool 
AES_KeySchedule
( uint8_t* key, uint8_t* round_key )
{

}

bool 
AES_Encrypt
( uint8_t* plaintext, uint8_t* key )
{
    AES_AddRoundKey(plaintext, key, 0);

    int i;
    for(i = 1; i < NUM_ROUNDS - 1; i++)
    {
        AES_Subbytes(plaintext);
        AES_ShiftRows(plaintext);
        AES_MixColumns(plaintext);
        AES_AddRoundKey(plaintext, key, i);
    }
    
    /* Last Round */
    AES_Subbytes(plaintext);
    AES_ShiftRows(plaintext);
    AES_AddRoundKey(plaintext, key, NUM_ROUNDS - 1);
}


bool
AES_Decrypt
( uint8_t* ciphertext, uint8_t* key )
{

}
