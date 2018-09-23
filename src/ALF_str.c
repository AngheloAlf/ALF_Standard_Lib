#include "ALF_std/ALF_str.h"

#include <string.h>

char **ALF_STR_split(const char *string, const char *delimiters){
    void *aux;
    size_t i = 0, difference = 0;
    char **splitted = (char **)malloc(sizeof(char *) * (i+2));
    if(splitted == NULL){
        return NULL;
    }
    size_t deliSize = strlen(delimiters);

    char *last = (char *)string;

    char *next = strstr(last, delimiters);
    while(next != NULL){
        aux = realloc(splitted, sizeof(char *) * (i+3));
        if(aux == NULL){
            while(i > 0){
                free(splitted[--i]);
            }
            free(splitted);
            return NULL;
        }
        splitted = (char **)aux;

        difference = next - last;
        splitted[i] = (char *)malloc(sizeof(char) * (difference + 1));
        if(splitted[i] == NULL){
            while(i > 0){
                free(splitted[--i]);
            }
            free(splitted);
            return NULL;
        }
        memcpy(splitted[i], last, difference);
        splitted[i][difference] = 0;

        last = next + deliSize;
        next = strstr(last, delimiters);
        i++;
    }
    difference = strlen(last);
    splitted[i] = (char *)malloc(sizeof(char) * (difference + 1));
    memcpy(splitted[i], last, difference);
    splitted[i][difference] = 0;
    splitted[i+1] = NULL;

    return splitted;
}

char* ALF_STR_changeExtension(const char* word, const char* newExt, size_t lenExt){
    size_t oldLen = 0, lastDotLen = 0, lenChange = 0;
    char* newWord;

    for(size_t i = 0; word[i]!= 0x0; i++){
        if(word[i] == '.'){
            lastDotLen = i;
        }
        oldLen += 1;
    }

    if(lastDotLen != 0){
        lenChange = lastDotLen;
    }
    else{
        lenChange = oldLen;
    }
    newWord = malloc(sizeof(char)*(lenChange + lenExt + 2));
    if(newWord == NULL){
        return NULL;
    }

    for(size_t i = 0; i < lenChange; i++){
        newWord[i] = word[i];
    }
    newWord[lenChange] = '.';
    for(size_t i = 0; i < lenExt; i++){
        newWord[lenChange + i + 1] = newExt[i];
    }
    newWord[lenChange + lenExt + 1] = 0x0;

    return newWord;
}
