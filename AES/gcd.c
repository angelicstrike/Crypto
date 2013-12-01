#include "aes.h"
#include <stdlib.h>


/*
 * Only works in modulo 2
 */
void
gcd_byte_to_field
( uint32_t byte, int32_t a[EQN_LEN] )
{
    for(int i = 0; i < EQN_LEN; i++)
    {
        a[i] = ( byte & (1 << i) ) >> i;
    }
}

/*
 * Only works in modulo 2
 */
uint32_t
gcd_field_to_byte
( int32_t a[EQN_LEN] )
{
    uint32_t ret_val = 0x0;
    for(int i = 0; i < EQN_LEN; i++)
    {
        if( a[i] )
        {
            ret_val |= (1 << i);
        }
    }

    return ret_val;
}

static void
shift_up
(int32_t a[EQN_LEN], int32_t shift)
{
    int32_t b[EQN_LEN];
    for(int i = 0; i < EQN_LEN; i++)
    {
        b[i] = a[i];
        a[i] = 0;
    }

    for(int i = EQN_LEN - 1; i-shift_up >= 0; i--)
    {
        a[i] = b[i-shift_up];
    } 
}

static void
modulus(int32_t a[EQN_LEN], uint32_t modulus)
{
    for(int i = 0; i < EQN_LEN; i++)
    {
        a[i] = a[i] % modulus;
    }
}

/*
 * Subtracts b from a and  stores the result back into a.
 * Overwrites a
 */
static void
subtract_polynomials
( int32_t a[EQN_LEN], int32_t b[EQN_LEN] )
{
    for(int i = 0; i < EQN_LEN; i++)
    {
        a[i] = a[i] - b[i];    
    }
}

/*
 *  Return codes:
 *  0 --> Arrays are equal
 *  1 --> a is higher field
 *  2 --> b is higher field
 *  3 --> Error error error
 *  Anything larger is undefined behavior
 */
int32_t
gcd_find_larger_field
( int32_t a[EQN_LEN], int32_t b[EQN_LEN] )
{
    int a_start = 31;
    int b_start = 31;

    while (a[a_start] == 0 && a_start > -1) {a_start--;}
    while (b[b_start] == 0 && a_start > -1) {b_start--;}
}

/*
 * Find the greatest common denominator of the polynomial
 * equations a and b, all under the modulus p
 */
uint32_t
gcd_extended_polynomial
( int32_t a[EQN_LEN], int32_t b[EQN_LEN], uint32_t modulus )
{
    int32_t* numerator;
    int32_t* denominator;
    
    int i = 31;
    while( a[i] == 0 && b[i] == 0 && i > -1){ i--; } 

    if( i < 0)
        return 0;

    if(a[i] != 0 && b[i] == 0)
    {
        numerator = a;
        denominator = b;
    }
    else if(a[i] == 0 && b[i] != 0)
    {
        numerator = b;
        denominator = a;
    }
    else if(a[i] == 0 && b[i] == 0)
    {
        return 0;
    }
    else /* Both are non zero*/
    {
        if(a[i] > b[i])
        {
            numerator = a;
            denominator = b;
        }
        else
        {
            numerator = b;
            denominator = a;
        }
    }

    int larger = gcd_find_larger_field(a,b);
    //Actual gcd calculation

}
