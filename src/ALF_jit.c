#include "ALF_jit.h"

char *ALF_jit_error = "";

ALF_jit_buf *ALF_jit_init(void){
	ALF_jit_buf *handler = malloc(sizeof(ALF_jit_buf *));
	#ifdef _WIN32
		DWORD type = MEM_RESERVE | MEM_COMMIT;
		handler->code = (uint8_t *)VirtualAlloc(NULL, ALF_PAGE_SIZE, type, PAGE_READWRITE);
	#elif defined(__unix__)
		int prot = PROT_READ | PROT_WRITE;
		int flags = MAP_ANONYMOUS | MAP_PRIVATE;
		handler->code = (uint8_t *)mmap(NULL, ALF_PAGE_SIZE, prot, flags, -1, 0);
	#else
		handler = NULL;
		ALF_jit_error = "System not recognized.";
	#endif
    return handler;
}

uint64_t ALF_jit_get_avaible_size(ALF_jit_buf *handler){
	return ALF_PAGE_SIZE - sizeof(uint64_t) - sizeof(uint8_t) - handler->position*sizeof(uint8_t);
}

int ALF_jit_instruction(ALF_jit_buf *handler, int size, uint64_t ins){
	if (handler->state & 0x1){
		ALF_jit_error = "JIT buffer is finalized. Can't write on it.";
		return 1;
	}
	if(ALF_jit_get_avaible_size(handler) < size){
		ALF_jit_error = "Input data is bigger than free space.";
		return 2;
	}
    for (int i = size - 1; i >= 0; i--){
        handler->code[handler->position++] = (ins >> (i * 8)) & 0xff;
    }
    return 0;
}

int ALF_jit_immediate(ALF_jit_buf *handler, int size, const void *value){
	if (handler->state & 0x1){
		ALF_jit_error = "JIT buffer is finalized. Can't write on it.";
		return 1;
	}
	if(ALF_jit_get_avaible_size(handler) < size){
		ALF_jit_error = "Input data is bigger than free space.";
		return 2;
	}
    memcpy(handler->code + handler->position, value, size);
    handler->position += size;
    return 0;
}

int ALF_jit_finalize(ALF_jit_buf *handler){
	if (handler->state & 0x1){
		ALF_jit_error = "JIT buffer can already be executed.";
		return 1;
	}

	#ifdef _WIN32
		DWORD old;
		VirtualProtect(handler->code, sizeof(handler->code), PAGE_EXECUTE_READ, &old);
	#elif defined(__unix__)
		mprotect(handler->code, ALF_PAGE_SIZE, PROT_READ | PROT_EXEC);
	#else
		ALF_jit_error = "System not recognized.";
		return -1;
	#endif
	handler->state |= 0x1;
	return 0;
}

void ALF_jit_free(ALF_jit_buf *handler){
	#ifdef _WIN32
		VirtualFree(handler->code, 0, MEM_RELEASE);
	#elif defined(__unix__)
		munmap(handler->code, ALF_PAGE_SIZE);
	#else
		return;
	#endif
	free(handler);
	// handler->state |= 0x2;
}

char *ALF_jit_get_error(void){
	return ALF_jit_error;
}
