#include "ALF_jit.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>

char *ALF_jit_error = "";

ALF_jit_buf *ALF_jit_init(void){
	ALF_jit_buf *handler = malloc(sizeof(ALF_jit_buf *));
	handler->position = 0;
	handler->state = 0;
	if(handler != NULL){
		#ifdef _WIN32
			DWORD type = MEM_RESERVE | MEM_COMMIT;
			handler->code = (uint8_t *)VirtualAlloc(NULL, ALF_PAGE_SIZE(), type, PAGE_READWRITE);
		#else
			int prot = PROT_READ | PROT_WRITE;
			int flags = MAP_ANONYMOUS | MAP_PRIVATE;
			handler->code = (uint8_t *)mmap(NULL, ALF_PAGE_SIZE(), prot, flags, -1, 0);
		#endif

		if(handler->code == NULL){
			ALF_jit_error = "ALF_jit_init(): Can't init. Couldn't allocate memory for instructions.";
		}
	}
	else{
		ALF_jit_error = "ALF_jit_init(): Can't init. The malloc returned NULL.";
	}
    return handler;
}

uint64_t ALF_jit_get_avaible_size(ALF_jit_buf *handler){
	return ALF_PAGE_SIZE() - sizeof(uint64_t) - sizeof(uint8_t) - handler->position*sizeof(uint8_t);
}

int ALF_jit_instruction(ALF_jit_buf *handler, uint64_t size, uint64_t ins){
	if (handler->state & 0x1){
		ALF_jit_error = "ALF_jit_instruction(): JIT buffer is finalized. Can't write on it.";
		return 1;
	}
	if(ALF_jit_get_avaible_size(handler) < size){
		ALF_jit_error = "ALF_jit_instruction(): Input data is bigger than free space.";
		return 2;
	}
    for (int64_t i = size - 1; i >= 0; i--){
        handler->code[handler->position++] = (ins >> (i * 8)) & 0xff;
    }
    return 0;
}

int ALF_jit_immediate(ALF_jit_buf *handler, uint64_t size, const void *value){
	if (handler->state & 0x1){
		ALF_jit_error = "ALF_jit_immediate(): JIT buffer is finalized. Can't write on it.";
		return 1;
	}
	if(ALF_jit_get_avaible_size(handler) < size){
		ALF_jit_error = "ALF_jit_immediate(): Input data is bigger than free space.";
		return 2;
	}
    memcpy(handler->code + handler->position, value, size);
    handler->position += size;
    return 0;
}

int ALF_jit_finalize(ALF_jit_buf *handler){
	if (handler->state & 0x1){
		ALF_jit_error = "ALF_jit_finalize(): JIT buffer was already finalized.";
		return 1;
	}

	#ifdef _WIN32
		DWORD old;
		VirtualProtect(handler->code, ALF_PAGE_SIZE(), PAGE_EXECUTE_READ, &old);
	#else
		mprotect(handler->code, ALF_PAGE_SIZE(), PROT_READ | PROT_EXEC);
	#endif
	handler->state |= 0x1;
	return 0;
}

int ALF_jit_free(ALF_jit_buf *handler){
	int retVal = 0;
	#ifdef _WIN32
		retVal = !VirtualFree(handler->code, 0, MEM_RELEASE);
		if (retVal) {
			ALF_jit_error = GetLastError();
		}
	#else
		if (munmap(handler->code, ALF_PAGE_SIZE())) {
			retVal = errno;
			ALF_jit_error = "ALF_jit_free(): Couldn't unmap the memory allocated";
		}
	#endif
	// free(handler); // FIXME: Throws error on windows.
	return retVal;
}

char *ALF_jit_get_error(void){
	return ALF_jit_error;
}

#ifdef _WIN32
	uint64_t ALF_PAGE_SIZE(void){
		SYSTEM_INFO system_info;
		GetSystemInfo(&system_info);
		return system_info.dwPageSize;
	}
#endif
