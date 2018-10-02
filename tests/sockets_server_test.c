#include "ALF_std.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
    ALF_socket *server = ALF_sockets_init(ALF_SOCKETS_TYPE_TCP, NULL, 8888);
    if(server == NULL){
        printf("%s\n", ALF_sockets_getLastErrorMsg());
        return ALF_sockets_getLastError();
    }
    fprintf(stderr, "Socket created.\n");

    if(ALF_sockets_bind(server)){
        printf("%s\n", ALF_sockets_getLastErrorMsg());
        return ALF_sockets_getLastError();
    }
    fprintf(stderr, "Bind done.\n");

    if(ALF_sockets_listen(server)){
        printf("%s\n", ALF_sockets_getLastErrorMsg());
        return ALF_sockets_getLastError();
    }
    fprintf(stderr, "Listen done.\n");

    fprintf(stderr, "Waiting connections...\n");

    ALF_socket *client = ALF_sockets_accept(server);
    if(client == NULL){
        printf("%s\n", ALF_sockets_getLastErrorMsg());
        return ALF_sockets_getLastError();
    }
    fprintf(stderr, "Client accepted.\n");

    size_t msgSize = 3;
    char msg[msgSize + 1];

    ssize_t asd = ALF_sockets_recv(client, msg, msgSize, NULL);
    while(asd > 0){
        fprintf(stderr, "recv: %s\n", msg);
        asd = ALF_sockets_send(client, msg, 0, NULL);
        if(asd < 0){
            printf("%s\n", ALF_sockets_getLastErrorMsg());
            // return ALF_sockets_getLastError();
            break;
        }
        while(ALF_sockets_recvNonBlocking(client, msg, msgSize, NULL) > 0){
            fprintf(stderr, "\t%s\n", msg);
            asd = ALF_sockets_send(client, msg, 0, NULL);
            if(asd < 0){
                printf("%s\n", ALF_sockets_getLastErrorMsg());
                // return ALF_sockets_getLastError();
                break;
            }
        }
       asd = ALF_sockets_recv(client, msg, msgSize, NULL);
    }
    printf("%s\n", ALF_sockets_getLastErrorMsg());

    fprintf(stderr, "Connection ended.\n");

    ALF_sockets_free(client);
    ALF_sockets_free(server);

    return 0;
}
