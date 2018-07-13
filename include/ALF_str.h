#ifndef ALF_LIB_STR_H
#define ALF_LIB_STR_H

#include <stdlib.h>
#include <string.h>

char **ALF_split(char *string, char *delimiters);

void ALF_charCopy(unsigned char* dst, const unsigned char* src, size_t size);

unsigned char *ALF_newCharFromIndex(const unsigned char* src, size_t size, size_t start);

char* ALF_changeExtension(const char* word, const char* newExt, int lenExt);

#endif /* ALF_LIB_STR_H */