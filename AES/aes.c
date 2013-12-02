#include "aes.h"

/*
 *  From a byte, returns the in the "postion"
 *  offset from 0. (so the first bit is the 0th bit,
 *  and the last, most significant bit is the 7th bit)
 *
 *  The returned value is always in the least significant place.
 *  So if you ask for the 7th bit, the value at the 7th location 
 *  in the given byte will be returned in the 0th place in the
 *  return value.
 */
uint8_t
get_bit
( uint8_t byte, uint8_t position )
{
    uint8_t ret_val = 0;
    return ret_val;
}
/*
 * Makes call to GCD functions here to do conversion to field
 * equation from bits and back again.
 */
bool 
AES_Subbytes
( uint8_t input[TEXT_MATRIX_SIZE][TEXT_MATRIX_SIZE] )
{
    int32_t a[EQN_LEN];
    int32_t field_eqn[EQN_LEN];
    gcd_byte_to_field(FIELD_BYTE, field_eqn);
    for(int i = 0; i < TEXT_MATRIX_SIZE; i++)
    {
        for(int j = 0; j < TEXT_MATRIX_SIZE; j++)
        {
            gcd_byte_to_field(input[i][j], a);
            //gcd_find_inverse();
        }
    } 

    for(int i = 0; i < TEXT_MATRIX_SIZE; i++)
    {
        for(int j = 0; j < TEXT_MATRIX_SIZE; j++)
        {
            for(int k = 0; k < 8; k++)
            {
                //short byte = (input[i][j] & (1 << k)) >> k;
            }            
        }
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
        for(rot = 0; rot < row; rot++)
        {
            /* For every element in a row*/
            temp = input[0][row];
            for(elem = 1; elem < TEXT_MATRIX_SIZE; elem++)
            {
                input[(elem-1)][row] = input[elem][row];
            }
            input[3][row] = temp;
        }
    }
    return true;
}


bool 
AES_MixColumns
( uint8_t input[TEXT_MATRIX_SIZE][TEXT_MATRIX_SIZE] )
{
    const uint8_t M[TEXT_MATRIX_SIZE][TEXT_MATRIX_SIZE] =
    {
        {0x02, 0x03, 0x01, 0x01},
        {0x01, 0x02, 0x03, 0x01},
        {0x01, 0x01, 0x02, 0x03},
        {0x03, 0x01, 0x01, 0x02}
    };

    uint8_t temp[TEXT_MATRIX_SIZE][TEXT_MATRIX_SIZE] = {{0}};
    for(int col = 0; col < TEXT_MATRIX_SIZE; col++)
    {
        for(int row = 0; row < TEXT_MATRIX_SIZE; row++)
        {
            uint8_t new_byte = 0x00;
            for(int elem = 0; elem < TEXT_MATRIX_SIZE; elem++)
            {
                uint8_t new_xor = 0x00;
                unsigned char h = (unsigned char)((signed char)input[col][elem] >> 7);

                if(M[row][elem] == 0x02)
                {
                    new_xor = (input[col][elem] << 1);
                    new_xor ^= 0x1b & h;
                }
                else if( M[row][elem] == 0x03)
                {
                    new_xor = ((input[col][elem] << 1) ^ input[col][elem]);
                    new_xor ^= 0x1b & h;
                }
                else
                {
                    new_xor = input[col][elem] ;
                }
                new_byte ^= new_xor;
            }
            temp[col][row] = new_byte;
            new_byte = 0;
        }
    }
    
    for(int i = 0; i < TEXT_MATRIX_SIZE; i++)
    {
        for(int j = 0; j < TEXT_MATRIX_SIZE; j++)
        {
            input[i][j] = temp[i][j];
        }
    }

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
        {/*
            roundKeys[i][0] = ;
            roundKeys[i][1] = ;
            roundKeys[i][2] = ;
            roundKeys[i][3] = ;
            */
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
