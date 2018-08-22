#include "ALF_str.h"

#include <string.h>

char **ALF_STR_split(char *string, const char *delimiters){
    char **splitted = malloc(sizeof(char *));
    char *token = strtok(string, delimiters);
    int i = 0;
    splitted[i++] = token;
    while(token != NULL){
        splitted = realloc(splitted, sizeof(char *) * (i + 1));
        token = strtok(NULL, delimiters);
        splitted[i++] = token;
    }
    return splitted;
}

char* ALF_STR_changeExtension(const char* word, const char* newExt, int lenExt){
    int oldLen = 0, lastDotLen = 0, lenChange = 0;
    char* newWord;

    for(int i = 0; word[i]!= 0x0; i++){
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

    for(int i = 0; i < lenChange; i++){
        newWord[i] = word[i];
    }
    newWord[lenChange] = '.';
    for(int i = 0; i < lenExt; i++){
        newWord[lenChange + i + 1] = newExt[i];
    }
    newWord[lenChange + lenExt + 1] = 0x0;

    return newWord;
}
