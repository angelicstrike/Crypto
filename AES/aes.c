#include "aes.h"
static void
print_matrix
( uint8_t a[TEXT_MATRIX_SIZE][TEXT_MATRIX_SIZE]  )
{
        for(int i = 0; i < TEXT_MATRIX_SIZE; i++)
        {
            for(int j = 0; j < TEXT_MATRIX_SIZE; j++)
            {
                printf("%02x ", a[j][i]);
            }   
                                                        
            printf("\\\\\n");
        }

        printf("\\\\\\\\\n\n");

}

uint8_t
sbox_byte_inversion
( uint8_t byte )
{
    uint32_t inverse;
    if(byte == 0)
        return 0;

    inverse = gcd_compute(byte, FIELD_BYTE);

    return inverse;
}

uint8_t
sbox_matrix_multiply
( uint8_t byte )
{
    uint8_t affine_matrix[8][8] =
    {
        {1,0,0,0,1,1,1,1},
        {1,1,0,0,0,1,1,1},
        {1,1,1,0,0,0,1,1},
        {1,1,1,1,0,0,0,1},
        {1,1,1,1,1,0,0,0},
        {0,1,1,1,1,1,0,0},
        {0,0,1,1,1,1,1,0},
        {0,0,0,1,1,1,1,1}
    };
    
    uint8_t new_byte = 0x0;
    uint8_t new_bit = 0x0;
    uint8_t temp = 0x0;
    
    for(int row = 0; row < 8; row++)
    {
        for(int elem = 0; elem < 8; elem++)
        {
            temp = byte & (0x01 << elem);
            temp >>= elem;
            temp &= affine_matrix[row][elem];
            new_bit ^= temp;
        }
        new_byte |= (new_bit << row);
        new_bit = 0;
        temp = 0;
    }

    return new_byte ^ 0x63;
}

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
        for(int j = 0; j < TEXT_MATRIX_SIZE; j++)
        {
            input[i][j] = sbox_byte_inversion(input[i][j]); 
        }
    } 

    for(int i = 0; i < TEXT_MATRIX_SIZE; i++)
    {
        for(int j = 0; j < TEXT_MATRIX_SIZE; j++)
        {
            input[i][j] = sbox_matrix_multiply(input[i][j]);
        }
    }
    puts("Post subbytes\\\\");
    print_matrix(input);


    
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
    puts("Post shift rows\\\\");
    print_matrix(input);

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

    puts("Post Mix Columns:\\\\");
    print_matrix(input);

    return true;
}


bool 
AES_AddRoundKey
( uint8_t input[TEXT_MATRIX_SIZE][TEXT_MATRIX_SIZE], uint8_t keys[NUM_KEYS][TEXT_MATRIX_SIZE], uint32_t round)
{
    for(int i = 0; i < TEXT_MATRIX_SIZE; i++)
    {
        for(int j = 0; j < TEXT_MATRIX_SIZE; j++)
        {
            input[i][j] ^= keys[4*round + i][j];
        }
    }
    puts("After addition of round key\\\\");
    print_matrix(input);

    return true;
}

bool
AES_ExpandKeys(uint8_t* mainKey, uint8_t roundKeys[NUM_KEYS][TEXT_MATRIX_SIZE])
{
    puts("Generating Round Key for Round 0\\\\");
    for(int i = 0; i < TEXT_MATRIX_SIZE; i++)
    {
        for(int j = 0; j < TEXT_MATRIX_SIZE; j++)
        {
            roundKeys[i][j] = mainKey[4*i + j];
        }
        printf("Made round key word of %02x, %02x, %02x, %02x\\\\\n", roundKeys[i][0], roundKeys[i][1], roundKeys[i][2], roundKeys[i][3]);
    }


    for(int i = 4; i <= 43; i++)
    {
        if(i % 4 == 0)
        {
            printf("\nGenerating Round Keys for Round %d\\\\\n", i/4);
            roundKeys[i][0] = roundKeys[i-4][0] ^ sbox_matrix_multiply(sbox_byte_inversion(roundKeys[i-1][1]));
            roundKeys[i][1] = roundKeys[i-4][1] ^ sbox_matrix_multiply(sbox_byte_inversion(roundKeys[i-1][2]));
            roundKeys[i][2] = roundKeys[i-4][2] ^ sbox_matrix_multiply(sbox_byte_inversion(roundKeys[i-1][3]));
            roundKeys[i][3] = roundKeys[i-4][3] ^ sbox_matrix_multiply(sbox_byte_inversion(roundKeys[i-1][0]));
            
            uint32_t shift = 0x0;
            shift = 0x01 << ((i-4)/4);
            if(shift >= 0x100)
                shift ^= (0x11b << (__builtin_ctz(shift)-8));

            roundKeys[i][0] ^= shift;
        }
        else
        {
            for(int j = 0; j < 4; j++)
            {
                roundKeys[i][j] = roundKeys[i-1][j] ^ roundKeys[i-4][j];
            }
        }
        
        printf("Made round key word of %02x, %02x, %02x, %02x\\\\\n", roundKeys[i][0], roundKeys[i][1], roundKeys[i][2], roundKeys[i][3]);
    }    

    puts("Finished generating round keys\\\\");
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

    AES_ExpandKeys(key, roundKeys);
    AES_AddRoundKey(state_matrix, roundKeys, 0);

    int i;
    for(i = 1; i < NUM_ROUNDS; i++)
    {
        printf("ROUND %d\\\\\n", i);
        puts("Rounds starts with:\\\\");
        print_matrix(state_matrix);
        AES_Subbytes(state_matrix);
        AES_ShiftRows(state_matrix);
        AES_MixColumns(state_matrix);
        AES_AddRoundKey(state_matrix, roundKeys, i);
    }
    
    /* Last Round */
    printf("ROUND %d\\\\\n", NUM_ROUNDS);
    puts("Rounds starts with:\\\\");
    print_matrix(state_matrix);
    AES_Subbytes(state_matrix);
    AES_ShiftRows(state_matrix);
    AES_AddRoundKey(state_matrix, roundKeys, NUM_ROUNDS );

    for(int i = 0; i < TEXT_MATRIX_SIZE; i++)
    {
        for(int j = 0; j < TEXT_MATRIX_SIZE; j++)
        {
            plaintext[4*i + j] = state_matrix[i][j];
        }
    }

    return true;
}


bool
AES_Decrypt
( uint8_t* ciphertext, uint8_t* key )
{

    return true;
}
