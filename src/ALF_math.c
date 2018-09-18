#include "ALF_std/ALF_math.h"

bool ALF_MATH_multiply_64(uint64_t a, uint64_t b, uint64_t *result, uint64_t *carry){
    uint64_t x0, x1, x2, x3, aux;
    bool overflows = false;
    *result = a*b;
    *carry = 0;
    if(a != 0 && (*result)/a != b){ // Checks overflow.
        // https://en.wikipedia.org/wiki/Multiplication_algorithm#Long_multiplication
        overflows = true;

        x0 = ALF_LOW_HALF(a) * ALF_LOW_HALF(b);
        x1 = ALF_MOVE_RIGHT(a) * ALF_LOW_HALF(b);
        x2 = ALF_LOW_HALF(a) * ALF_MOVE_RIGHT(b);
        x3 = ALF_MOVE_RIGHT(a) * ALF_MOVE_RIGHT(b);

        *result = ALF_MOVE_LEFT(x2) + ALF_MOVE_LEFT(x1) + x0;
        aux = x2 + x1 + ALF_MOVE_RIGHT(x0);
        *carry = x3 + ALF_MOVE_RIGHT(aux);
    }
    return overflows;
}

bool ALF_MATH_multiply_32(uint32_t a, uint32_t b, uint32_t *result, uint32_t *carry){
    uint32_t x0, x1, x2, x3, aux;
    bool overflows = false;
    *result = a*b;
    *carry = 0;

    if(a != 0 && (*result)/a != b){ // Checks overflow.
        // https://en.wikipedia.org/wiki/Multiplication_algorithm#Long_multiplication
        overflows = true;

        x0 = ALF_LOW_HALF(a) * ALF_LOW_HALF(b);
        x1 = ALF_MOVE_RIGHT(a) * ALF_LOW_HALF(b);
        x2 = ALF_LOW_HALF(a) * ALF_MOVE_RIGHT(b);
        x3 = ALF_MOVE_RIGHT(a) * ALF_MOVE_RIGHT(b);

        *result = ALF_MOVE_LEFT(x2) + ALF_MOVE_LEFT(x1) + x0;
        aux = x2 + x1 + ALF_MOVE_RIGHT(x0);
        *carry = x3 + ALF_MOVE_RIGHT(aux);
    }
    return overflows;
}


bool ALF_MATH_multiply_16(uint16_t a, uint16_t b, uint16_t *result, uint16_t *carry){
    uint16_t x0, x1, x2, x3, aux;
    bool overflows = false;
    *result = a*b;
    *carry = 0;

    if(a != 0 && (*result)/a != b){ // Checks overflow.
        // https://en.wikipedia.org/wiki/Multiplication_algorithm#Long_multiplication
        overflows = true;

        x0 = ALF_LOW_HALF(a) * ALF_LOW_HALF(b);
        x1 = ALF_MOVE_RIGHT(a) * ALF_LOW_HALF(b);
        x2 = ALF_LOW_HALF(a) * ALF_MOVE_RIGHT(b);
        x3 = ALF_MOVE_RIGHT(a) * ALF_MOVE_RIGHT(b);

        *result = ALF_MOVE_LEFT(x2) + ALF_MOVE_LEFT(x1) + x0;
        aux = x2 + x1 + ALF_MOVE_RIGHT(x0);
        *carry = x3 + ALF_MOVE_RIGHT(aux);
    }
    return overflows;
}


bool ALF_MATH_multiply_8(uint8_t a, uint8_t b, uint8_t *result, uint8_t *carry){
    uint8_t x0, x1, x2, x3, aux;
    bool overflows = false;
    *result = a*b;
    *carry = 0;

    if(a != 0 && (*result)/a != b){ // Checks overflow.
        // https://en.wikipedia.org/wiki/Multiplication_algorithm#Long_multiplication
        overflows = true;

        x0 = ALF_LOW_HALF(a) * ALF_LOW_HALF(b);
        x1 = ALF_MOVE_RIGHT(a) * ALF_LOW_HALF(b);
        x2 = ALF_LOW_HALF(a) * ALF_MOVE_RIGHT(b);
        x3 = ALF_MOVE_RIGHT(a) * ALF_MOVE_RIGHT(b);

        *result = ALF_MOVE_LEFT(x2) + ALF_MOVE_LEFT(x1) + x0;
        aux = x2 + x1 + ALF_MOVE_RIGHT(x0);
        *carry = x3 + ALF_MOVE_RIGHT(aux);
    }
    return overflows;
}
