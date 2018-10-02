#include "ALF_std.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
    ALF_socket *server = ALF_sockets_init(ALF_SOCKETS_TYPE_TCP, NULL, 8888);
    if(server == NULL){
        printf("%s\n", ALF_sockets_getLastErrorMsg());
        return ALF_sockets_getLastError();
    }
    printf("Socket created.\n");

    if(ALF_sockets_bind(server)){
        printf("%s\n", ALF_sockets_getLastErrorMsg());
        return ALF_sockets_getLastError();
    }
    printf("Bind done.\n");

    if(ALF_sockets_listen(server)){
        printf("%s\n", ALF_sockets_getLastErrorMsg());
        return ALF_sockets_getLastError();
    }
    printf("Listen done.\n");

    printf("Waiting connections...\n");

    ALF_socket *client = ALF_sockets_accept(server);
    if(client == NULL){
        printf("%s\n", ALF_sockets_getLastErrorMsg());
        return ALF_sockets_getLastError();
    }
    printf("Client accepted.\n");

    size_t msgSize = 1024;
    char msg[msgSize + 1];

    ssize_t asd = ALF_sockets_recv(client, msg, msgSize, NULL);
    while(asd > 0){
        fprintf(stderr, "recv: %s\n", msg);
        asd = ALF_sockets_send(client, msg, 0, NULL);
        if(asd < 0){
            printf("%s\n", ALF_sockets_getLastErrorMsg());
            break;
        }
       asd = ALF_sockets_recv(client, msg, msgSize, NULL);
    }
    printf("%s\n", ALF_sockets_getLastErrorMsg());

    printf("Connection ended.\n");

    ALF_sockets_free(client);
    ALF_sockets_free(server);

    return 0;
}
