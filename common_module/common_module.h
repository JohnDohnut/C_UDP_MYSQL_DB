#ifndef __COMMON_MODULE_H__
#define __COMMON_MODULE_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <bsd/string.h>

#include "../protocol/protocol.h"

#define SERVER_ADDR "127.0.0.1"
#define DB_SERVER_PORT 4000
#define MID_SERVER_PORT 4010


typedef struct udp_socket_s udp_socket_t;
struct udp_socket_s{
	int SOCK;	///fd for socket
	struct sockaddr_in* server_addr;///srtucture manage server address

};
udp_socket_t* common_module_udp_server_init(int SERVER_PORT);/// Initialize and return udp_server_t*, socket() and bind(),
udp_socket_t* common_module_udp_client_init(int SERVER_PORT);
void common_module_udp_socket_destroy(udp_socket_t* socket);/// Destroy udp_server_t* server and terminate the server. (Currently SIGINT is only way to terminate the program.)
#endif
