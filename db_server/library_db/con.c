#include <stdio.h>
#include <mysql.h>
#include <errno.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
void main(void){
	char buf[1024];
	int temp = 1;
	memset(buf,0,1024);
	MYSQL_RES *result /*= malloc(sizeof(MYSQL_RES))*/;
	memset(result,0,sizeof(MYSQL_RES));
	MYSQL* mysql = malloc(sizeof(MYSQL));
	
	mysql_init(mysql);
	if(!mysql_real_connect(mysql,NULL,"guest","1234","LibraryDB",3306,(char*)NULL,0)){
		printf("%s\n",mysql_error(mysql));
		exit(1);
	}
	printf("connected\n") ;

	if(mysql_query(mysql, "describe book")){
		fprintf(stderr, "%s\n", mysql_error(mysql));
		mysql_close(mysql);
		exit(1);
	}
	result = mysql_store_result(mysql);
	if(result == NULL){
		fprintf(stderr, "%s\n", mysql_error(mysql));
		mysql_close(mysql);
		exit(1);
	}
	int num_fields = mysql_num_fields(result);
	printf("%d", num_fields);
	MYSQL_ROW row;
	int i=0;
	while(row = mysql_fetch_row(result)){
		for(i=0; i<num_fields;i++){
			temp = row[i] ? 1 : 0;
			if(temp == 1){
			printf("%s %d \n",row[i]);
			}
			else
				printf("%s %d\n","NULL", strlen("NULL"));

		}
		printf("**\n");
		
	}
	mysql_free_result(result);
	
	mysql_close(mysql);
}

