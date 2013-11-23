#ifndef AES_H
#define AES_H

#include <stdbool.h>
#include <stdint.h>

typedef uint32_t polynomial;

bool extended_gcd(polynomail a, polynomial b, uint32_t modulus);

bool AES_Subbytes(uint8_t* input);
bool AES_ShiftRows(uint8_t* input);
bool AES_MixColumns(uint8_t* input);
bool AES_AddRoundKey(uint8_t* input);
bool AES_KeySchedule(uint8_t* key, uint8_t* round_key);

uint8_t* AES_Encrypt(uint8_t* plaintext, uint8_t* key);
uint8_t* AES_Decrypt(uint8_t* ciphertext, uint8_t* key); 

#endif /* AES_H */
