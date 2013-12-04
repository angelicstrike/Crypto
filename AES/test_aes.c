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
    /*uint8_t test_matrix[16] =
    {
        0x01, 0x23, 0x45, 0x67,
        0x89, 0xAB, 0xCD, 0xEF,
        0x12, 0x34, 0x56, 0x78,
        0x9A, 0xBC, 0xDE, 0xF0
    };*/
    uint8_t test_key[16] =
    {
        0x2B, 0x7E, 0x15, 0x16,
        0x28, 0xAE, 0xD2, 0xA6,
        0xAB, 0xF7, 0x15, 0x88,
        0x09, 0xCF, 0x4F, 0x3C
    };
    
    uint8_t roundKeys[NUM_KEYS][TEXT_MATRIX_SIZE];

    puts("Expanding Key of:");
    for(int i = 0; i < 16; i++)
    {
        printf("%02x ", test_key[i]);
    }   
    puts("\\\\\n");

    AES_ExpandKeys(test_key, roundKeys);

    /*puts("Encrypting plaintext:\\\\");
    for(int i = 0; i < 16; i++)
    {
        printf("%02x ", test_matrix[i]);
    }
    puts("\\\\\n");

    puts("With Key\\\\");
    for(int i = 0; i < 16; i++)
    {
        printf("%02x ", test_key[i]);
    }   

    puts("\\\\\n");
    AES_Encrypt(test_matrix, test_key); 
    
    puts("Final answer\\\\\n");
    for(int i = 0; i < 16; i++)
    {
        printf("%02x ", test_matrix[i]);
    }*/
    return 0;
}
