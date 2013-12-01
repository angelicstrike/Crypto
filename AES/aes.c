#include <stdlib.h>
#include <stdio.h>
#include "aes.h"

/*
 * Makes call to GCD functions here to do conversion to field
 * equation from bits and back again.
 */
bool 
AES_Subbytes
( uint8_t input[TEXT_MATRIX_SIZE][TEXT_MATRIX_SIZE] )
{
    for(int i = 0; i < TEXT_MATRIX_SIZE; i++)
    {
        
    } 
    return true;
}


bool 
AES_ShiftRows
( uint8_t input[TEXT_MATRIX_SIZE][TEXT_MATRIX_SIZE] )
{
    int row, elem, rot;
    uint8_t temp = 0x00;

    /* For every row in the state matrix*/
    for(row = 1; row < TEXT_MATRIX_SIZE; row++)
    {
        /* Number of times to rotate a row*/
        for(rot = 0; rot < 4-row; rot++)
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
    return true;
}


bool 
AES_MixColumns
( uint8_t input[TEXT_MATRIX_SIZE][TEXT_MATRIX_SIZE] )
{

    return true;
}


bool 
AES_AddRoundKey
( uint8_t input[TEXT_MATRIX_SIZE][TEXT_MATRIX_SIZE], uint8_t keys[NUM_KEYS][TEXT_MATRIX_SIZE], uint32_t round)
{
    for(int i = 0; i < TEXT_MATRIX_SIZE; i++)
    {

    }

    return true;
}

bool
AES_ExpandKeys(uint8_t* mainKey, uint32_t roundKeys[NUM_KEYS][TEXT_MATRIX_SIZE])
{
    for(int i = 4; i <= 43; i++)
    {
        if(i % 4 == 0)
        {
            roundKeys[i][0] = ;
            roundKeys[i][1] = ;
            roundKeys[i][2] = ;
            roundKeys[i][3] = ;
        }
        else
        {
            for(int j = 0; j < 4; j++)
            {
                roundKeys[i][j] = roundKeys[i-1][j] ^ roundKeys[i-4][j];
            }
        } 
    }    

    return true;
}


static void 
construct_state_matrix
( uint8_t* text, uint8_t state_matrix[TEXT_MATRIX_SIZE][TEXT_MATRIX_SIZE] )
{
    for(int i = 0; i < TEXT_MATRIX_SIZE; i++)
    {
        for(int j = 0; j < TEXT_MATRIX_SIZE; j++)
        {
            state_matrix[i][j] = text[4*i + j];
        }
    }
}

/*
 * Main, top level encryption algorithm. Implements
 * the AES logic as per FIPS Document 197.
 */
bool 
AES_Encrypt
( uint8_t* plaintext, uint8_t* key )
{
    uint8_t roundKeys[NUM_KEYS][TEXT_MATRIX_SIZE];
    uint8_t state_matrix[TEXT_MATRIX_SIZE][TEXT_MATRIX_SIZE];

    construct_state_matrix(plaintext, state_matrix);

    AES_AddRoundKey(state_matrix, roundKeys, 0);

    int i;
    for(i = 1; i < NUM_ROUNDS - 1; i++)
    {
        AES_Subbytes(state_matrix);
        AES_ShiftRows(state_matrix);
        AES_MixColumns(state_matrix);
        AES_AddRoundKey(state_matrix, roundKeys, i);
    }
    
    /* Last Round */
    AES_Subbytes(state_matrix);
    AES_ShiftRows(state_matrix);
    AES_AddRoundKey(state_matrix, roundKeys, NUM_ROUNDS - 1);

    return true;
}


bool
AES_Decrypt
( uint8_t* ciphertext, uint8_t* key )
{

    return true;
}
