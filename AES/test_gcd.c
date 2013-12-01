#include <stdbool.h>
#include <stdio.h>
#include "aes.h"
    
int 
main()
{
    uint32_t a_byte = 0x010000101000011;
    uint32_t b_byte = 0x010011;
   
    int32_t a[EQN_LEN];
    int32_t b[EQN_LEN];

    gcd_byte_to_field(a_byte, a);
    gcd_byte_to_field(b_byte, b);

    puts("a is:");
    for(int i = 0; i < EQN_LEN; i++)
        printf("%d\n", a[i]);

    puts("b is:");
    for(int i = 0; i < EQN_LEN; i++)
        printf("%d\n", b[i]);

    return 0;
}
