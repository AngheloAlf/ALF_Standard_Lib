#include "ALF_std.h"
#include <stdio.h>
#include <stdint.h>

int main(){ // int argc, char *argv[]){
    long number = 15;
    uint64_t instruction = 0;

    if (ALF_OS_isWindows()) {
        instruction = 0x4889C8; // mov    rax,rcx
    }
    else if(ALF_OS_isUnix()) {
        instruction = 0x4889f8; // mov    rax,rdi
    }
    else {
        ALF_IO_raw_input("Test not made for this CPU arquitecture/OS\n");
        return -1;
    }

    ALF_jit_buf *buffer = ALF_jit_init();
    if(buffer == NULL){
        printf("ERROR: %s\n", ALF_jit_getError());

        ALF_IO_raw_input("Press enter to exit ");
        return -1;
    }

    if(ALF_jit_addInstruction(buffer, 3, instruction)){
        printf("ERROR: %s\n", ALF_jit_getError());

        ALF_IO_raw_input("Press enter to exit ");
        return -1;
    }

    if(ALF_jit_addInstruction(buffer, 1, 0xc3)){ // ret
        printf("ERROR: %s\n", ALF_jit_getError());

        ALF_IO_raw_input("Press enter to exit ");
        return -1;
    }
    if(ALF_jit_finalize(buffer)){
        printf("ERROR: %s\n", ALF_jit_getError());

        ALF_IO_raw_input("Press enter to exit ");
        return -1;
    }

    long (*dummy)(long) = (void *)buffer->code;

    printf("The input number was %ld and the result is %ld.\n", number, dummy(number));


    if (ALF_jit_free(buffer)) {
        printf("ERROR: %s\n", ALF_jit_getError());

        ALF_IO_raw_input("Press enter to exit ");
        return -1;
    }

    ALF_IO_raw_input("Press enter to exit ");

    return 0;
}
