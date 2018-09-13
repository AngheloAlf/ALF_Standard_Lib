/** \file ALF_math.h
* Some math releated functions.
**/

#ifndef ALF_math_h
#define ALF_math_h

#include "ALF_common.h"

#include <stdint.h>

/// 
char ALF_MATH_multiply_64(uint64_t a, uint64_t b, uint64_t *result, uint64_t *carry);

char ALF_MATH_multiply_8(uint8_t a, uint8_t b, uint8_t *result, uint8_t *carry);

#endif /* ALF_math_h */
