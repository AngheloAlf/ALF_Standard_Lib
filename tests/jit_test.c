#include "ALF_std.h"
#include <stdio.h>

// TODO: Fix this.
int main(int argc, char *argv[]){
	#ifdef __unix__
		ALF_jit_buf *buffer = ALF_jit_init();
		if(ALF_jit_instruction(buffer, 3, 0x4889f8)){ // mov   %rdi, %rax
			printf("ERROR: %s\n", ALF_jit_get_error());

			getchar();
			return -1;
		}

		// long number = 3;

	    // asmbuf_ins(buf, 2, 0x48bf);         // mov   operand, %rdi
		// asmbuf_immediate(buf, 8, &number);
	    
		if(ALF_jit_instruction(buffer, 1, 0xc3)){ // ret
			printf("ERROR: %s\n", ALF_jit_get_error());

			getchar();
			return -1;
		} 
		if(ALF_jit_finalize(buffer)){
			printf("ERROR: %s\n", ALF_jit_get_error());

			getchar();
			return -1;
		}

		long (*dummy)(long) = (void *)buffer->code;

		printf("%ld\n", dummy(15));


		ALF_jit_free(buffer);
	#else
		printf("Test not made for this CPU arquitecture/OS\n");
		getchar();
		return -1;
	#endif

	getchar();

	return 0;
}