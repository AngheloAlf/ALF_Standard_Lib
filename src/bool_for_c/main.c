#include <stdio.h>
#include "bool_c.h"

int main(int argc, char* argv[]){
	bool ex = argc > 2;
	bool ex2 = true;
	printf("%i, %i\n", ex, ex2);
	return 0;
}