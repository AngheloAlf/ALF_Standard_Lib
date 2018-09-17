#include "ALF_std/ALF_bytes.h"

#include <stdlib.h>
#include <string.h>

ALF_bytes *ALF_bytes_init(const uint8_t *bytes, size_t size){
    if(size > 0){
        ALF_bytes *bytesObj = (ALF_bytes *)malloc(sizeof(ALF_bytes));
        if(bytesObj != NULL){
            bytesObj->size = size;
            bytesObj->bytes = NULL;
            if(bytes){
                bytesObj->bytes = (uint8_t *)malloc(sizeof(uint8_t) * size);
                if(bytesObj->bytes == NULL){
                    free(bytesObj);
                    return NULL;
                }
                memcpy(bytesObj->bytes, bytes, size);
            }
            else{
                bytesObj->bytes = (uint8_t *)calloc(size, sizeof(uint8_t));
                if(bytesObj->bytes == NULL){
                    free(bytesObj);
                    return NULL;
                }
            }
        }
        return bytesObj;
    }
    else{
        return NULL;
    }
}

void ALF_bytes_free(ALF_bytes *bytesObj){
    free(bytesObj->bytes);
    free(bytesObj);
}

size_t ALF_bytes_getSize(ALF_bytes *bytesObj){
    return bytesObj->size;
}

uint8_t *ALF_bytes_getBytes(ALF_bytes *bytesObj){
    uint8_t *aux = malloc(sizeof(uint8_t) * bytesObj->size);
    return memcpy(aux, bytesObj->bytes, bytesObj->size);
}

const uint8_t *ALF_bytes_seeBytes(ALF_bytes *bytesObj){
    return bytesObj->bytes;
}

bool ALF_bytes_setBytes(ALF_bytes *bytesObj, const uint8_t *bytes, size_t size){
    if(size == bytesObj->size){
        if(bytes){
            memcpy(bytesObj->bytes, bytes, size);
        }
        else{
            for(size_t i = 0; i < size; i++){
                bytesObj->bytes[i] = 0;
            }
        }
    }
    else if(size > 0){
        uint8_t *aux = realloc(bytesObj->bytes, sizeof(uint8_t) * size);
        if(aux == NULL){
            return false;
        }
        bytesObj->bytes = aux;
        bytesObj->size = size;
        if(bytes){
            memcpy(bytesObj->bytes, bytes, size);
        }
        else{
            for(size_t i = 0; i < size; i++){
                bytesObj->bytes[i] = 0;
            }
        }
    }
    else{
        return false;
    }
    return true;
}

bool ALF_bytes_setSize(ALF_bytes *bytesObj, size_t size){
    if(size <= 0){
        return false;
    }
    uint8_t *aux = (uint8_t *)realloc(bytesObj->bytes,sizeof(uint8_t) * size);
    if(aux == NULL){
        return false;
    }
    bytesObj->bytes = aux;
    if(size > bytesObj->size){
        for(size_t i = bytesObj->size; i < size; i++){
            bytesObj->bytes[i] = 0;
        }
    }
    bytesObj->size = size;

    return true;
}

uint8_t ALF_bytes_getByte(ALF_bytes *bytesObj, size_t position){
    if(position >= bytesObj->size){
        return bytesObj->bytes[bytesObj->size - 1];
    }
    return bytesObj->bytes[position];
}

void ALF_bytes_changeByte(ALF_bytes *bytesObj, size_t position, uint8_t newByte){
    if(position >= bytesObj->size){
        bytesObj->bytes[bytesObj->size - 1] = newByte;
    }
    bytesObj->bytes[position] = newByte;
}
