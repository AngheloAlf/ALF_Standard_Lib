#include "ALF_std.h"
#include <stdlib.h>
#include <stdio.h>

#include <time.h>

#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr


int main(){
    ALF_socket *server = ALF_sockets_init(ALF_SOCKETS_TYPE_TCP, "127.0.0.1", 8888);
    if(server == NULL){
        // printf("Could not create socket.\n");
        printf("%s\n", ALF_sockets_getLastErrorMsg());
        return 1;
    }
    printf("Socket created.\n");

    if(ALF_sockets_connect(server)){
        printf("%s\n", ALF_sockets_getLastErrorMsg());
        return 1;
    }
    printf("Connect done.\n");

    ssize_t recv_retval, auxSize = 4;
    char *msg, aux[auxSize+1];
    msg = ALF_IO_raw_input("Message: ");

    do{
        if(ALF_sockets_send(server, msg, NULL) < 0){
            printf("sendBreak\n");
            printf("%s\n", ALF_sockets_getLastErrorMsg());
            break;
        }
        free(msg);

        recv_retval = ALF_sockets_recv(server, auxSize, aux, NULL);
        if(recv_retval < 0){
            printf("auxBreak: %i\n", (int)recv_retval);
            printf("%s\n", ALF_sockets_getLastErrorMsg());
            break;
        }
        printf("recv: %s\n", aux);
        // free(aux);
        struct timespec tim, tim2;
        tim.tv_sec = 0;
        tim.tv_nsec = 10000L;
        nanosleep(&tim, &tim2);
        while(ALF_sockets_recvNonBlocking(server, auxSize, aux, NULL) > 0){
            printf("\t%s\n", aux);
        }
        
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
