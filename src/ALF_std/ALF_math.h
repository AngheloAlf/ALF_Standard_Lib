/** \file ALF_math.h
* Some math releated functions.
**/

#ifndef ALF_math_h
#define ALF_math_h

#include "ALF_common.h"

#include <stdint.h>

/// 
char ALF_MATH_multiply_64(uint64_t a, uint64_t b, uint64_t *result, uint64_t *carry);

///
char ALF_MATH_multiply_32(uint32_t a, uint32_t b, uint32_t *result, uint32_t *carry);

///
char ALF_MATH_multiply_16(uint16_t a, uint16_t b, uint16_t *result, uint16_t *carry);

///
char ALF_MATH_multiply_8(uint8_t a, uint8_t b, uint8_t *result, uint8_t *carry);

#define ALF_MATH_multiply8(a, b, result, carry) ALF_MATH_multiply_64(a, b, result, carry)

#define ALF_MATH_multiply4(a, b, result, carry) ALF_MATH_multiply_32(a, b, result, carry)

#define ALF_MATH_multiply2(a, b, result, carry) ALF_MATH_multiply_16(a, b, result, carry)

#define ALF_MATH_multiply1(a, b, result, carry) ALF_MATH_multiply_8(a, b, result, carry)

#define ALF_MATH_multiply  _Generic((a), \
                                        uint64_t: ALF_MATH_multiply_64, \
                                        uint32_t: ALF_MATH_multiply_32, \
                                        uint16_t: ALF_MATH_multiply_16, \
                                        uint8_t: ALF_MATH_multiply_8)

#endif /* ALF_math_h */
