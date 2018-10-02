#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

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

	int len = ALF_sockets_send(server, data_to_send, server);
	if(len < 0){
        printf("%s\n", ALF_sockets_getLastErrorMsg());
		return ALF_sockets_getLastError();
	}

	printf("%i\n", len);

	char buffer[100];
	if(ALF_sockets_recv(server, len, buffer, server) < 0){
        printf("%s\n", ALF_sockets_getLastErrorMsg());
		return ALF_sockets_getLastError();
	}

	printf("recieved: '%s'\n", buffer);

	ALF_sockets_free(server);
	return 0;
}
