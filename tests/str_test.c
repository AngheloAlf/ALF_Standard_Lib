#include "ALF_std.h"
#include <stdio.h>

int main(){
    char *example = ALF_STR_changeExtension("example.txt", "asdf", 4);
    printf("%s\n", example);
    return 0;
}