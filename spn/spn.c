#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <getopt.h>
#include <string.h>
#include "spn.h"

//Something is wrong here
uint16_t Substitute
(uint16_t pt, const uint16_t* box)
{
    uint16_t ct = 0x0;
    uint16_t temp = 0;
    int i;
    printf("Performing SBox operation on %x\n", pt);
    for(i = 0; i < BLOCK_LEN_BYTES; i++)
    {
        temp = ( pt >> (4*i) ) & 0x0F;
        temp = box[temp];
        ct |= ( temp << (4*i) );
    }
    printf("SBox operations yielded %x\n", ct);

    return ct;
}

uint16_t Permute
(uint16_t pt)
{
    uint16_t ct = 0x0;
    uint16_t temp = 0x0;

    int i;
    printf("Permuting string %x using permutation mapping\n", pt);
    for(i = 0; i < BLOCK_LEN_BITS; i++)
    {
        temp = (pt >> (15-i)) & 0x01;
        ct |= (temp << (16 - permutation[i])); 
    }
    printf("Permutation mapping yielded %x\n", ct);

    return ct;
}

//Round goes from 0 to N-1, where N is the number of rounds
//in the encryption
uint16_t GenRoundKey
(uint32_t mainKey, int round)
{
    uint16_t subKey = 0x0;
    uint32_t temp = 0x0;

    temp = mainKey & ((0xFFFF <<  16) >> 4*round);
    subKey = temp >> 4*(4-round);

    printf("Generating round key of %x\n", subKey);

    return subKey;
}

static void usage
()
{
    printf("Options:\n"
           "-d: decrypt the given string. If this is not present, defaults to encryptions\n"
           "-p: four hex digit plaintext/ciphertext to encrypt/decrypt\n"
           "-k: eight hext digit key to be used in encryption/decryption\n");

    abort();
}

uint16_t Encrypt(uint16_t plaintext, uint32_t mainKey)
{
    int i = 0;
    uint16_t subKey = 0x0;
    printf("Pre Rounds, Key whitening\n");
    subKey= GenRoundKey(mainKey, 0);
    plaintext = plaintext ^ subKey;
    printf("XOR of subkey and current text yielded %4x\n\n", plaintext);
    for(i = 0; i < NUM_ROUNDS - 1; i++)
    {
        printf("Round %d\n", i+1);
        plaintext = Substitute(plaintext, sbox);
        plaintext = Permute(plaintext);
        subKey = GenRoundKey(mainKey, i+1);
        plaintext = plaintext ^ subKey;
        printf("XOR of subkey and current text yielded %4x\n", plaintext);
        printf("\n");
    }
    printf("Round 4, Substitution and Round Key addition only\n");
    plaintext = Substitute(plaintext, sbox);
    subKey = GenRoundKey(mainKey, 4);
    plaintext = plaintext ^ subKey;
    printf("XOR of subkey and current text yielded %4x\n", plaintext);
    printf("Final ciphertext is: %4x\n", plaintext);


    return plaintext;
}

uint16_t Decrypt(uint16_t ciphertext, uint32_t mainKey)
{
    int i = 0;
    int counter = 1;

    uint16_t subKey = 0x0;
    printf("Performing pre-rounds, subkey addition\n");
    subKey = GenRoundKey(mainKey, 4);
    ciphertext = ciphertext ^ subKey;
    printf("XOR of subkey and current text yielded %4x\n\n", ciphertext);
    for(i = NUM_ROUNDS - 1; i > 0; i--)
    {
        printf("Round %d\n", counter);
        ciphertext = Substitute(ciphertext, inv_sbox);
        ciphertext = Permute(ciphertext);
        subKey = GenRoundKey(mainKey, i);
        subKey = Permute(subKey);
        ciphertext = ciphertext ^ subKey;
        printf("XOR of permuted subkey and current text yielded %4x\n", ciphertext);
        printf("\n");
        counter++;
    }

    printf("Round 4, Substitution and Round Key Addition only\n");
    ciphertext = Substitute(ciphertext, inv_sbox);
    subKey = GenRoundKey(mainKey, 0);
    ciphertext = ciphertext ^ subKey;
    printf("XOR of subkey and current text yielded %4x\n", ciphertext);
    printf("Final plaintext is: %4x\n", ciphertext);

    return ciphertext;
}

int main
(int argc, char* argv[])
{
    assert(argc > 2 || !!!"Input both a key and a plain text to encrypt");

    char input_pt[BLOCK_LEN_BYTES];
    char input_key[KEY_LEN_BYTES];
    bool encrypt = true;

    uint16_t plaintext = 0x0;
    uint32_t mainKey = 0x0;

    int opt;

    while( (opt = getopt(argc, argv, "hdp:k:")) != -1 ) {
        switch(opt) {
            case 'h':
                usage();
                break;
            case 'd':
                encrypt = false;
                break;
            case 'p':
                assert(strlen(optarg) == 4 || !!!"Plaintext must be of length 4");
                strncpy(input_pt, optarg, BLOCK_LEN_BYTES);
                break;
            case 'k':
                assert(strlen(optarg) == KEY_LEN_BYTES || !!!"Key must be of length 8");
                strncpy(input_key, optarg, KEY_LEN_BYTES);
                break;
            default:
                usage();
                break;
        }
    }
    plaintext |= (uint16_t)(strtoul(input_pt, NULL, 16));
    mainKey |= (uint32_t)(strtoul(input_key, NULL, 16));

    printf("Received plaintext: %x\n"
           "Received key: %x\n",
           plaintext, mainKey);

    if(encrypt)
        Encrypt(plaintext, mainKey);
    else
        Decrypt(plaintext, mainKey);

        
    return 0;

}

