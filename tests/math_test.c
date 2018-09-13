#include "ALF_std.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
    uint8_t a = 0xFF;
    uint8_t b = 20;
    uint8_t result, carry;
    
    char overflow = ALF_MATH_multiply_8(a, b, &result, &carry);

    printf("overflow: %d\n", overflow);
    printf("%x*%x = 0x%x%x\n", a, b, carry, result);

    /*
    uint64_t a = 0x0FFFFFFFFFFFFFFF;
    uint64_t b = 20;
    uint64_t result, carry;

    char overflow = ALF_MATH_multiply(a, b, &result, &carry);

    printf("overflow: %d\n", overflow);
    printf("%lu*%lu = %lu %lu\n", a, b, carry, result);
    */

    // printf("size: %ld\n", ALF_LOW_HALF(a));
/*
    printf("a = %lx\n", a);
    printf("sizeof a = %lx\n", sizeof a);
    printf("ALF_BITS_IN_BYTE = %lx\n", ALF_BITS_IN_BYTE);
    printf("(sizeof a)*ALF_BITS_IN_BYTE/2  = %lx\n", (sizeof a)*ALF_BITS_IN_BYTE/2 );
    printf("1L << ((sizeof a)*ALF_BITS_IN_BYTE/2) = %lx\n", 1L << ((sizeof a)*ALF_BITS_IN_BYTE/2) );
    printf("(1L << ((sizeof a)*ALF_BITS_IN_BYTE/2)) - 1 = %lx\n", (1L << ((sizeof a)*ALF_BITS_IN_BYTE/2)) - 1 );
    printf("a & ((1L << ((sizeof a)*ALF_BITS_IN_BYTE/2)) - 1) = %lx\n", a & ((1L << ((sizeof a)*ALF_BITS_IN_BYTE/2)) - 1) );
*/
    return 0;
}
