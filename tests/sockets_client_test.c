#include "ALF_std.h"
#include <stdlib.h>
#include <stdio.h>

#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr


int main(){
    ALF_socket *server = ALF_sockets_init("127.0.0.1", 8888);
    if(server == NULL){
        printf("Could not create socket.\n");
        return 1;
    }
    printf("Socket created.\n");

    if(ALF_sockets_connect(server)){
        printf("Connect failed.\n");
        return 1;
    }
    printf("Connect done.\n");

    char *msg, aux[5];
    ssize_t recv_retval;
    msg = ALF_IO_raw_input("Message: ");

    do{
        if(ALF_sockets_send(server, msg) <= 0){
            printf("sendBreak\n");
            break;
        }
        free(msg);

        recv_retval = ALF_sockets_recv(server, 5-1, aux);
        if(recv_retval <= 0){
            printf("auxBreak: %i\n", (int)recv_retval);
            break;
        }
        printf("recv: %s\n", aux);
        // free(aux);
        
        msg = ALF_IO_raw_input("Message: ");
    } while(strcmp(msg, ""));



    printf("Connection ended.\n");
    ALF_sockets_free(server);

    /*
    int sock;
    struct sockaddr_in server;
    char message[1000] , server_reply[2000];
     
    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons( 8888 );
 
    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }
     
    puts("Connected\n");
     
    //keep communicating with server
    while(1)
    {
        printf("Enter message : ");
        scanf("%s" , message);
         
        //Send some data
        if( send(sock , message , strlen(message) , 0) < 0)
        {
            puts("Send failed");
            return 1;
        }
        
        //Receive a reply from the server
        if( recv(sock , server_reply , 2000 , 0) < 0)
        {
            puts("recv failed");
            break;
        }
        
         
        printf("Server reply :%s\n", server_reply);
    }
     
    close(sock);
    return 0;
    */
}
