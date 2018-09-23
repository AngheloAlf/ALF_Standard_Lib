#include "ALF_std/ALF_str.h"

#include <string.h>

inline void __ALF_cleanCharDoublePointer(char **pointer, size_t last_i){
    while(last_i > 0){
        free(pointer[--last_i]);
    }
    free(pointer);
}

void *ALF_allocAndCopy(const void *input_data, size_t size){
    void *output_pointer = malloc(size);
    if(output_pointer == NULL){
        return NULL;
    }
    memcpy(output_pointer, input_data, size);
    return output_pointer;
}

char **ALF_STR_split(const char *string, const char *delimiters){
    void *aux;
    size_t i = 0, difference = 0, deliSize = strlen(delimiters);
    char *next, *last = (char *)string;

    char **splitted = (char **)malloc(sizeof(char *) * (i+2));
    if(splitted == NULL){
        return NULL;
    }

    for(next = strstr(last, delimiters); next != NULL; i++, next = strstr(last, delimiters)){
        if((aux = realloc(splitted, sizeof(char *) * (i+3))) == NULL){
            __ALF_cleanCharDoublePointer(splitted, i);
            return NULL;
        }
        splitted = (char **)aux;

        difference = next - last;
        if((splitted[i] = (char *)ALF_allocAndCopy(last, sizeof(char) * (difference + 1) )) == NULL){
            __ALF_cleanCharDoublePointer(splitted, i);
            return NULL;
        }
        splitted[i][difference] = 0;

        last = next + deliSize;
    }

    difference = strlen(last);
    if((splitted[i] = (char *)ALF_allocAndCopy(last, sizeof(char) * (difference + 1))) == NULL){
        __ALF_cleanCharDoublePointer(splitted, i);
        return NULL;
    }
    splitted[i][difference] = 0;

    splitted[i+1] = NULL;
    return splitted;
}

void ALF_STR_freeSplitted(char **splitted){
    char *aux;
    size_t i = 0;
    while((aux = splitted[i++]) != NULL){
        free(aux);
    }
    free(splitted);
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
