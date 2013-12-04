#include "aes.h"

/*
 *  Returns the shift needed to get b to have the same
 *  degree as a.
 *  If b has a higher degree, then the shift returned
 *  is negative and a should be shifted instead
 */
static int32_t
find_shift
(uint32_t a, uint32_t b)
{
    /* Number of leading zeroes in a and b, undefined if a or b is 0*/
    int a_lead = __builtin_clz(a);
    int b_lead = __builtin_clz(b);


    return a_lead - b_lead;
}

static int32_t
degree
( uint32_t num )
{
    uint32_t degree = 0;
    while(num >>= 1)
    {
        degree++;
    }

    return degree;
}

static uint32_t
barrel_multiply
( uint32_t a, uint32_t b )
{
    uint32_t ans = 0;
    int32_t shift = -1;
    do {
        shift++;

        if(b & 0x01)
        {
            ans ^= (a << shift);
        }

    }while( b >>= 1 );

    return ans;
}

/*
 *  Works mod 2 always
 */
uint32_t
gcd_compute
( uint32_t a, uint32_t b )
{
    int counter = 0;
    int32_t shifts[EQN_LEN] = {0};
    uint32_t higher;
    uint32_t lower;
    if(a >= b)
    {
        higher = a;
        lower = b;
    }
    else
    {
        higher = b;
        lower = a;
    }

    printf("Finding gcd of %x and %x\\\\\n", higher, lower);
    while( higher > 1 && lower > 1 )
    {
        while( degree(higher) >= degree(lower)  )
        {
            shifts[counter] |= (0x01 << find_shift(lower, higher));
            higher ^= (lower << find_shift(lower, higher));
        }
        printf("Generated quotient of %x\\\\\n", shifts[counter]);
        counter++;
        uint32_t temp = higher;
        higher = lower;
        lower = temp;
    }

    uint32_t prev = 0;
    uint32_t cur = 1;
    uint32_t ans = 0;
    counter--;
    while(counter > -1)
    {
        ans = barrel_multiply(cur, shifts[counter]);
        ans ^= prev;

        prev = cur;
        cur = ans;
        printf("Generated temporary value of %x\\\\\n", cur);
        ans = 0;
        counter--;
    }
    if(higher == 0) //gcd higher than 1
        ans = lower;
    else if(lower == 0) //still gcd higher than 1
        ans = higher;
    else//mutually prime
        ans = 1;


    if(a >= b)
    {
        higher = a;
        lower = b;
    }
    else
    {
        higher = b;
        lower = a;
    }

    printf("So our gcd equation is (%x)(%x) + (%x)(%x) = %x mod 2\\\\\n", lower, cur, higher, prev, ans);
    return cur;
}
