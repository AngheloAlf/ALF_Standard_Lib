/** \file ALF_jit.h
* A simple cross-platform wraper to use JIT recompilation.
**/

#ifndef ALF_jit_h
#define ALF_jit_h

#include "ALF_common.h"

#include <stdint.h>


#ifdef __cplusplus
extern "C"{

#include <string>
#endif

#ifdef _WIN32
#	include <windows.h>
#else
#	include <unistd.h>
#	include <sys/mman.h>
#endif

typedef struct {
    uint64_t position;
    /**
	 * Posible states:

	 * 0x0: Normal. Data can be inserted.

	 * 0x1: Ready for execution.
    **/
    uint8_t state;
    uint8_t *code;
} ALF_jit_buf;


/// Creates a buffer for use as a JIT.
/**
 * 
**/
ALF_jit_buf *ALF_jit_init(void);

/// Returns the aviable size for code.
/**
 * 
**/
uint64_t ALF_jit_getAvaibleSize(ALF_jit_buf *handler);

/// Inserts a instruction in the code.
/**
 * 
**/
int ALF_jit_addInstruction(ALF_jit_buf *handler, uint64_t size, uint64_t ins);

/// Inserts an immediate (number) in the code.
/**
 * 
**/
int ALF_jit_addImmediate(ALF_jit_buf *handler, uint64_t size, const void *value);

/// Prepares the code to be executed.
/**
 * 
**/
int ALF_jit_finalize(ALF_jit_buf *handler);

/// Free the memory.
/**
 * 
**/
int ALF_jit_free(ALF_jit_buf *handler);

/// Returns the last error.
/**
 * 
**/
char *ALF_jit_getError(void);


uint64_t ALF_jit_pageSize(void);



#ifdef __cplusplus
}


namespace ALF{
    namespace JIT{
        class JIT{
        public:
            JIT(void){
                jitObj = ALF_jit_init();
            }
            ~JIT(void){
                ALF_jit_free(jitObj);
            }

            uint64_t getAvaibleSize(void){
                return ALF_jit_getAvaibleSize(jitObj);
            }

            int addInstruction(uint64_t size, uint64_t ins){
                return ALF_jit_addInstruction(jitObj, size, ins);
            }

            int addImmediate(uint64_t size, const void *value){
                return ALF_jit_addImmediate(jitObj, size, value);
            }

            int finalize(void){
                return ALF_jit_finalize(jitObj);
            }

        private:
            ALF_jit_buf *jitObj;
        };

        std::string getError(void){
            return std:string(ALF_jit_getError());
        }

        uint64_t pageSize(void){
            return ALF_jit_pageSize();
        }
    }
}

#endif

#endif /* ALF_jit_h */

