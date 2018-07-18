#include "ALF_std_extra.h"

#include <stdio.h>

int main(int argc, char *argv[]){
    if(argc < 3){
        printf("Usage: dso_test lib_name function_name(must recieve an char* and return char*)\n");
        return 1;
    }
    // ALF_DSO_handl so_file = ALF_DSO_load_file("../out/dynamic/libALF_std.so");
    ALF_DSO_handl so_file = ALF_DSO_load_file(argv[1]);
    if(!so_file){
        printf("%s\n", ALF_DSO_get_error());
    }
    // char* (*raw_input)(char *) = ALF_DSO_load_function(so_file, "ALF_raw_input");
    char* (*raw_input)(char *) = ALF_DSO_load_function(so_file, argv[2]);
    if(!raw_input){
        printf("%s\n", ALF_DSO_get_error());
    }
    char *wea = (*raw_input)("char *");
    printf("char *: %s\n", wea);
    if(ALF_DSO_close_file(so_file)){
        printf("%s\n", ALF_DSO_get_error());
    }

    return 0;
}
