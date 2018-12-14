#include "ALF_std.h"
#include <stdio.h>
#include <string.h>

void raw_input_test(void) {
    char* mensaje = ALF_IO_raw_input("Ingrese un mensaje: ");
    printf("Su mensaje es: %s\n", mensaje);
    free(mensaje);
}

void fraw_input_test(FILE *file){
    char* mensaje;
    while((mensaje = ALF_IO_fraw_input(file, "Reading from file...\n")) != NULL){
        printf("Readed: %s\n\n", mensaje);
        free(mensaje);
    }
}

void puthex_test(void) {
    ALF_IO_puthex(5);
    printf("\n");
    ALF_IO_puthex(83);
    printf("\n");
    ALF_IO_puthex(0x25);
    printf("\n");
    ALF_IO_puthex(0x13);
    printf("\n");
    ALF_IO_puthex(0x6);
    printf("\n");
    ALF_IO_puthex(13);
    printf("\n");
}

void printfColoredBlock_test(void) {

    for(int i = 0; i < 256; i++){
        if(i % 8 == 0){
            printf("\n");
        }
        ALF_IO_printfColoredBlock(i, 0);
    }

    printf("\n");
    for(int i = 0; i < 256; i++){
        if(i % 8 == 0){
            printf("\n");
        }
        ALF_IO_printfColoredBlock(i, 1);
    }

    printf("\n");

    /*
    int a = 31;
    int b = 44;

    printf("\033[%i;%im%i%i"ALF_ANSI_COLOR_RESET"\n", a, b, a, b);
    */
}

int main(int argc, char *argv[]){
    for(int i = 0; i < argc; i++){
        if(!strcmp(argv[i], "raw_input")){
            raw_input_test();
        }
        if(!strcmp(argv[i], "fraw_input")){
            FILE *file = fopen(argv[++i], "r");
            fraw_input_test(file);
            fclose(file);
        }
        if(!strcmp(argv[i], "puthex")){
            puthex_test();
        }
        if(!strcmp(argv[i], "printfColoredBlock")){
            printfColoredBlock_test();
        }
    }

    ALF_IO_raw_input("ENTER ");
    return 0;
}
