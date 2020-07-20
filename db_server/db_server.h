#include "library_db/library_db.h"
#include "../common_module/common_module.h"

typedef struct db_server_s db_server_t;

struct db_server_s{
	udp_socket_t* server;
	library_db_t* db_conn;
};

db_server_t* db_server_db_init();
int db_server_connect(db_server_t* db_server);
int db_server_destroy(db_server_t* db_server);
int db_server_db_connect(db_server_t* db_server);
