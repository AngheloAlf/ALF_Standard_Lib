#include "ALF_std.h"
#include <stdio.h>

#include <string.h>
#include <errno.h>

int main(){
    ALF_db *aux = ALF_db_open("example_.bin");
    if(aux == NULL){
        fprintf(stderr, "error: %s\n", strerror(errno));
        return 1;
    }
    for(int i = 0; aux->columnsName[i] != NULL; i++){
        printf("%s\n", aux->columnsName[i]);
    }
    // printf("%p\n", aux);
    ALF_db_free(aux);
    return 0;
}