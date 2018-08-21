/** \file ALF_str.h
* Macros and functions concerning strings operations
**/

#ifndef ALF_str_h
#define ALF_str_h

#include "ALF_common.h"

// TODO: Update this file with the new function convetion.

#include <stdlib.h>

/// Python-like string.split()
/**
 * Params:

 * -char *string: The string to be splited.

 * -char *delimiters: The delimiter that is going to split the string.

 * Return value:

 * ->char **: An 'array' of strings. Each string is a part of the original string param.

**/
char **ALF_split(char *string, const char *delimiters);

/// 
char* ALF_changeExtension(const char* word, const char* newExt, int lenExt);

#endif /* ALF_str_h */