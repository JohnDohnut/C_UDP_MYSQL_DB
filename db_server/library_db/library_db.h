#ifndef __library_db_H__
#define __library_db_H__
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include <mysql.h>

#define ADDRESS "127.0.0.1"
#define GUEST_ID "guest"
#define GUEST_PW "1234"
#define DB_NAME "LibraryDB"
#define DB_PORT 3306

typedef struct library_db_s library_db_t;
struct library_db_s{
	MYSQL mysql;
	char query[1024];
	MYSQL_RES* result;
	int num_fields;
	MYSQL_ROW num_row;
};

library_db_t* library_db_t_init();
int library_db_close_connection(library_db_t* DB_CONN);
int library_db_send_query(library_db_t* DB_CONN);
int library_db_recv_result(library_db_t* DB_CONN);
int library_db_print_result(library_db_t* DB_CONN);
int library_db_set_query(library_db_t* DB_CONN, char* query);

#endif
