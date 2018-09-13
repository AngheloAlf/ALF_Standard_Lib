#include "ALF_std.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
    /*
    uint8_t a = 0xFF;
    uint8_t b = 20;
    uint8_t result, carry;
    
    char overflow = ALF_MATH_multiply(a, b, &result, &carry);

    printf("overflow: %d\n", overflow);
    printf("%x*%x = 0x%x%x\n", a, b, carry, result);
    */


    uint64_t a = 0x0FFFFFFFFFFFFFFF;
    uint64_t b = 20;
    uint64_t result, carry;

    char overflow = ALF_MATH_multiply(a, b, &result, &carry);

    printf("overflow: %d\n", overflow);
    printf("%lx*%lx = 0x%lx%lx\n", a, b, carry, result);



    return 0;
}
