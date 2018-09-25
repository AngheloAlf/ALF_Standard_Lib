#include "ALF_std.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    // char *example = ALF_STR_changeExtension("example.txt", "asdf", 4);
    // printf("%s\n", example);

    const char *coso = "123wea123de123la123wea.123";
    const char *cortar = "123";
    char **ejemplo = ALF_STR_split(coso, cortar);
    char *aux;
    int i = 0;
    while((aux = ejemplo[i++]) != NULL){
        printf("\"%s\"\n", aux);
    }
    printf("%s\n", coso);
    ALF_STR_freeSplitted(ejemplo);
/*
    char asdf[3] = {0, 0, 0};
    for(i = 0; i < (2<<11); i++){
        asdf[0] = 0b11000000 | (i & 0b00011111);
        asdf[1] = 0b10000000 | (i & 0b00011111100000)>>5;
        printf("%s\n", asdf);
    }*/
    /*
    char *wea =  strstr(coso, "123");
    printf("%p\n", coso);
    printf("%p\n", wea);
    */
/*
    char *wea = strdup(coso);
    char **cortado = ALF_STR_split(wea, "123");
    while(*cortado != NULL){
        printf("%s\n", *cortado);
        cortado++;
    }
    printf("\nOriginal: %s\n", wea);
    for(int i = 0; i < strlen(coso); i++){
        printf("%i ", wea[i]);
    }
    printf("\n");
    free(wea);
    */
    return 0;
}