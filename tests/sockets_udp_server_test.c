#include <arpa/inet.h>
#include <stdio.h>

#include "ALF_std.h"

int main() {
    int SERVER_PORT = 8877;

    ALF_socket *server = ALF_sockets_init(ALF_SOCKETS_TYPE_UDP, NULL, SERVER_PORT);
    if(server == NULL){
        printf("%s\n", ALF_sockets_getLastErrorMsg());
        return ALF_sockets_getLastError();
    }
    printf("Socket created.\n");
    if(ALF_sockets_bind(server) < 0){
        printf("%s\n", ALF_sockets_getLastErrorMsg());
        return ALF_sockets_getLastError();
    }
    printf("Socket binded.\n");

    ALF_socket *destinatary = ALF_sockets_createDestObj(ALF_SOCKETS_TYPE_UDP);

    size_t bufferSize = 1024;
    char buffer[bufferSize + 1];
    while(1){
        int len = ALF_sockets_recv(destinatary, buffer, bufferSize, server);

        if(len < 0){
            printf("%s\n", ALF_sockets_getLastErrorMsg());
            break;
        }

        buffer[len] = '\0';
        printf("received: '%s' from client %s\n", buffer, inet_ntoa(destinatary->addr->sin_addr));

        if(ALF_sockets_send(destinatary, buffer, len, server) < 0){
            printf("%s\n", ALF_sockets_getLastErrorMsg());
            break;
        }
    }

    ALF_sockets_free(destinatary);
    ALF_sockets_free(server);

    return 0;
}
