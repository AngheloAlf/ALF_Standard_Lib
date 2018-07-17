#include "ALF_std.h"
#include <stdio.h>

int main(int argc, char *argv[]){
	char* mensaje = ALF_raw_input("Ingrese un mensaje: ");
	printf("Su mensaje es: %s\n", mensaje);

	return 0;
}

int wmain( int argc, wchar_t *argv[ ], wchar_t *envp[ ] ){
	return main(argc, argv);
}
