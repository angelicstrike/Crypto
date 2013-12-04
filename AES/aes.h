#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef AES_H
#define AES_H

#define NUM_ROUNDS 10
#define TEXT_MATRIX_SIZE 4
#define KEY_MATRIX_SIZE 4
#define NUM_KEYS 44

#define EQN_LEN 32
#define FIELD_BYTE 0x11B //0x100011011
#define C_BYTE 0x63

uint8_t sbox_matrix_multiply( uint8_t byte);
uint8_t sbox_byte_inversion(uint8_t byte);
uint32_t gcd_compute( uint32_t a, uint32_t b);
//void gcd_find_inverse(int32_t inverse[EQN_LEN], int a[EQN_LEN], int b[EQN_LEN], int modulus);
uint32_t gcd_extended_polynomial(int32_t a[EQN_LEN], int32_t  b[EQN_LEN], uint32_t modulus);
void gcd_byte_to_field(uint32_t byte, int32_t a[EQN_LEN]);
uint8_t gcd_field_to_byte(int32_t a[EQN_LEN]);
int32_t gcd_find_larger_field(int32_t a[EQN_LEN], int32_t b[EQN_LEN]);

bool AES_Subbytes(uint8_t input[TEXT_MATRIX_SIZE][TEXT_MATRIX_SIZE]);
bool AES_SubWord(uint8_t word[TEXT_MATRIX_SIZE]);
bool AES_ShiftRows(uint8_t input[TEXT_MATRIX_SIZE][TEXT_MATRIX_SIZE]);
bool AES_MixColumns(uint8_t input[TEXT_MATRIX_SIZE][TEXT_MATRIX_SIZE]);
bool AES_AddRoundKey(uint8_t input[TEXT_MATRIX_SIZE][TEXT_MATRIX_SIZE], uint8_t keys[NUM_KEYS][TEXT_MATRIX_SIZE], uint32_t round);
bool AES_ExpandKeys(uint8_t* mainKey, uint8_t roundKeys[NUM_KEYS][TEXT_MATRIX_SIZE]);

/*
 * For the gcd, a[0] is the constant value, and a[EQN_LEN] is the coefficient of the highest value
 */

/*
 * input array structure by column:
 *    input[0]*     input[1]*    input[2]*    input[3]*
 *    |             |            |            |
 *    V             V            V            V
 0 -> b0            b4           b8           b12
 1 -> b1            b5           b9           b13
 2 -> b2            b6           b10          b14
 3 -> b3            b7           b11          b15
 */

bool AES_Encrypt(uint8_t* plaintext, uint8_t* key);
bool AES_Decrypt(uint8_t* ciphertext, uint8_t* key); 

#endif /* AES_H */
