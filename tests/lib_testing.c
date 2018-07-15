#include "ALF_std_extra.h"


int main(){
/*	
	char *wea = ALF_raw_input("Ingrese un mensaje: ");
	printf("Su mensaje es: %s\n", wea);
*/

	ALF_DSO_handl so_file = ALF_DSO_load_file("../dynamic/libALF_std.so");
	char* (*raw_input)(const char *) = ALF_DSO_load_function(so_file, "ALF_raw_input");
	char *wea = (*raw_input)("wea: ");
	printf("wea: %s\n", wea);

	return 0;
}
