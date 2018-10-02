#include "ALF_std.h"
#include <stdlib.h>
#include <stdio.h>

#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write

int main(){

    ALF_socket *server = ALF_sockets_init(ALF_SOCKETS_TYPE_TCP, NULL, 8888);
    if(server == NULL){
        fprintf(stderr, "Could not create socket.\n");
        perror("ERROR");
        return 1;
    }
    fprintf(stderr, "Socket created.\n");

    if(ALF_sockets_bind(server)){
        fprintf(stderr, "Bind failed.\n");
        perror("ERROR");
        return 1;
    }
    fprintf(stderr, "Bind done.\n");

    if(ALF_sockets_listen(server)){
        fprintf(stderr, "Listen failed.\n");
        perror("ERROR");
        return 1;
    }
    fprintf(stderr, "Listen done.\n");

    fprintf(stderr, "Waiting connections...\n");

    ALF_socket *client = ALF_sockets_accept(server);
    if(client == NULL){
        fprintf(stderr, "Accept failed.\n");
        perror("ERROR");
        return 1;
    }
    fprintf(stderr, "Client accepted.\n");

    size_t msgSize = 3;
    char msg[msgSize + 1];

    ssize_t asd = ALF_sockets_recv(client, msgSize, msg, NULL);
    while(asd > 0){
        fprintf(stderr, "recv: %s\n", msg);
        asd = ALF_sockets_send(client, msg, NULL);
        if(asd < 0){
            fprintf(stderr, "Couldn't send.\n");
            perror("ERROR");
            break;
        }
        while(ALF_sockets_recvNonBlocking(client, msgSize, msg, NULL) > 0){
            fprintf(stderr, "\t%s\n", msg);
            asd = ALF_sockets_send(client, msg, NULL);
            if(asd < 0){
                fprintf(stderr, "Couldn't send.\n");
                perror("ERROR");
                break;
            }
        }
       asd = ALF_sockets_recv(client, msgSize, msg, NULL);
    }

    fprintf(stderr, "Connection ended.\n");

    ALF_sockets_free(client);
    ALF_sockets_free(server);


    /*
    int socket_desc , client_sock , c , read_size;
    struct sockaddr_in server , client;
    char client_message[2000];
     
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        fprintf(stderr, "Could not create socket");
    }
    puts("Socket created");
     
    //Prepare the sockaddr_in structure
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons( 8888 );
     
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");
     
    //Listen
    listen(socket_desc , 3);
     
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
     
    //accept connection from an incoming client
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
    puts("Connection accepted");
     
    //Receive a message from client
    while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 )
    {
        fprintf(stderr, "%i\n", read_size);
        //Send the message back to client
        write(client_sock , client_message , strlen(client_message));
    }
     
    if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }
    
     */
    return 0;
}
