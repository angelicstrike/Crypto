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

    while( higher >1 && lower > 1 )
    {
        while( higher > lower  )
        {
            shifts[counter] |= (0x01 << find_shift(lower, higher));
            higher ^= (lower << find_shift(lower, higher));
        }
        counter++;
        uint32_t temp = higher;
        higher = lower;
        lower = temp;
    }

    uint32_t prev = 0;
    uint32_t cur = 1;
    counter--;
    while(counter > -1)
    {
        printf("prev %x and cur %x and shift %x\n", prev, cur, shifts[counter]);
        cur *= shifts[counter];
        cur ^= prev;
        counter--;
        prev = cur;
    }

    return cur;
}
