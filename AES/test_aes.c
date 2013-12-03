#include <getopt.h>
#include "aes.h"

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

int
main
( int argc, char* argv[] )
{
    uint8_t test_matrix[TEXT_MATRIX_SIZE][TEXT_MATRIX_SIZE] =
    {
        {0xd4, 0xbf, 0x5d, 0x30},
        {0xe0, 0xb4, 0x52, 0xae},
        {0xb8, 0x41, 0x11, 0xf1},
        {0x1e, 0x27, 0x98, 0xe5}
    };

    uint8_t roundKeys[NUM_KEYS][TEXT_MATRIX_SIZE];
    uint8_t mainKey[] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};

    AES_ExpandKeys(mainKey, roundKeys);

    return 0;
}
