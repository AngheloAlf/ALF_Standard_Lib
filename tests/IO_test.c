#include "ALF_std.h"
#include <stdio.h>

void raw_input_test(void) {
	char* mensaje = ALF_raw_input("Ingrese un mensaje: ");
	printf("Su mensaje es: %s\n", mensaje);
}

void puthex_test(void) {
	ALF_puthex(5);
	printf("\n");
	ALF_puthex(83);
	printf("\n");
	ALF_puthex(0x25);
	printf("\n");
	ALF_puthex(0x13);
	printf("\n");
	ALF_puthex(0x6);
	printf("\n");
	ALF_puthex(13);
	printf("\n");
}

void printfColoredBlock_test(void) {

	for(int i = 0; i < 256; i++){
		if(i % 8 == 0){
			printf("\n");
		}
		ALF_printfColoredBlock(i, 0);
	}

	printf("\n");
	for(int i = 0; i < 256; i++){
		if(i % 8 == 0){
			printf("\n");
		}
		ALF_printfColoredBlock(i, 1);
	}

	printf("\n");

	/*
	int a = 31;
	int b = 44;

	printf("\033[%i;%im%i%i"ALF_ANSI_COLOR_RESET"\n", a, b, a, b);
	*/
}

int main(int argc, char *argv[]) {
	// raw_input_test();
	// puthex_test();
	printfColoredBlock_test();

	ALF_raw_input("ENTER ");
	return 0;
}
