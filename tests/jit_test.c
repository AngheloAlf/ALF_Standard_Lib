#include "ALF_std.h"
#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[]){
	long number = 15;
	uint64_t instruction = 0;
	#ifdef __unix__
		instruction = 0x4889f8; // mov    rax,rdi
	#elif _WIN32
		instruction = 0x4889C8; // mov    rax,rcx
	#else
		ALF_raw_input("Test not made for this CPU arquitecture/OS\n");
		return -1;
	#endif

	ALF_jit_buf *buffer = ALF_jit_init();
	if(buffer == NULL){
		printf("ERROR: %s\n", ALF_jit_get_error());

		ALF_raw_input("Press enter to exit ");
		return -1;
	}

	if(ALF_jit_instruction(buffer, 3, instruction)){
		printf("ERROR: %s\n", ALF_jit_get_error());

		ALF_raw_input("Press enter to exit ");
		return -1;
	}

	if(ALF_jit_instruction(buffer, 1, 0xc3)){ // ret
		printf("ERROR: %s\n", ALF_jit_get_error());

		ALF_raw_input("Press enter to exit ");
		return -1;
	}
	if(ALF_jit_finalize(buffer)){
		printf("ERROR: %s\n", ALF_jit_get_error());

		ALF_raw_input("Press enter to exit ");
		return -1;
	}

	long (*dummy)(long) = (void *)buffer->code;

	printf("The input number was %ld and the result is %ld.\n", number, dummy(number));


	ALF_jit_free(buffer);

	ALF_raw_input("Press enter to exit ");

	return 0;
}
