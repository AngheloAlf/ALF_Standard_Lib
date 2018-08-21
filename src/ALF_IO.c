#include "ALF_IO.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char *ALF_IO_raw_input(const char *outMessage){
    printf("%s", outMessage);

    int inSize = 32;
    char *inData = malloc(sizeof(char)*inSize);
    if(!fgets(inData, inSize, stdin)){ // No se pudo leer
        free(inData);
        return NULL;
    }

    size_t len = strlen(inData);
    if(inData[len-1] == '\n'){ // String completo
        inData[len-1] = '\0'; // Eliminando el salto de linea
        inData = realloc(inData, sizeof(char)*len); // Liberando memoria no necesaria.
        return inData;
    }
    else{ // No se encontro el salto de linea. A seguir leyendo!
        char *auxData = malloc(sizeof(char)*inSize*2); // String mas grande
        strcpy(auxData, inData); // Copiando datos al string final
        while(fgets(inData, inSize, stdin)){ // Lee datos de stdin
            strcat(auxData, inData); // Se concatena al string grande
            len = strlen(auxData);
            if(auxData[len-1] == '\n'){ // Revisando si tenemos toodo el string
                auxData[len-1] = '\0'; // Elimina salto de linea
                free(inData);
                auxData = realloc(auxData, sizeof(char)*len); // Liberando memoria no necesaria.
                return auxData; // Yay!
            }
            auxData = realloc(auxData, sizeof(char)*(len + inSize)); //String mas grande!
        }
        free(inData);
        free(auxData);
        return NULL; // En caso de error
    }
}

void ALF_IO_puthex(unsigned char character){
    if(character < 0x10){
        printf("0");
    }
    printf("%x", character);
}

void ALF_IO_printfColoredBlock(unsigned char character, char withNumber){
    unsigned char color = 0, param = character;
    character &= 0x0F;
    if(character >= 0 && character <= 7){
        color = character + 40;
    }
    else if(character >= 8 && character <= 15){
        color = character - 8 + 100;
    }
    if(withNumber){
        if(param > 0x0F){
            printf("\033[%im%x" ALF_ANSI_COLOR_RESET, color, param);
        }
        else{
            printf("\033[%im %x" ALF_ANSI_COLOR_RESET, color, param);
        }
    }
    else{
        printf("\033[%im  " ALF_ANSI_COLOR_RESET, color);
    }
}

