#include "ALF_bytes.h"

#include <stdlib.h>
#include <string.h>

ALF_bytes *ALF_bytes_init(const char *bytes, long size){
    ALF_bytes *this = (ALF_bytes *)malloc(sizeof(ALF_bytes));
    this->size = size;
    if(bytes && size > 0){
        this->bytes = (char *)malloc(sizeof(char) * size);
        memcpy(this->bytes, bytes, size);
    }
    return this;
}

void ALF_bytes_free(ALF_bytes *this){
    free(this->bytes);
    free(this);
}

long ALF_bytes_getSize(ALF_bytes *this){
    return this->size;
}

const char *ALF_bytes_getBytes(ALF_bytes *this){
    return this->bytes;
}

void ALF_bytes_setBytes(ALF_bytes *this, const char *bytes, long size){
    if(this->bytes){
        free(this->bytes);
    }
    this->size = size;
    if(bytes && size > 0){
        this->bytes = (char *)malloc(sizeof(char) * size);
        memcpy(this->bytes, bytes, size);
    }
}
