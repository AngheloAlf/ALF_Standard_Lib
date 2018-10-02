/** \file ALF_sockets.h
* A wrapper for easy use of sockets.
**/

#ifndef ALF_sockets_h
#define ALF_sockets_h

#include "ALF_common.h"
#include <stdint.h>
#include <stdbool.h>
#include <sys/socket.h>

#define ALF_SOCKETS_TYPE_TCP SOCK_STREAM
#define ALF_SOCKETS_TYPE_UDP SOCK_DGRAM

typedef struct {
    int sock_desc;
    struct sockaddr_in *addr;

    int backlog;
    size_t maxRecv;

    bool binded;
    bool listening;
    bool connected;

    int type;
} ALF_socket;


ALF_socket *ALF_sockets_init(int type, const char *ip, uint16_t port);

ALF_socket *ALF_sockets_createDestObj();

void ALF_sockets_free(ALF_socket *handler);

void ALF_sockets_setBacklog(ALF_socket *handler, int backlog);

int ALF_sockets_getBacklog(ALF_socket *handler);

int ALF_sockets_connect(ALF_socket *handler);

int ALF_sockets_bind(ALF_socket *handler);

int ALF_sockets_listen(ALF_socket *handler);

ALF_socket *ALF_sockets_accept(ALF_socket *handler);

ssize_t ALF_sockets_recv(ALF_socket *_to, char *msg, size_t maxRecv, ALF_socket *_from);

ssize_t ALF_sockets_recvNonBlocking(ALF_socket *_to, char *msg, size_t maxRecv, ALF_socket *_from);

ssize_t ALF_sockets_send(ALF_socket *_to, const char* msg, size_t msgSize, ALF_socket *_from);

ssize_t ALF_sockets_getLastError();
const char *ALF_sockets_getLastErrorMsg();

#endif /* ALF_sockets_h */
