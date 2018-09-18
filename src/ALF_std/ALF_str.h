/** \file ALF_str.h
* Macros and functions concerning strings operations
**/

#ifndef ALF_str_h
#define ALF_str_h

#include "ALF_common.h"

#include <stdlib.h>
#include <stdint.h>

/// Python-like string.split()
/**
 * Params:

 * -char *string: The string to be splited.

 * -char *delimiters: The delimiter that is going to split the string.

 * Return value:

 * ->char **: An 'array' of strings. Each string is a part of the original string param.

**/
char **ALF_STR_split(char *string, const char *delimiters);

/// 
char* ALF_STR_changeExtension(const char* word, const char* newExt, size_t lenExt);

#endif /* ALF_str_h */
