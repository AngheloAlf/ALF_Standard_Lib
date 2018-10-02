#include "ALF_std.h"
#include <stdlib.h>
#include <stdio.h>

#include <time.h>

#include<string.h>

int main(){
    ALF_socket *server = ALF_sockets_init(ALF_SOCKETS_TYPE_TCP, "127.0.0.1", 8888);
    if(server == NULL){
        printf("%s\n", ALF_sockets_getLastErrorMsg());
        return ALF_sockets_getLastError();
    }
    printf("Socket created.\n");

    if(ALF_sockets_connect(server)){
        printf("%s\n", ALF_sockets_getLastErrorMsg());
        return ALF_sockets_getLastError();
    }
    printf("Connect done.\n");

    ssize_t recv_retval, auxSize = 1024;
    char *msg, aux[auxSize+1];
    msg = ALF_IO_raw_input("Message: ");

    do{
        if(ALF_sockets_send(server, msg, 0, NULL) < 0){
            printf("%s\n", ALF_sockets_getLastErrorMsg());
            break;
        }
        free(msg);

        recv_retval = ALF_sockets_recv(server, aux, auxSize, NULL);
        if(recv_retval < 0){
            printf("%s\n", ALF_sockets_getLastErrorMsg());
            break;
        }
        printf("recv: %s\n", aux);
        
        msg = ALF_IO_raw_input("Message: ");
    } while(strcmp(msg, ""));

    printf("Connection ended.\n");
    ALF_sockets_free(server);

    return 0;
}
