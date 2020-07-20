#ifndef __CLIENT_H__
#define __CLIENT_H__
#include "../common_module/common_module.h"

udp_socket_t* udp_client_init();
void udp_client_connect(udp_socket_t* client);
void udp_client_destroy(udp_socket_t* client);


#endif
