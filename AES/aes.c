#include <stdlib.h>
#include <stdio.h>
#include "aes.h"

bool 
AES_Subbytes
( uint8_t** input )
{

}


bool 
AES_ShiftRows
( uint8_t** input )
{
    int row, elem, rot;
    uint8_t temp = 0x00;

    /* For every row in the state matrix*/
    for(row = 1; row < TEXT_MATRIX_SIZE; row++)
    {
        /* Number of times to rotate a row*/
        for(rot = 0; rot < 4-i; rot++)
        {
            /* For every element in a row*/
            temp = input[3][row];
            for(elem = TEXT_MATRIX_SIZE-1; elem > -1; elem--)
            {
                input[(elem-1)%TEXT_MATRIX_SIZE][row] = input[elem][row];
            }
            input[0][row] = temp;
        }
    }
}


bool 
AES_MixColumns
( uint8_t** input )
{

}


bool 
AES_AddRoundKey
( uint8_t** input )
{

}

/*
 * Main, top level encryption algorithm. Implements
 * the AES logic as per FIPS Document 197.
 */
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
