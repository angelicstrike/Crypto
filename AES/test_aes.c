#include <getopt.h>
#include "aes.h"
/*
static void
print_matrix
( uint8_t a[TEXT_MATRIX_SIZE][TEXT_MATRIX_SIZE]  )
{
    for(int i = 0; i < TEXT_MATRIX_SIZE; i++)
    {
        for(int j = 0; j < TEXT_MATRIX_SIZE; j++)
        {
            printf("%x ", a[j][i]);
        }
        printf("\n");
    }

}
*/
int
main
( int argc, char* argv[] )
{
    uint8_t test_matrix[16] =
    {
        0x32, 0x43, 0xf6, 0xa8,
        0x88, 0x5a, 0x30, 0x8d,
        0x31, 0x31, 0x98, 0xa2,
        0xe0, 0x37, 0x07, 0x34
    };
    uint8_t test_key[16] =
    {
        0x2b, 0x7e, 0x15, 0x16,
        0x28, 0xae, 0xd2, 0xa6,
        0xab, 0xf7, 0x15, 0x88,
        0x09, 0xcf, 0x4f, 0x3c
    };
/*
    uint8_t roundKeys[NUM_KEYS][TEXT_MATRIX_SIZE];
    uint8_t mainKey[] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};

    AES_ExpandKeys(mainKey, roundKeys);
*/

    for(int i = 0; i < 16; i++)
    {
        printf("%x ", test_matrix[i]);
    }
    puts("");
    AES_Encrypt(test_matrix, test_key); 
    for(int i = 0; i < 16; i++)
    {
        printf("%x ", test_matrix[i]);
    }
    return 0;
}
