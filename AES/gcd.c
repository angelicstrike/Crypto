#include "aes.h"
#include <stdlib.h>


void
gcd_byte_to_field
( uint32_t byte, int32_t a[EQN_LEN] )
{

}

uint32_t
gcd_field_to_byte
( int32_t a[EQN_LEN] )
{
    for(int i = 0; i < EQN_LEN; i++)
    {

    }
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

static void
gcd_helper
( int32_t a[EQN_LEN], int32_t b[EQN_LEN] )
{

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
    while((a[i] != 0 || b[i] != 0) && i > -1){ i-; } 

    if( i < 0)
        i = 0;

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

    //Actual gcd calculation

}
