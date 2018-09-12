#include "ALF_std/ALF_math.h"

uint64_t ALF_high_64(uint64_t x){
    return x >> 32;
}

uint64_t ALF_low_64(uint64_t x){
    return 0xFFFFFFFF & x;
}

char ALF_MATH_multiply(uint64_t a, uint64_t b, uint64_t *result, uint64_t *carry){
    char overflows = 0;
    *carry = 0;
    *result = a*b;
    if(a != 0 && (*result)/a != b){ // Checks overflow.
        // https://en.wikipedia.org/wiki/Multiplication_algorithm#Long_multiplication
        overflows = 1;

        uint64_t x0, x1, x2, x3, aux;

        aux = ALF_low_64(a) * ALF_low_64(b);
        x0 = ALF_low_64(aux);

        aux = ALF_high_64(a) * ALF_low_64(b) + ALF_high_64(aux);
        x1 = ALF_low_64(aux);
        x2 = ALF_high_64(aux);

        aux = x1 + ALF_low_64(a) * ALF_high_64(b);
        x1 = ALF_low_64(aux);

        aux = x2 + ALF_high_64(a) * ALF_high_64(b) + ALF_high_64(aux);

        x2 = ALF_low_64(aux);
        x3 = ALF_high_64(aux);

        *result = x1 << 32 | x0;
        *carry = x3 << 32 | x2;
    }
    return overflows;
}
