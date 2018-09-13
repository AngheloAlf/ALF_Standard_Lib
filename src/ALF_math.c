#include "ALF_std/ALF_math.h"
#include <stdio.h>


char ALF_MATH_multiply_64(uint64_t a, uint64_t b, uint64_t *result, uint64_t *carry){
    uint64_t x0, x1, x2, x3, aux;
    char overflows = 0;
    aux = a*b;
    if(a != 0 && aux/a != b){ // Checks overflow.
        // https://en.wikipedia.org/wiki/Multiplication_algorithm#Long_multiplication
        overflows = 1;

        printf("a: 0x%lx\n", a);
        printf("b: 0x%lx\n", b);
        printf("ALF_LOW_HALF(a): 0x%lx\n", ALF_LOW_HALF(a));
        printf("ALF_LOW_HALF(b): 0x%lx\n", ALF_LOW_HALF(b));
        printf("ALF_LOW_HALF(a): %ld\n", ALF_LOW_HALF(a));
        printf("ALF_LOW_HALF(b): %ld\n", ALF_LOW_HALF(b));
        x0 = ALF_LOW_HALF(a) * ALF_LOW_HALF(b);
        printf("x0: %lu, 0x%lx\n", x0, x0);
        x1 = ALF_HIGH_HALF(a) * ALF_LOW_HALF(b);
        printf("x1: %lu, 0x%lx\n", x1, x1);
        x2 = ALF_LOW_HALF(a) * ALF_HIGH_HALF(b);
        printf("x2: %lu, 0x%lx\n", x2, x2);
        x3 = ALF_HIGH_HALF(a) * ALF_HIGH_HALF(b);
        printf("x3: %lu, 0x%lx\n", x3, x3);

        printf("ALF_MOVE_LEFT(x0): %lu, 0x%lx\n", ALF_MOVE_LEFT(x0), ALF_MOVE_LEFT(x0));
        printf("ALF_MOVE_LEFT(x1): %lu, 0x%lx\n", ALF_MOVE_LEFT(x1), ALF_MOVE_LEFT(x1));
        printf("ALF_MOVE_LEFT(x2): %lu, 0x%lx\n", ALF_MOVE_LEFT(x2), ALF_MOVE_LEFT(x2));

        printf("ALF_MOVE_LEFT(x1) + x0: %lx\n", ALF_MOVE_LEFT(x1) + x0);
        *result = ALF_MOVE_LEFT(x2) + ALF_MOVE_LEFT(x1) + x0;
        aux = x2 + x1 + ALF_MOVE_RIGHT(x0);
        printf("aux: %lu, 0x%lx\n", aux, aux);
        *carry = x3 + ALF_MOVE_RIGHT(aux);

        /*
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
        */
    }
    else{
        *result = aux;
        *carry = 0;
    }
    return overflows;
}

char ALF_MATH_multiply_8(uint8_t a, uint8_t b, uint8_t *result, uint8_t *carry){
    uint8_t x0, x1, x2, x3, aux;
    char overflows = 0;
    *result = a*b;
    *carry = 0;

    if(a != 0 && (*result)/a != b){ // Checks overflow.
        // https://en.wikipedia.org/wiki/Multiplication_algorithm#Long_multiplication
        overflows = 1;

        x0 = ALF_LOW_HALF(a) * ALF_LOW_HALF(b);
        x1 = ALF_HIGH_HALF(a) * ALF_LOW_HALF(b);
        x2 = ALF_LOW_HALF(a) * ALF_HIGH_HALF(b);
        x3 = ALF_HIGH_HALF(a) * ALF_HIGH_HALF(b);

        *result = ALF_MOVE_LEFT(x2) + ALF_MOVE_LEFT(x1) + x0;
        aux = x2 + x1 + ALF_MOVE_RIGHT(x0);
        *carry = x3 + ALF_MOVE_RIGHT(aux);
    }
    else{
    }
    return overflows;
}
