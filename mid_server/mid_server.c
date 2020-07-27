#include "mid_server.h"

/**
*@fn mid_server_t* mid_server_init(){
*@brief malloc and initialize mid_server structure
*@return mid_server_t*
*/
mid_server_t* mid_server_init(){
	mid_server_t* mid_server = malloc(sizeof(mid_server_t));
	memset(mid_server,0,sizeof(mid_server_t));
	mid_server->server = common_module_udp_server_init(MID_SERVER_PORT);
	printf("1\n");
	mid_server->client = common_module_udp_client_init(DB_SERVER_PORT);	
	printf("2\n");
	return mid_server;


}
/**
*@fn int mid_server_connect(mid_server_t* mid_server){
*@brief handle msg from client by querying or echoing the msg back to client 
*@param mid_server_t*
*@return int
*/
int mid_server_connect(mid_server_t* mid_server){
	protocol_packet_t* send_packet = common_module_packet_init();
	protocol_packet_t* recv_packet = common_module_packet_init();
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
		int server_sock = common_module_get_fd(mid_server->server);
		int client_sock = common_module_get_fd(mid_server->client);
		if(server_sock == -999 || client_sock == -999){
			printf("server sock / client sock error \n");
			return -1;
		}
	
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
					send_bytes = sendto(server_sock,send_packet,sizeof(protocol_packet_t), 0, (struct sockaddr*)(&client_addr), sizeof(client_addr));
				}
				else if(MSG_TYPE == 2){
					send_bytes = sendto(client_sock,recv_packet,sizeof(protocol_packet_t),0,(struct sockaddr*)mid_server->client->server_addr,sizeof(struct sockaddr));
					recv_bytes = recvfrom(client_sock,recv_packet,sizeof(protocol_packet_t),0,(struct sockaddr*)mid_server->client->server_addr,&addr_len);
					send_bytes = sendto(server_sock,recv_packet,sizeof(protocol_packet_t), 0, (struct sockaddr*)(&client_addr), sizeof(client_addr));
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

/**
*@fn int mid_server_destroy(mid_server_t* mid_server)
*@brief release mid_server_t* struct
*@param mid_server_t*
*@return int
*/
int mid_server_destroy(mid_server_t* mid_server){
	close(mid_server->server->SOCK);
	common_module_udp_socket_destroy(mid_server->server);
	common_module_udp_socket_destroy(mid_server->client);

}

/**
*@fn int main()
*@brief main() for mid_server
*@return int
*/
int main(){
	mid_server_t* mid_server = mid_server_init();
	mid_server_connect(mid_server);
	mid_server_destroy(mid_server);
}







