#ifndef SPN_H
#define SPN_H

#include <stdint.h>
#include <stdbool.h>

#define KEY_LEN_BYTES 8
#define BLOCK_LEN_BITS 16
#define BLOCK_LEN_BYTES 4
#define NUM_ROUNDS 4

uint16_t Substitute(uint16_t pt, const uint16_t* box);
uint16_t Permute(uint16_t pt);
uint16_t GenRoundKey(uint32_t mainKey, int round);

uint16_t Encrypt(uint16_t plaintext, uint32_t mainKey);
uint16_t Decrypt(uint16_t ciphertext, uint32_t mainKey);

const uint16_t sbox[BLOCK_LEN_BITS] =
{0xE, 0x4, 0xD, 0x1, 0x2, 0xF, 0xB, 0x8, 0x3, 0xA, 0x6, 0xC, 0x5, 0x9, 0x0, 0x7};

const uint16_t inv_sbox[BLOCK_LEN_BITS] =
{0xE, 0x3, 0x4, 0x8, 0x1, 0xC, 0xA, 0xF, 0x7, 0xD, 0x9, 0x6, 0xB, 0x2, 0x0, 0x5};

const uint16_t permutation[BLOCK_LEN_BITS] =
{1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16};

#endif /* SPN_H */
