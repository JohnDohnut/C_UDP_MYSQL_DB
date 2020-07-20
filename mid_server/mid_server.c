#include "mid_server.h"


mid_server_t* mid_server_init(){
	mid_server_t* mid_server = malloc(sizeof(mid_server_t));
	memset(mid_server,0,sizeof(mid_server_t));
	mid_server->server = common_module_udp_server_init(MID_SERVER_PORT);
	printf("1\n");
	mid_server->client = common_module_udp_client_init(DB_SERVER_PORT);	
	printf("2\n");
	return mid_server;


}
int mid_server_connect(mid_server_t* mid_server){
	protocol_packet_t* send_packet = malloc(sizeof(protocol_packet_t));
	protocol_packet_t* recv_packet = malloc(sizeof(protocol_packet_t));
	memset(send_packet,0,sizeof(protocol_packet_t));
	memset(recv_packet,0,sizeof(protocol_packet_t));
	char data_buffer[1024];
	int MSG_TYPE=0;
	printf("s : %ld\n",sizeof(protocol_packet_t));
	if(mid_server->server->SOCK <=0){
		free(mid_server);
		printf("socket fd error while connection\n");
		return -1;
		}
		struct sockaddr_in client_addr;
		int addr_len = sizeof(struct sockaddr);
		ssize_t recv_bytes;
		ssize_t send_bytes;
		memset(&client_addr,0,addr_len);
		printf("client addr struct init done...\n");
	
	while(1){
		MSG_TYPE = 0;
		//recv
		printf("waiting for msg\n");
		recv_bytes = recvfrom(mid_server->server->SOCK, recv_packet,sizeof(protocol_packet_t),0,(struct sockaddr*)(&client_addr),&addr_len);
		if(recv_bytes<=0){
			printf("failed to receive data\n");
			break;
		}
		else{	
			  

				protocol_print_message(recv_packet);
				recv_packet->data[DATA_MAX_LENGTH-1] = '\0';
				MSG_TYPE = protocol_get_msg_type(recv_packet);
				if(MSG_TYPE == 0){
					memcpy(send_packet,recv_packet,sizeof(protocol_packet_t));
					send_bytes = sendto(mid_server->server->SOCK,send_packet,sizeof(protocol_packet_t), 0, (struct sockaddr*)(&client_addr), sizeof(client_addr));
				}
				else if(MSG_TYPE == 2){
					send_bytes = sendto(mid_server->client->SOCK,recv_packet,sizeof(protocol_packet_t),0,(struct sockaddr*)mid_server->client->server_addr,sizeof(struct sockaddr));
					recv_bytes = recvfrom(mid_server->client->SOCK,recv_packet,sizeof(protocol_packet_t),0,(struct sockaddr*)mid_server->client->server_addr,&addr_len);
					send_bytes = sendto(mid_server->server->SOCK,recv_packet,sizeof(protocol_packet_t), 0, (struct sockaddr*)(&client_addr), sizeof(client_addr));
					protocol_print_message(recv_packet);

				}
				else if(MSG_TYPE == 9){
					continue;
				}
				else{
					
					continue;
				}				
				protocol_clean_packet(recv_packet);
				protocol_clean_packet(send_packet);
				
			
		}

			//send
			//recv
		//send
	}
	protocol_packet_destroy(send_packet);
	protocol_packet_destroy(recv_packet);

	return 0;

}
int mid_server_destroy(mid_server_t* mid_server){
	
	



}


int main(){
	mid_server_t* mid_server = mid_server_init();
	mid_server_connect(mid_server);
}







