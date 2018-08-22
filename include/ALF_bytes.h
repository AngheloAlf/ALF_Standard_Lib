/** \file ALF_bytes.h
* A simple structure for storing bytes.
**/

#ifndef ALF_bytes_h
#define ALF_bytes_h

#include "ALF_common.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef struct{
    char *bytes;
    long size;
} ALF_bytes;

/** Object initializer.
 * Params:

 * - const char *bytes: The bytes that will be stored.

 * - long size: The size of the stored bytes. If the bytes's size are greater than this param, it will be truncated.

 * Return value: The object.
**/
ALF_bytes *ALF_bytes_init(const char *bytes, long size);


/** Object destroyer.
 * Params:

 * - ALF_bytes *bytesObj: The object to be freed.
**/
void ALF_bytes_free(ALF_bytes *bytesObj);

/// Return the size of the bytes.
long ALF_bytes_getSize(ALF_bytes *bytesObj);

/// Return the bytes.
const char *ALF_bytes_getBytes(ALF_bytes *bytesObj);

/// Set a new set of bytes, deleting the old one.
void ALF_bytes_setBytes(ALF_bytes *bytesObj, const char *bytes, long size);


#ifdef __cplusplus
}

namespace ALF{
    namespace bytes{
        /// C++ class wrapper.
        class Bytes{
        public:
            Bytes(const char *bytes, long size){
                bytesObj = ALF_bytes_init(bytes, size);
            }
            ~Bytes(){
                ALF_bytes_free(bytesObj);
            }

            long getSize(){
                return ALF_bytes_getSize(bytesObj);
            }

            const char *getBytes(){
                return ALF_bytes_getBytes(bytesObj);
            }

            void setBytes(const char *bytes, long size){
                ALF_bytes_setBytes(bytesObj, bytes, size);
            }

        private:
            ALF_bytes *bytesObj;
        };
    }
}


#endif


#endif /* ALF_bytes_h */
