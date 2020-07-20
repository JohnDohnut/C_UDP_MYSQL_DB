#include "db_server.h"
db_server_t* db_server_init(){
	db_server_t* db_server = malloc(sizeof(db_server_t));
	printf("1\n");
	if(db_server == NULL){
		return NULL;
	}
	printf("2\n");
	if(memset(db_server,0,sizeof(db_server_t))==NULL){
		return NULL;
	}
	printf("3\n");
	db_server->server = common_module_udp_server_init(DB_SERVER_PORT);
	printf("4\n");
	if(db_server->server == NULL)
		return NULL;	
	db_server->db_conn = (library_db_t*)(library_db_t_init());
	if(db_server->db_conn == NULL)
		return NULL;

	return db_server;
	
}
int  db_server_db_connect(db_server_t* db_server){
	if(library_db_connect(db_server->db_conn)!=0){
		return -1;
	}
	return 0;
}
int db_server_connect(db_server_t* db_server){
	int i;
	char query[1024];
	memset(query,0,1024);
	memcpy(query,"select * from book", sizeof(query));
	protocol_packet_t* send_packet = protocol_packet_init();
	protocol_packet_t* recv_packet = protocol_packet_init();
	printf("connecting...\n");
	printf("SOCK no : %d\n",db_server->server->SOCK);
	if(db_server->server->SOCK <=0){
		free(db_server);
		printf("socket fd error while connection\n");
		return -1;
	}
	struct sockaddr_in client_addr;
	int addr_len = sizeof(struct sockaddr);
	ssize_t recv_bytes;
	memset(&client_addr,0,addr_len);
	printf("client addr struct init done...\n");
	while(1){
		printf("waiting for msg\n");
		recv_bytes = recvfrom(db_server->server->SOCK, recv_packet,sizeof(*recv_packet),0,(struct sockaddr*)(&client_addr),&addr_len);
		if(recv_bytes<=0){
			printf("failed to receive data\n");
			break;
		}
		else{	
				protocol_print_message(recv_packet);
				memcpy(send_packet,recv_packet,sizeof(protocol_packet_t));

				library_db_set_query(db_server->db_conn,recv_packet->data);
				printf("set\n");
				library_db_send_query(db_server->db_conn);
				printf("snd\n");
				library_db_recv_result(db_server->db_conn);
				printf("rcv\n");
				library_db_print_result_to_buffer(db_server->db_conn, send_packet->data);
				printf("BUFFER *** \b %s \n",send_packet->data);
				//library_db_print_result(db_server->db_conn);
				

				printf("pr\n");
	
				recv_packet->data[DATA_MAX_LENGTH-1] = '\0';
				sendto(db_server->server->SOCK,send_packet,sizeof(protocol_packet_t), 0, (struct sockaddr*)(&client_addr), sizeof(client_addr));


		}
		protocol_clean_packet(send_packet);
		protocol_clean_packet(recv_packet);
		protocol_increase_seq_id(send_packet);

		
	}


	
}

int db_server_destroy(db_server_t* db_server){
	common_module_udp_socket_destroy(db_server->server);
	if(library_db_close_connection(db_server->db_conn)!=0)
		return -1;

}


int main(){
	db_server_t* server = db_server_init();
	db_server_db_connect(server);
	printf("init done \n");
	db_server_connect(server);
	db_server_destroy(server);
}

