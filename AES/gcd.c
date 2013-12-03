#include "aes.h"

/*
 * Only works in modulo 2
 */
void
gcd_byte_to_field
( uint32_t byte, int32_t a[EQN_LEN] )
{
    for(int i = 0; i < EQN_LEN; i++)
    {
        a[i] = 0x0;
    }

    for(int i = 0; i < EQN_LEN; i++)
    {
        a[i] = ( byte & (1 << i) ) >> i;
    }
}

/*
 * Only works in modulo 2
 */
uint8_t
gcd_field_to_byte
( int32_t a[EQN_LEN] )
{
    uint8_t ret_val = 0x0;
    for(int i = 0; i < EQN_LEN; i++)
    {
        if( a[i] )
        {
            ret_val |= (1 << i);
        }
    }

    return ret_val;
}

void
shift_up
(int32_t a[EQN_LEN], int32_t shift)
{
    int32_t b[EQN_LEN];
    for(int i = 0; i < EQN_LEN; i++)
    {
        b[i] = a[i];
        a[i] = 0;
    }

    for(int i = EQN_LEN - 1; i-shift >= 0; i--)
    {
        a[i] = b[i-shift];
    } 
}

static void
gcd_modulus(int32_t a[EQN_LEN], uint32_t modulus)
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

    return 3;
}

/*
 *  All shifts are relative to a, so
 *  <0 --> a must be shifted to match b
 *  0  --> no shift must occur
 *  >0 --> b must be shifted to match a
 */
int32_t 
gcd_find_shift
( int32_t a[EQN_LEN], int32_t b[EQN_LEN] )
{
    int a_start = 31;
    int b_start = 31;
    while( a[a_start] == 0 && a_start > -1) {a_start--;}
    while( b[b_start] == 0 && b_start > -1) {b_start--;}
    
    if(a_start < 0 || b_start < 0)
        return 0;
    else
        return (a_start - b_start);
}

double
gcd_find_mult
( int32_t a[EQN_LEN], int32_t b[EQN_LEN] )
{
    int a_start = 31;
    int b_start = 31;

    while( a[a_start] == 0 && a_start > -1) {a_start--;}
    while( b[b_start] == 0 && b_start > -1) {b_start--;}
    
    
    return 0.0;
}


static bool
gcd_done
( int32_t a[EQN_LEN] )
{
    for(int i = 0; i < EQN_LEN-1; i++)
    {
        if ( a[i] != 0 )
            return false;
    }
    if(a[EQN_LEN-1] == 0 || a[EQN_LEN-1] == 1)
        return true;
    else
        return false;
}

/*
 * Find the greatest common denominator of the polynomial
 * equations a and b, all under the modulus p
 *
 */
uint32_t
gcd_extended_polynomial
( int32_t a[EQN_LEN], int32_t b[EQN_LEN], uint32_t p )
{
    int counter = 0;
    int32_t shifts[EQN_LEN];
    int32_t mults[EQN_LEN];
    //Actual gcd calculation
    int larger = 0;
    while( !gcd_done(a) && !gcd_done(b) )
    {
        larger = gcd_find_larger_field(a,b);
        if(larger == 0) //equal
        {
            shifts[counter] = 0;
            subtract_polynomials(a,b);
        }
        else if(larger == 1) // a is larger
        {
            shifts[counter] = gcd_find_shift(a,b);
            mults[counter] = gcd_find_mult(a,b);
            shift_up(b, shifts[counter]);
            subtract_polynomials(a,b);
            shift_down(b, shifts[counter]);
        }
        else if(larger == 2) // b is larger
        {
            //same as if a was larger, but roles of a and b are reversed
            shifts[counter] = gcd_find_shift(b,a);
            shift_up(a, shifts[counter]);
            subtract_polynomials(b,a); 
            shift_down(a, shifts[counter]);
        }
        else //Error
        {
            printf("An error occurred while encrypting\n");
            exit(-1);
        }
        gcd_modulus(a, p);
        gcd_modulus(b, p);
        counter++;
    }
    return 0;
}
