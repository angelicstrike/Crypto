#include <stdbool.h>
#include <stdio.h>
#include "aes.h"
    
int 
main()
{
    for(uint32_t i = 0; i < 0xff; i++)
    {
        uint32_t x_inv = gcd_compute(i, FIELD_BYTE);
        printf("%x ", x_inv);
        if(i % 0x0F == 0)
            puts("");
    }
    return 0;
}
