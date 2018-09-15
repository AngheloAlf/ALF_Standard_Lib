#include "ALF_std/ALF_bytes.h"

#include <stdlib.h>
#include <string.h>

ALF_bytes *ALF_bytes_init(const uint8_t *bytes, size_t size){
    ALF_bytes *this = (ALF_bytes *)malloc(sizeof(ALF_bytes));
    this->size = size;
    if(bytes && size > 0){
        this->bytes = (uint8_t *)malloc(sizeof(uint8_t) * size);
        memcpy(this->bytes, bytes, size);
    }
    return this;
}

void ALF_bytes_free(ALF_bytes *this){
    free(this->bytes);
    free(this);
}

size_t ALF_bytes_getSize(ALF_bytes *this){
    return this->size;
}

uint8_t *ALF_bytes_getBytes(ALF_bytes *this){
    return this->bytes;
}

void ALF_bytes_setBytes(ALF_bytes *this, const uint8_t *bytes, size_t size){
    if(this->bytes){
        free(this->bytes);
    }
    this->size = size;
    if(bytes && size > 0){
        this->bytes = (uint8_t *)malloc(sizeof(uint8_t) * size);
        memcpy(this->bytes, bytes, size);
    }
}
