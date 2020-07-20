#include "../common_module/common_module.h"
typedef struct mid_server_s mid_server_t;
struct mid_server_s{
	udp_socket_t* server;
	udp_socket_t* client;
};

mid_server_t* mid_server_db_init();
int mid_server_connect(mid_server_t* mid_server);
int mid_server_destroy(mid_server_t* mid_server);

