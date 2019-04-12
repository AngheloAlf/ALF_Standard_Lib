#include <stdio.h>
#include "ALF_std.h"

int main() {
    const char* server_name = "127.0.0.1";
    const int server_port = 8877;

    const char* data_to_send = "UDP example!";

    ALF_socket *server = ALF_sockets_init(ALF_SOCKETS_TYPE_UDP, server_name, server_port);
    if(server == NULL){
        printf("%s\n", ALF_sockets_getLastErrorMsg());
        return 1;
    }
    printf("Socket created.\n");

    int len = ALF_sockets_send(server, data_to_send, 0, server);
    if(len < 0){
        printf("%s\n", ALF_sockets_getLastErrorMsg());
        return ALF_sockets_getLastError();
    }
    else{
        size_t bufferSize = 1024;
        char buffer[bufferSize + 1];
        if(ALF_sockets_recv(server, buffer, len, server) < 0){
            printf("%s\n", ALF_sockets_getLastErrorMsg());
        }
        printf("recieved: '%s'\n", buffer);
    }

    ALF_sockets_free(server);
    return 0;
}
