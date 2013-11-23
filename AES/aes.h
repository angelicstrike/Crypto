#ifndef AES_H
#define AES_H

#include <stdbool.h>
#include <stdint.h>

#define NUM_ROUNDS 10

typedef uint32_t polynomial;

bool gcd_extended_polynomial(polynomail a, polynomial b, uint32_t modulus);

bool AES_Subbytes(uint8_t* input);
bool AES_ShiftRows(uint8_t* input);
bool AES_MixColumns(uint8_t* input);
bool AES_AddRoundKey(uint8_t* input, uint8_t* key, uint32_t round);

/*
 * input array structure by column:
 * input[0]     input[1]    input[2]    input[3]
 * |            |           |           |
 * V            V           V           V
 * b0           b4          b8          b12
 * b1           b5          b9          b13
 * b2           b6          b10         b14
 * b3           b7          b11         b15
 */

bool AES_Encrypt(uint8_t* plaintext, uint8_t* key);
bool AES_Decrypt(uint8_t* ciphertext, uint8_t* key); 

#endif /* AES_H */
