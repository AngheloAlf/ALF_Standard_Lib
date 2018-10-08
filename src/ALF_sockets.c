#include "ALF_std/ALF_sockets.h"

#include <stdlib.h>
#include <string.h>


#ifdef _WIN32
#include <Winsock2.h>

typedef int socklen_t;

#define SHUT_RD SD_RECEIVE
#define SHUT_WR SD_SEND
#define SHUT_RDWR SD_BOTH

#define MSG_DONTWAIT 0

#pragma comment(lib, "ws2_32.lib")

#else
#include <arpa/inet.h>
#endif

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
#define IP_ERROR "IP is not valid. "
#define TYPE_ERROR "Invalid type. "
#define INVALID_TYPE_FUNCTION_ERROR "The function is not compatible with this mode. "
#define ACCEPT_ERROR "Couldn't accept. "
#define NONBLOCKING_ERROR "Couldn't enter/exit non-blocking mode. "
#define WINDOWS_INIT_ERROR "Windows couldn't init a thing. "

#define MALLOC_ERROR_CODE -2
#define SOCKET_CREATION_ERROR_CODE -3
#define ALREADY_BINDED_ERROR_CODE -4
#define ALREADY_LISTENING_ERROR_CODE -5
#define ALREADY_CONNECTED_ERROR_CODE -6
#define NOT_BINDED_ERROR_CODE -7
#define CONNECT_ERROR_CODE -8
#define BIND_ERROR_CODE -9
#define LISTEN_ERROR_CODE -10
#define NOT_LISTENING_ERROR_CODE -11
#define ACCEPT_ERROR_CODE -12
#define NOT_CONNECTED_ERROR_CODE -13
#define RECV_ERROR_CODE -14
#define RECV_NB_ERROR_CODE -15
#define SEND_ERROR_CODE -16
#define IP_ERROR_CODE -17
#define TYPE_ERROR_CODE -18
#define INVALID_TYPE_FUNCTION_ERROR_CODE -19
#define NONBLOCKING_ERROR_CODE -20
#define WINDOWS_INIT_ERROR_CODE -21

#define ERROR_MSG_LEN 1024
int ALF_sockets_error = 0;
char ALF_sockets_errorMsg[ERROR_MSG_LEN];

int ALF_sockets_getLastError() {
	return ALF_sockets_error;
}

const char *ALF_sockets_getLastErrorMsg() {
	return ALF_sockets_errorMsg;
}

int setError(int code, char *msg1, char *msg2) {
	size_t msg1len = strlen(msg1);
	long howMuchCpy = ERROR_MSG_LEN - msg1len;
	if (howMuchCpy < 0) {
		howMuchCpy = 0;
	}

	ALF_sockets_error = code;
	strncpy(ALF_sockets_errorMsg, msg1, ERROR_MSG_LEN);
	if(msg2 != NULL){
		strncpy(ALF_sockets_errorMsg + msg1len, msg2, howMuchCpy);
	}
    return code;
}


ALF_socket *ALF_sockets_createObject(const char *ip, uint16_t port, struct sockaddr_in *sock_addr){
    ALF_socket *handler = malloc(sizeof(ALF_socket));
    if(handler == NULL){
        /*ALF_sockets_error = -2;
        strcpy(ALF_sockets_errorMsg, MALLOC_ERROR);*/
		setError(MALLOC_ERROR_CODE, MALLOC_ERROR, NULL);
        return NULL;
    }

    if((handler->addr = malloc(sizeof(struct sockaddr_in))) == NULL){
        //ALF_sockets_error = -2;
        //strcpy(ALF_sockets_errorMsg, MALLOC_ERROR);
		setError(MALLOC_ERROR_CODE, MALLOC_ERROR, NULL);
        free(handler);
        return NULL;
    }

    if(ip == NULL && port == 0 && sock_addr == NULL){
        // pass
    }
    else if(sock_addr == NULL){
        memset(handler->addr, 0, sizeof *(handler->addr));
        handler->addr->sin_family = AF_INET;
        handler->addr->sin_addr.s_addr = htonl(INADDR_ANY);
        if(ip != NULL){
            // handler->addr->sin_addr.s_addr = inet_addr(ip);
            int aux = inet_pton(AF_INET, ip, &(handler->addr->sin_addr.s_addr));

            if(aux <= 0){
				char *auxError = NULL;
                //ALF_sockets_error = -17;
                //strcpy(ALF_sockets_errorMsg, IP_ERROR);
                if(aux < 0){
					auxError = strerror(errno);
                    //strcpy(ALF_sockets_errorMsg + strlen(ALF_sockets_errorMsg), strerror(errno));
                }

				setError(IP_ERROR_CODE, IP_ERROR, auxError);
                free(handler->addr);
                free(handler);
                return NULL;
            }
        }
        handler->addr->sin_port = htons(port);
    }
    else{
        memcpy(handler->addr, sock_addr, sizeof *(handler->addr));
    }

    return handler;
}

ALF_socket *ALF_sockets_createDestObj(int type){
    ALF_socket *aux = ALF_sockets_createObject(NULL, 0, NULL);
    aux->type = type;
    return aux;
}

ALF_socket *ALF_sockets_init(int type, const char *ip, uint16_t port){
    #ifdef _WIN32
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0) {
		wchar_t *s = NULL;

		FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, WSAGetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPWSTR)&s, 0, NULL);

		setError(WINDOWS_INIT_ERROR_CODE, WINDOWS_INIT_ERROR, s);

		LocalFree(s);
        return NULL;
	}
    #endif

    if(type != ALF_SOCKETS_TYPE_TCP && type != ALF_SOCKETS_TYPE_UDP){
        //ALF_sockets_error = -18;
        //strcpy(ALF_sockets_errorMsg, TYPE_ERROR);

		setError(TYPE_ERROR_CODE, TYPE_ERROR, NULL);
        return NULL;
    }

    ALF_socket *handler = ALF_sockets_createObject(ip, port, NULL);
    if(handler == NULL){
        return NULL;
    }

    if((handler->sock_desc = socket(AF_INET, type, 0)) < 0){
        //ALF_sockets_error = -3;
        //strcpy(ALF_sockets_errorMsg, SOCKET_CREATION_ERROR);
        //strcpy(ALF_sockets_errorMsg + strlen(ALF_sockets_errorMsg), strerror(errno));

		setError(SOCKET_CREATION_ERROR_CODE, SOCKET_CREATION_ERROR, strerror(errno));
        free(handler->addr);
        free(handler);
        return NULL;
    }

    handler->backlog = 128; // arbitrary.
    handler->binded = false;
    handler->listening = false;
    handler->connected = false;

    handler->type = type;

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
    // int aux = 0;
    if(handler->binded){
        // aux = -4;
        // strcpy(ALF_sockets_errorMsg, ALREADY_BINDED_ERROR);
		return setError(ALREADY_BINDED_ERROR_CODE, ALREADY_BINDED_ERROR, NULL);
    }
    if(handler->listening){
        // aux = -5;
        //strcpy(ALF_sockets_errorMsg, ALREADY_LISTENING_ERROR);
		return setError(ALREADY_LISTENING_ERROR_CODE, ALREADY_LISTENING_ERROR, NULL);
    }
    if(handler->connected){
        // aux = -6;
        //strcpy(ALF_sockets_errorMsg, ALREADY_CONNECTED_ERROR);
		return setError(ALREADY_CONNECTED_ERROR_CODE, ALREADY_CONNECTED_ERROR, NULL);
    }
    if(handler->type != ALF_SOCKETS_TYPE_TCP){
        // aux = -19;
        //strcpy(ALF_sockets_errorMsg, INVALID_TYPE_FUNCTION_ERROR);
		return setError(INVALID_TYPE_FUNCTION_ERROR_CODE, INVALID_TYPE_FUNCTION_ERROR, NULL);
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
        // ALF_sockets_error = -8;
        // strcpy(ALF_sockets_errorMsg, CONNECT_ERROR);
        // strcpy(ALF_sockets_errorMsg + strlen(ALF_sockets_errorMsg), strerror(errno));

		setError(CONNECT_ERROR_CODE, CONNECT_ERROR, strerror(errno));
    }
    return retval;
}

int parseBindErrors(ALF_socket *handler){
    // int aux = 0;
    if(handler->binded){
        // aux = -4;
        // strcpy(ALF_sockets_errorMsg, ALREADY_BINDED_ERROR);
		return setError(ALREADY_BINDED_ERROR_CODE, ALREADY_BINDED_ERROR, NULL);
    }
    if(handler->listening){
        // aux = -5;
        // strcpy(ALF_sockets_errorMsg, ALREADY_LISTENING_ERROR);
		return setError(ALREADY_LISTENING_ERROR_CODE, ALREADY_LISTENING_ERROR, NULL);
    }
    if(handler->connected){
        // aux = -6;
        // strcpy(ALF_sockets_errorMsg, ALREADY_CONNECTED_ERROR);
		return setError(ALREADY_CONNECTED_ERROR_CODE, ALREADY_CONNECTED_ERROR, NULL);
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
        //ALF_sockets_error = -9;
        // strcpy(ALF_sockets_errorMsg, BIND_ERROR);
        //strcpy(ALF_sockets_errorMsg + strlen(ALF_sockets_errorMsg), strerror(errno));

		setError(BIND_ERROR_CODE, BIND_ERROR, strerror(errno));
    }
    return retval;
}

int parseListenErrors(ALF_socket *handler){
    // int aux = 0;
    if(!handler->binded){
        // aux = -7;
        // strcpy(ALF_sockets_errorMsg, NOT_BINDED_ERROR);

		return setError(BIND_ERROR_CODE, BIND_ERROR, NULL);
    }
    if(handler->listening){
        // aux = -5;
        // strcpy(ALF_sockets_errorMsg, ALREADY_LISTENING_ERROR);

		return setError(ALREADY_LISTENING_ERROR_CODE, ALREADY_LISTENING_ERROR, NULL);
    }
    if(handler->connected){
        // aux = -6;
        // strcpy(ALF_sockets_errorMsg, ALREADY_CONNECTED_ERROR);

		return setError(ALREADY_CONNECTED_ERROR_CODE, ALREADY_CONNECTED_ERROR, NULL);
    }
    if(handler->type != ALF_SOCKETS_TYPE_TCP){
        // aux = -19;
        //  strcpy(ALF_sockets_errorMsg, INVALID_TYPE_FUNCTION_ERROR);

		return setError(INVALID_TYPE_FUNCTION_ERROR_CODE, INVALID_TYPE_FUNCTION_ERROR, NULL);
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
        // ALF_sockets_error = -10;
        // strcpy(ALF_sockets_errorMsg, LISTEN_ERROR);
        // strcpy(ALF_sockets_errorMsg + strlen(ALF_sockets_errorMsg), strerror(errno));

		setError(LISTEN_ERROR_CODE, LISTEN_ERROR, strerror(errno));
    }
    return retval;
}

int parseAcceptErrors(ALF_socket *handler){
    // int aux = 0;
    if(!handler->binded){
        // aux = -7;
        //strcpy(ALF_sockets_errorMsg, NOT_BINDED_ERROR);
		return setError(NOT_BINDED_ERROR_CODE, NOT_BINDED_ERROR, NULL);
    }
    if(!handler->listening){
        // aux = -11;
        //strcpy(ALF_sockets_errorMsg, NOT_LISTENING_ERROR);
		return setError(NOT_LISTENING_ERROR_CODE, NOT_LISTENING_ERROR, NULL);
    }
    if(handler->connected){
        // aux = -6;
        //strcpy(ALF_sockets_errorMsg, ALREADY_CONNECTED_ERROR);
		return setError(ALREADY_CONNECTED_ERROR_CODE, ALREADY_CONNECTED_ERROR, NULL);
    }
    if(handler->type != ALF_SOCKETS_TYPE_TCP){
        // aux = -19;
        //strcpy(ALF_sockets_errorMsg, INVALID_TYPE_FUNCTION_ERROR);
		return setError(INVALID_TYPE_FUNCTION_ERROR_CODE, INVALID_TYPE_FUNCTION_ERROR, NULL);
    }
    return 0;
}

ALF_socket *ALF_sockets_accept(ALF_socket *handler){
    if(parseAcceptErrors(handler) < 0){
        return NULL;
    }

    socklen_t address_len = sizeof(struct sockaddr_in);
    struct sockaddr addr_aux;

    int sock = accept(handler->sock_desc, &addr_aux, &address_len);

    if(sock < 0){
        //ALF_sockets_error = -12;
        //strcpy(ALF_sockets_errorMsg, ACCEPT_ERROR);
        //strcpy(ALF_sockets_errorMsg + strlen(ALF_sockets_errorMsg), strerror(errno));
		setError(ACCEPT_ERROR_CODE, ACCEPT_ERROR, strerror(errno));
        return NULL;
    }

    ALF_socket *client_handler = ALF_sockets_createObject(NULL, 0, (struct sockaddr_in *)&addr_aux);
    if(client_handler == NULL){
        return NULL;
    }
    client_handler->sock_desc = sock;

    client_handler->backlog = 0;
    client_handler->binded = false;
    client_handler->listening = false;
    client_handler->connected = true;

    client_handler->type = handler->type;

    return client_handler;
}

int parseDataInterchangeErrors(ALF_socket *client_handler){
    // int aux = 0;
    if(client_handler->type == ALF_SOCKETS_TYPE_TCP){
        if(client_handler->binded){
            //aux = -4;
            // strcpy(ALF_sockets_errorMsg, ALREADY_BINDED_ERROR);
			return setError(ALREADY_BINDED_ERROR_CODE, ALREADY_BINDED_ERROR, NULL);
        }
        if(client_handler->listening){
            //aux = -5;
            //strcpy(ALF_sockets_errorMsg, ALREADY_LISTENING_ERROR);
			return setError(ALREADY_LISTENING_ERROR_CODE, ALREADY_LISTENING_ERROR, NULL);
        }
        if(!client_handler->connected){
            //aux = -13;
            //strcpy(ALF_sockets_errorMsg, NOT_CONNECTED_ERROR);
			return setError(NOT_CONNECTED_ERROR_CODE, NOT_CONNECTED_ERROR, NULL);
        }
    }
    return 0;
}

ssize_t ALF_sockets_recv(ALF_socket *_from, char *msg, size_t maxRecv, ALF_socket *_to){
    ssize_t aux;
    if((aux = parseDataInterchangeErrors(_from)) < 0){
        return aux;
    }

    ssize_t read_size;
    if(_from->type == ALF_SOCKETS_TYPE_TCP){
        read_size = recv(_from->sock_desc, msg, maxRecv, 0);
    }
    else if(_from->type == ALF_SOCKETS_TYPE_UDP){
        socklen_t sock_len = sizeof *(_from->addr);
        read_size = recvfrom(_to->sock_desc, msg, maxRecv, 0, (struct sockaddr *)_from->addr, &sock_len);
    }
    else{
        //ALF_sockets_error = -18;
        //strcpy(ALF_sockets_errorMsg, TYPE_ERROR);
		setError(TYPE_ERROR_CODE, TYPE_ERROR, NULL);
        return ALF_sockets_error;
    }

    if(read_size >= 0){
        msg[read_size] = 0;
    }
    else{
        //ALF_sockets_error = -14;
        //strcpy(ALF_sockets_errorMsg, RECV_ERROR);
        //strcpy(ALF_sockets_errorMsg + strlen(ALF_sockets_errorMsg), strerror(errno));
		setError(RECV_ERROR_CODE, RECV_ERROR, strerror(errno));
    }
    return read_size;
}

long changeBlockingMode(ALF_socket *handler, long mode){
	int retVal = 0;
    #ifdef _WIN32
	long _mode = mode;
	retVal = ioctlsocket(handler->sock_desc, FIONBIO, &mode);
	if (retVal != 0) {
		//ALF_sockets_error = -20;
		//strcpy(ALF_sockets_errorMsg, NONBLOCKING_ERROR);

		wchar_t *s = NULL;
		FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, WSAGetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPWSTR)&s, 0, NULL);

		//strcpy(ALF_sockets_errorMsg + strlen(ALF_sockets_errorMsg), s);

		setError(NONBLOCKING_ERROR_CODE, NONBLOCKING_ERROR, s);

		LocalFree(s);
	}
    #else
    handler = handler + mode;
    #endif
	return retVal;
}

ssize_t ALF_sockets_recvNonBlocking(ALF_socket *_from, char *msg, size_t maxRecv, ALF_socket *_to){
    ssize_t aux;
    if((aux = parseDataInterchangeErrors(_from)) < 0){
        return aux;
    }

    ssize_t read_size;

    if(_from->type == ALF_SOCKETS_TYPE_TCP){
		if (changeBlockingMode(_from, -1) != 0){ // Windows bullshit. Init non blocking mode.
			return ALF_sockets_error;
		}
		read_size = recv(_from->sock_desc, msg, maxRecv, MSG_DONTWAIT);
		if (changeBlockingMode(_from, 0) != 0) { // Windows bullshit. Exit non blocking mode.
			return ALF_sockets_error;
		}
    }
    else if(_from->type == ALF_SOCKETS_TYPE_UDP){
		if (changeBlockingMode(_from, -1) != 0) { // Windows bullshit
			return ALF_sockets_error;
		}
		socklen_t sock_len = sizeof *(_from->addr);
		read_size = recvfrom(_to->sock_desc, msg, maxRecv, MSG_DONTWAIT, (struct sockaddr *)_from->addr, &sock_len);
		if (changeBlockingMode(_from, 0) != 0) { // Windows bullshit
			return ALF_sockets_error;
		}
    }
    else{
        //ALF_sockets_error = -18;
        //strcpy(ALF_sockets_errorMsg, TYPE_ERROR);
		setError(TYPE_ERROR_CODE, TYPE_ERROR, NULL);
        return ALF_sockets_error;
    }

    if(read_size == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)){
        // There is not message yet.
        return 0;
    }
    else if(read_size >= 0){
        msg[read_size] = 0;
    }
    if(read_size < 0){
       // ALF_sockets_error = -15;
       // strcpy(ALF_sockets_errorMsg, RECV_NB_ERROR);
        //strcpy(ALF_sockets_errorMsg + strlen(ALF_sockets_errorMsg), strerror(errno));
		setError(RECV_NB_ERROR_CODE, RECV_NB_ERROR, strerror(errno));
    }

    return read_size;
}

ssize_t ALF_sockets_send(ALF_socket *_to, const char* msg, size_t msgSize, ALF_socket *_from){
    ssize_t aux;
    if((aux = parseDataInterchangeErrors(_to)) < 0){
        return aux;
    }
    ssize_t retval;
    msgSize = msgSize > 0 ? msgSize : strlen(msg);

    if(_to->type == ALF_SOCKETS_TYPE_TCP){
        retval = send(_to->sock_desc, msg, msgSize, 0);
    }
    else if(_to->type == ALF_SOCKETS_TYPE_UDP){
        retval = sendto(_from->sock_desc, msg, msgSize, 0, (struct sockaddr *)(_to->addr), sizeof *(_to->addr));
    }
    else{
        //ALF_sockets_error = -18;
        //strcpy(ALF_sockets_errorMsg, TYPE_ERROR);
		setError(TYPE_ERROR_CODE, TYPE_ERROR, NULL);
        return ALF_sockets_error;
    }

    if(retval < 0){
        //ALF_sockets_error = -16;
        //strcpy(ALF_sockets_errorMsg, SEND_ERROR);
        //strcpy(ALF_sockets_errorMsg + strlen(ALF_sockets_errorMsg), strerror(errno));
		setError(SEND_ERROR_CODE, SEND_ERROR, strerror(errno));
    }

    return retval;
}

