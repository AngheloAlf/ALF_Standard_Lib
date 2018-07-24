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
	ALF_printfColoredBlock(0, 0);
	ALF_printfColoredBlock(1, 0);
	ALF_printfColoredBlock(2, 0);
	ALF_printfColoredBlock(3, 0);
	ALF_printfColoredBlock(4, 0);
	ALF_printfColoredBlock(5, 0);
	ALF_printfColoredBlock(6, 0);
	ALF_printfColoredBlock(7, 0);

	printf("\n");

	ALF_printfColoredBlock(0, 1);
	ALF_printfColoredBlock(1, 1);
	ALF_printfColoredBlock(2, 1);
	ALF_printfColoredBlock(3, 1);
	ALF_printfColoredBlock(4, 1);
	ALF_printfColoredBlock(5, 1);
	ALF_printfColoredBlock(6, 1);
	ALF_printfColoredBlock(7, 1);

	printf("\n");

	ALF_printfColoredBlock(8, 1);
	ALF_printfColoredBlock(9, 1);
	ALF_printfColoredBlock(10, 1);
	ALF_printfColoredBlock(11, 1);
	ALF_printfColoredBlock(12, 1);
	ALF_printfColoredBlock(13, 1);
	ALF_printfColoredBlock(14, 1);
	ALF_printfColoredBlock(15, 1);

	printf("\n");
}

int main(int argc, char *argv[]) {
	raw_input_test();
	puthex_test();
	printfColoredBlock_test();

	ALF_raw_input("ENTER");
	return 0;
}