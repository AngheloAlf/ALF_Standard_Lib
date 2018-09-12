#include "ALF_std.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
    uint64_t a = 0xFFFFFFFFFFFFFFFF;
    uint64_t b = 20;
    uint64_t result, carry;

    char overflow = ALF_MATH_multiply(a, b, &result, &carry);

    printf("overflow: %d\n", overflow);
    printf("%lu*%lu = %lu %lu\n", a, b, carry, result);

    return 0;
}
