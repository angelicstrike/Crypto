#include <stdbool.h>
#include <stdio.h>
#include "aes.h"
    
int 
main()
{
    uint32_t x_inv = gcd_compute(0x11, FIELD_BYTE);

    printf("inverse is %x\n", x_inv);
    return 0;
}
