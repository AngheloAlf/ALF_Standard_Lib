#include "ALF_IO.h"

char *ALF_raw_input(const char *outMessage){
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

void ALF_puthex(unsigned char character){
    if(character < 0x10){
        printf("0");
    }
    printf("%x", character);
}

void ALF_printfColoredBlock(unsigned char character, int withNumber){
    if(withNumber){
        printf("\033[%im%i " ALF_ANSI_COLOR_RESET, character + 40, character);
    }
    else{
        printf("\033[%im  " ALF_ANSI_COLOR_RESET, character + 40);
    }
}
