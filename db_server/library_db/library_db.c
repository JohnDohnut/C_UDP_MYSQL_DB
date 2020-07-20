#include "library_db.h"

library_db_t* library_db_t_init(){
	library_db_t* DB_CONN = malloc(sizeof(library_db_t));
	memset(DB_CONN,0,sizeof(library_db_t));
	return DB_CONN;

}
int library_db_close_connection(library_db_t* DB_CONN){
	mysql_close(&(DB_CONN->mysql));
	free(DB_CONN);
	return 0;
}
int library_db_connect(library_db_t* DB_CONN){
	if(!mysql_real_connect(&(DB_CONN->mysql),NULL,GUEST_ID,GUEST_PW,DB_NAME,DB_PORT,(char*)NULL,0)){
		fprintf(stderr, "%s\n", mysql_error(&(DB_CONN->mysql)) );
		return -1;
	}
	printf("connected\n");
	return 0;
}
int library_db_send_query(library_db_t* DB_CONN){
	if(mysql_query(&(DB_CONN->mysql),DB_CONN->query)){
		fprintf(stderr, "%s\n", mysql_error(&(DB_CONN->mysql)) );
		mysql_close(&(DB_CONN->mysql));
		return -2;		
	}
	printf("Query successfully sent...\nWaiting for result...\n");
	return 0;
}
int library_db_recv_result(library_db_t* DB_CONN){
	DB_CONN->result = mysql_store_result(&(DB_CONN->mysql));
	if(DB_CONN->result == NULL){
		fprintf(stderr, "%s\n", mysql_error(&(DB_CONN->mysql)) );
		mysql_close(&(DB_CONN->mysql));
		return -3;
	}
	printf("Result succesfully stored...\n");
	return 0;
}
int library_db_print_result(library_db_t* DB_CONN){
	DB_CONN->num_fields = mysql_num_fields(DB_CONN->result);
	if(DB_CONN->num_fields<=0){
		printf("Number of field is less than 1...\n");
		mysql_free_result(DB_CONN->result);
		mysql_close(&(DB_CONN->mysql));
		return -4;
	}
	int i=0;
	printf("Printing result...\n\n");
	while(DB_CONN -> num_row = mysql_fetch_row(DB_CONN->result)){
		for(i=0;i<DB_CONN -> num_fields;i++){
			printf("%s	",DB_CONN->num_row[i] ? DB_CONN->num_row[i] : "NULL");
		}
		printf("\n");
		
	}
	printf("\n\n Result Printed\n");
//	mysql_free_result(DB_CONN->result);
	return 0;
}

int library_db_print_result_to_buffer(library_db_t* DB_CONN,char* buffer){
	printf("%ld\n",sizeof('\t'));
	char* ptr = &buffer[0];
	memset(buffer,0,1024);
	int offset = 0;
	DB_CONN->num_fields = mysql_num_fields(DB_CONN->result);
	if(DB_CONN->num_fields<=0){
		printf("Number of field is less than 1...\n");
		mysql_free_result(DB_CONN->result);
		mysql_close(&(DB_CONN->mysql));
		return -4;
	}
	int i=0;
	printf("Printing result...\n\n");
	while(DB_CONN -> num_row = mysql_fetch_row(DB_CONN->result)){
		for(i=0;i<DB_CONN -> num_fields;i++){
			offset += snprintf(buffer+offset, strlen(DB_CONN->num_row[i])+9,"%s	",DB_CONN->num_row[i] ? DB_CONN->num_row[i] : "NULL");
			
		}
		offset+=snprintf(buffer+offset,2,"\n");
		
		
	}

	printf("%s\n",buffer);
	printf("\n\n Result Printed\n");
	mysql_free_result(DB_CONN->result);
	return 0;
}
int library_db_set_query(library_db_t* DB_CONN, char* query){
	if(0 > memcpy(DB_CONN->query, query, sizeof(DB_CONN->query)))
		return -1;
	return 0;
	
}




