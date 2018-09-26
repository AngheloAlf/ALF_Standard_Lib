#include "ALF_std.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void searchCharPairTest(){
    char *parentesis = "if((a = b(c(d(e(f))))) == g){printf(\"%%s\\n\", h);}";
    char *encontrado = strstr(parentesis, "(");
    char *final = ALF_STR_searchCharPair(encontrado+1, '(', ')');
    if(final == NULL){
        printf("Not found.\n");
        return;
    }
    printf("Original: %s\n", parentesis);
    printf("First '(': %s\n", encontrado);
    printf("Last ')': %s\n", final);
    char copiado[100];
    strncpy(copiado, encontrado, final-encontrado);
    printf("Extracted: %s\n", copiado);
}

void changeExtensionTest(){
    char *example = ALF_STR_changeExtension("example.txt", "asdf", 4);
    printf("%s\n", example);
}

void splitTest(){
    const char *coso = "123wea123de123la123wea.123";
    const char *cortar = "123";
    char **ejemplo = ALF_STR_split(coso, cortar);
    char *aux;
    int i = 0;
    while((aux = ejemplo[i++]) != NULL){
        printf("\"%s\"\n", aux);
    }
}

int main(){
    searchCharPairTest();
    return 0;
}