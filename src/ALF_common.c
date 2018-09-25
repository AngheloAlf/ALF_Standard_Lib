#include "ALF_std/ALF_common.h"
#include <string.h>

void *ALF_allocAndCopy(const void *input_data, size_t size){
    void *output_pointer = malloc(size);
    if(output_pointer == NULL){
        return NULL;
    }
    memcpy(output_pointer, input_data, size);
    return output_pointer;
}
