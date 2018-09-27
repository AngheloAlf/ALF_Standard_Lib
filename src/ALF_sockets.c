#include "ALF_std/ALF_sockets.h"
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

ALF_socket *ALF_sockets_init(const char *ip, uint16_t port){
    ALF_socket *handler = malloc(sizeof(ALF_socket));
    if(handler == NULL){
        return NULL;
    }
    if((handler->sock_desc = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        free(handler);
        return NULL;
    }

    if((handler->addr = malloc(sizeof(struct sockaddr_in))) == NULL){
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

int ALF_sockets_connect(ALF_socket *handler){
    if(handler->binded){
        return -2;
    }
    if(handler->connected){
        return -4;
    }
    int retval = connect(handler->sock_desc, (struct sockaddr *)handler->addr, sizeof *(handler->addr));
    if(retval == 0){
        handler->connected = true;
    }
    return retval;
}

int ALF_sockets_bind(ALF_socket *handler){
    if(handler->binded){
        return -2;
    }
    if(handler->connected){
        return -4;
    }
    int retval = bind(handler->sock_desc, (struct sockaddr *)handler->addr, sizeof *(handler->addr));
    if(retval == 0){
        handler->binded = true;
    }
    return retval;
}

int ALF_sockets_listen(ALF_socket *handler){
    if(!handler->binded){
        return -2;
    }
    if(handler->listening){
        return -3;
    }
    if(handler->connected){
        return -4;
    }
    int retval = listen(handler->sock_desc, handler->backlog);
    if(retval == 0){
        handler->listening = true;
    }
    return retval;
}

ALF_socket *ALF_sockets_accept(ALF_socket *handler){
    if(!handler->binded){
        return NULL;
    }
    if(!handler->listening){
        return NULL;
    }
    if(handler->connected){
        return NULL;
    }
    ALF_socket *client_handler = malloc(sizeof(ALF_socket));
    if(client_handler == NULL){
        return NULL;
    }
    if((client_handler->addr = malloc(sizeof(struct sockaddr_in))) == NULL){
        free(client_handler);
        return NULL;
    }

    socklen_t address_len = sizeof(struct sockaddr_in);
    client_handler->sock_desc = accept(handler->sock_desc, (struct sockaddr *)client_handler->addr, &address_len);

    if(client_handler->sock_desc < 0){
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

int ALF_sockets_recv(ALF_socket *client_handler, size_t maxRecv, char *msg){
    if(client_handler->binded){
        return -2;
    }
    if(client_handler->listening){
        return -3;
    }
    if(!client_handler->connected){
        return -4;
    }
    size_t read_size;
    read_size = recv(client_handler->sock_desc, msg, maxRecv, 0);
    msg[read_size] = 0;

    return read_size;
}

char *ALF_sockets_recv_s(ALF_socket *client_handler, size_t maxRecv){
    char *msg = (char *)malloc(sizeof(char) * (maxRecv + 1));
    if(msg == NULL){
        return NULL;
    }
    size_t read_size;
    if((read_size = ALF_sockets_recv(client_handler, maxRecv, msg)) <= 0){
        free(msg);
        return NULL;
    }
    void *aux = realloc(msg, sizeof(char) * (read_size + 1));
    if(aux == NULL){
        free(msg);
        return NULL;
    }
    msg = (char *)aux;
    return msg;
}

int ALF_sockets_send(ALF_socket *client_handler, const char* msg){
    if(client_handler->binded){
        return -2;
    }
    if(client_handler->listening){
        return -3;
    }
    if(!client_handler->connected){
        return -4;
    }
    return send(client_handler->sock_desc, msg, strlen(msg), 0);
}
