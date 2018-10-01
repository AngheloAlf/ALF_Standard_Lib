#include "ALF_std/ALF_sockets.h"

#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>

#include <errno.h>

#define MALLOC_ERROR "Couldn't allocate memory. "
#define SOCKET_CREATION_ERROR "Couldn't create socket. "
#define ALREADY_BINDED_ERROR "The socket is binded. "
#define ALREADY_LISTENING_ERROR "The socket is listening. "
#define ALREADY_CONNECTED_ERROR "The socket is connected. "
#define NOT_BINDED_ERROR "The socket is not binded. "
#define CONNECT_ERROR "The socket couldn't connect. "
#define BIND_ERROR "The socket couldn't bind. "
#define LISTEN_ERROR "The socket couldn't listen. "
#define NOT_LISTENING_ERROR "The socket is not listening. "
#define NOT_CONNECTED_ERROR "The socket is not connected. "
#define RECV_ERROR "Couldn't recive message. "
#define RECV_NB_ERROR "Couldn't recive non blocking message. "
#define SEND_ERROR "Couldn't send message. "

#define GENERIC_ERROR "GENERIC_ERROR. "


ssize_t ALF_sockets_error = 0;
char ALF_sockets_errorMsg[1024];

ALF_socket *ALF_sockets_init(const char *ip, uint16_t port){
    ALF_socket *handler = malloc(sizeof(ALF_socket));
    if(handler == NULL){
        ALF_sockets_error = -2;
        strcpy(ALF_sockets_errorMsg, MALLOC_ERROR);
        return NULL;
    }

    if((handler->addr = malloc(sizeof(struct sockaddr_in))) == NULL){
        ALF_sockets_error = -2;
        strcpy(ALF_sockets_errorMsg, MALLOC_ERROR);
        free(handler);
        return NULL;
    }

    if((handler->sock_desc = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        ALF_sockets_error = -3;
        strcpy(ALF_sockets_errorMsg, SOCKET_CREATION_ERROR);
        strcpy(ALF_sockets_errorMsg + strlen(ALF_sockets_errorMsg), strerror(errno));
        free(handler);
        return NULL;
    }

    memset(handler->addr, 0, sizeof *(handler->addr));
    handler->addr->sin_family = AF_INET;
    handler->addr->sin_addr.s_addr = INADDR_ANY;
    if(ip != NULL){
        handler->addr->sin_addr.s_addr = inet_addr(ip);
    }

    handler->addr->sin_port = htons(port);

    handler->backlog = 128; // arbitrary.
    handler->binded = false;
    handler->listening = false;
    handler->connected = false;

    return handler;
}

void ALF_sockets_free(ALF_socket *handler){
    if(handler == NULL){
        return;
    }
    shutdown(handler->sock_desc, SHUT_RDWR);
    free(handler->addr);
    free(handler);
}

void ALF_sockets_setBacklog(ALF_socket *handler, int backlog){
    handler->backlog = backlog;
}

int ALF_sockets_getBacklog(ALF_socket *handler){
    return handler->backlog;
}

int parseConnectErrors(ALF_socket *handler){
    int aux = 0;
    if(handler->binded){
        aux = -4;
        strcpy(ALF_sockets_errorMsg, ALREADY_BINDED_ERROR);
    }
    if(handler->listening){
        aux = -5;
        strcpy(ALF_sockets_errorMsg, ALREADY_LISTENING_ERROR);
    }
    if(handler->connected){
        aux = -6;
        strcpy(ALF_sockets_errorMsg, ALREADY_CONNECTED_ERROR);
    }
    if(aux < 0){
        ALF_sockets_error = aux;
        return aux;
    }
    return 0;
}

int ALF_sockets_connect(ALF_socket *handler){
    int aux;
    if((aux = parseConnectErrors(handler)) < 0){
        return aux;
    }
    int retval = connect(handler->sock_desc, (struct sockaddr *)handler->addr, sizeof *(handler->addr));
    if(retval == 0){
        handler->connected = true;
    }
    if(retval < 0){
        ALF_sockets_error = -8;
        strcpy(ALF_sockets_errorMsg, CONNECT_ERROR);
        strcpy(ALF_sockets_errorMsg + strlen(ALF_sockets_errorMsg), strerror(errno));
    }
    return retval;
}

int parseBindErrors(ALF_socket *handler){
    int aux = 0;
    if(handler->binded){
        aux = -4;
        strcpy(ALF_sockets_errorMsg, ALREADY_BINDED_ERROR);
    }
    if(handler->listening){
        aux = -5;
        strcpy(ALF_sockets_errorMsg, ALREADY_LISTENING_ERROR);
    }
    if(handler->connected){
        aux = -6;
        strcpy(ALF_sockets_errorMsg, ALREADY_CONNECTED_ERROR);
    }
    if(aux < 0){
        ALF_sockets_error = aux;
        return aux;
    }
    return 0;
}

int ALF_sockets_bind(ALF_socket *handler){
    int aux;
    if((aux = parseBindErrors(handler)) < 0){
        return aux;
    }
    int retval = bind(handler->sock_desc, (struct sockaddr *)handler->addr, sizeof *(handler->addr));
    if(retval == 0){
        handler->binded = true;
    }
    if(retval < 0){
        ALF_sockets_error = -9;
        strcpy(ALF_sockets_errorMsg, BIND_ERROR);
        strcpy(ALF_sockets_errorMsg + strlen(ALF_sockets_errorMsg), strerror(errno));
    }
    return retval;
}

int parseListenErrors(ALF_socket *handler){
    int aux = 0;
    if(!handler->binded){
        aux = -7;
        strcpy(ALF_sockets_errorMsg, NOT_BINDED_ERROR);
    }
    if(handler->listening){
        aux = -5;
        strcpy(ALF_sockets_errorMsg, ALREADY_LISTENING_ERROR);
    }
    if(handler->connected){
        aux = -6;
        strcpy(ALF_sockets_errorMsg, ALREADY_CONNECTED_ERROR);
    }
    if(aux < 0){
        ALF_sockets_error = aux;
        return aux;
    }
    return 0;
}

int ALF_sockets_listen(ALF_socket *handler){
    int aux;
    if((aux = parseListenErrors(handler)) < 0){
        return aux;
    }

    int retval = listen(handler->sock_desc, handler->backlog);
    if(retval == 0){
        handler->listening = true;
    }
    if(retval < 0){
        ALF_sockets_error = -10;
        strcpy(ALF_sockets_errorMsg, LISTEN_ERROR);
        strcpy(ALF_sockets_errorMsg + strlen(ALF_sockets_errorMsg), strerror(errno));
    }
    return retval;
}

int parseAcceptErrors(ALF_socket *handler){
    int aux = 0;
    if(!handler->binded){
        aux = -7;
        strcpy(ALF_sockets_errorMsg, NOT_BINDED_ERROR);
    }
    if(!handler->listening){
        aux = -11;
        strcpy(ALF_sockets_errorMsg, NOT_LISTENING_ERROR);
    }
    if(handler->connected){
        aux = -6;
        strcpy(ALF_sockets_errorMsg, ALREADY_CONNECTED_ERROR);
    }
    if(aux < 0){
        ALF_sockets_error = aux;
        return aux;
    }
    return 0;
}

ALF_socket *ALF_sockets_accept(ALF_socket *handler){
    if(parseAcceptErrors(handler) < 0){
        return NULL;
    }

    ALF_socket *client_handler = malloc(sizeof(ALF_socket));
    if(client_handler == NULL){
        ALF_sockets_error = -2;
        strcpy(ALF_sockets_errorMsg, MALLOC_ERROR);
        return NULL;
    }
    if((client_handler->addr = malloc(sizeof(struct sockaddr_in))) == NULL){
        ALF_sockets_error = -2;
        strcpy(ALF_sockets_errorMsg, MALLOC_ERROR);
        free(client_handler);
        return NULL;
    }

    socklen_t address_len = sizeof(struct sockaddr_in);
    client_handler->sock_desc = accept(handler->sock_desc, (struct sockaddr *)client_handler->addr, &address_len);

    if(client_handler->sock_desc < 0){
        ALF_sockets_error = -12;
        strcpy(ALF_sockets_errorMsg, GENERIC_ERROR);
        strcpy(ALF_sockets_errorMsg + strlen(ALF_sockets_errorMsg), strerror(errno));

        free(client_handler->addr);
        free(client_handler);
        return NULL;
    }

    client_handler->backlog = 0;
    client_handler->binded = false;
    client_handler->listening = false;
    client_handler->connected = true;

    return client_handler;
}

int parseDataInterchangeErrors(ALF_socket *client_handler){
    int aux = 0;
    if(client_handler->binded){
        aux = -4;
        strcpy(ALF_sockets_errorMsg, ALREADY_BINDED_ERROR);
    }
    if(client_handler->listening){
        aux = -5;
        strcpy(ALF_sockets_errorMsg, ALREADY_LISTENING_ERROR);
    }
    if(!client_handler->connected){
        aux = -13;
        strcpy(ALF_sockets_errorMsg, NOT_CONNECTED_ERROR);
    }
    if(aux < 0){
        ALF_sockets_error = aux;
        return aux;
    }
    return 0;
}

ssize_t ALF_sockets_recv(ALF_socket *main_handler, ALF_socket *client_handler, size_t maxRecv, char *msg){
    ssize_t aux;
    if((aux = parseDataInterchangeErrors(client_handler)) < 0){
        return aux;
    }
    ssize_t read_size;

    read_size = recv(client_handler->sock_desc, msg, maxRecv, 0);
    if(read_size >= 0){
        msg[read_size] = 0;
    }
    if(read_size < 0){
        ALF_sockets_error = -14;
        strcpy(ALF_sockets_errorMsg, RECV_ERROR);
        strcpy(ALF_sockets_errorMsg + strlen(ALF_sockets_errorMsg), strerror(errno));
    }
    return read_size;
}

ssize_t ALF_sockets_recvNonBlocking(ALF_socket *main_handler, ALF_socket *client_handler, size_t maxRecv, char *msg){
    if(client_handler->binded){
        return -2;
    }
    if(client_handler->listening){
        return -3;
    }
    if(!client_handler->connected){
        return -4;
    }
    ssize_t read_size;

    read_size = recv(client_handler->sock_desc, msg, maxRecv, MSG_DONTWAIT);
    if(read_size == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)){
        // There is not message yet.
        return 0;
    }
    else if(read_size >= 0){
        msg[read_size] = 0;
    }
    if(read_size < 0){
        ALF_sockets_error = -15;
        strcpy(ALF_sockets_errorMsg, RECV_NB_ERROR);
        strcpy(ALF_sockets_errorMsg + strlen(ALF_sockets_errorMsg), strerror(errno));
    }

    return read_size;
}

ssize_t ALF_sockets_send(ALF_socket *main_handler, ALF_socket *client_handler, const char* msg){
    if(client_handler->binded){
        return -2;
    }
    if(client_handler->listening){
        return -3;
    }
    if(!client_handler->connected){
        return -4;
    }
    ssize_t retval = send(client_handler->sock_desc, msg, strlen(msg), 0);

    if(retval < 0){
        ALF_sockets_error = -16;
        strcpy(ALF_sockets_errorMsg, SEND_ERROR);
        strcpy(ALF_sockets_errorMsg + strlen(ALF_sockets_errorMsg), strerror(errno));
    }
    
    return retval;
}

ssize_t ALF_sockets_getLastError(){
    return ALF_sockets_error;
}

const char *ALF_sockets_getLastErrorMsg(){
    return ALF_sockets_errorMsg;
}
