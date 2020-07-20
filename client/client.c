#include "client.h"

udp_socket_t* udp_client_init(){	
	udp_socket_t* client = malloc(sizeof(udp_socket_t*));
	client->server_addr = malloc(sizeof(struct sockaddr_in));
	memset(client->server_addr,0,sizeof(struct sockaddr_in));
	client->server_addr->sin_family = AF_INET;
	inet_aton("127.0.0.1", (struct in_addr*) &client->server_addr->sin_addr.s_addr);
	client->server_addr->sin_port = htons(MID_SERVER_PORT);

	if((client->SOCK = socket(AF_INET,SOCK_DGRAM,0))==-1){
		printf("socket() failed\n");
		exit(1);
	}
	return client;
}
void udp_client_connect(udp_socket_t* client){

	ssize_t sendbytes;
		ssize_t recvbytes;
		int addr_len=sizeof(struct sockaddr);
		int i=0;
		protocol_packet_t* send_packet = protocol_packet_init();
		protocol_packet_t* recv_packet = protocol_packet_init();
		char user_buffer[DATA_MAX_LENGTH];
		while(1){
			
			printf("wating for input...\n");
			fgets(user_buffer, DATA_MAX_LENGTH-1,stdin);
			for(i=0;i<DATA_MAX_LENGTH;i++){
				if(user_buffer[i] == '\n')
					user_buffer[i] = '\0';
			}
			user_buffer[DATA_MAX_LENGTH-1] = '\0';
			send_packet->header.data_type = protocol_set_message(send_packet,user_buffer);
			if(send_packet->header.data_type == -1){
				printf("wrong msg\n");
				continue;
			}
			sendbytes = sendto(client->SOCK,send_packet,sizeof(*recv_packet),0,(struct sockaddr*)client->server_addr,sizeof(struct sockaddr));
			printf("%d bytes sent\n",sendbytes);
			if(sendbytes == -1){ // if fail to send packet
				printf("send msg failed.\n1 : continue\n2 : terminate client\n");
				fgets(user_buffer,DATA_MAX_LENGTH-1,stdin);
				if(atoi(user_buffer) == 1){
					continue;
				}
				else if (atoi(user_buffer) == 2){
					break;
				}
				else{
					printf("wrong input, terminating process. \n");
					break;
				}
				//send error handling
				
			}
			if(send_packet->header.data_type == 9){
				break;
			}
			printf("msg sent.. waiting for response..\n");
			recvbytes = recvfrom(client->SOCK,recv_packet,sizeof(*recv_packet),0,(struct sockaddr*)client->server_addr,&addr_len);
			printf("recv bytes : %d\n",recvbytes);		
			if(recvbytes<=0){
				printf("recv error \n");
				continue;
			}
			else{
				printf("response from server\n\n");
				recv_packet->data[DATA_MAX_LENGTH-1] = '\0';
				protocol_print_message(recv_packet);
			}
			// destroy packets.
			protocol_clean_packet(recv_packet);
			protocol_clean_packet(send_packet);
			protocol_increase_seq_id(send_packet);
			
		}
		protocol_packet_destroy(send_packet);
		protocol_packet_destroy(recv_packet);
	
}
void udp_client_destroy(udp_socket_t* client){
	close(client->SOCK);
	free(client);

}

int main(){
	udp_socket_t* client = udp_client_init();

	udp_client_connect(client);
	udp_client_destroy(client);
}

