#include "common_module.h"

udp_socket_t* common_module_udp_server_init(int PORT){
	udp_socket_t* server = malloc(sizeof(udp_socket_t));
	if(server ==NULL)
		return NULL;
	printf("5\n");
	if(memset(server,0,sizeof(udp_socket_t))==NULL)
		return NULL;
	server->server_addr = malloc(sizeof(struct sockaddr_in));
	if(memset(server->server_addr,0,sizeof(struct sockaddr_in)) == NULL){
		return NULL;
	}	
	printf("6\n");
	server->server_addr->sin_family = AF_INET;
	server->server_addr->sin_port = htons(PORT);
	server->server_addr->sin_addr.s_addr=htonl(INADDR_ANY);
	server->SOCK = socket(PF_INET,SOCK_DGRAM,0);
	printf("7\n");
	if(server->SOCK <0){
		printf("socket() failed\n");
		free(server);
		exit(0);	
	}
	printf("8\n");
	if(bind(server->SOCK, (struct sockaddr*)server->server_addr, sizeof(struct sockaddr))<0){
		printf("bind() faild\n");
		close(server->SOCK);
		free(server);
		exit(1);
	}
	return server;

}

udp_socket_t* common_module_udp_client_init(int SERVER_PORT){
	printf("client socket init...\n");
	udp_socket_t* client = malloc(sizeof(udp_socket_t));
	if(client == NULL)
		return NULL;
	client->server_addr = malloc(sizeof(struct sockaddr_in));
	if(memset(client->server_addr,0,sizeof(struct sockaddr_in))==NULL)
		return NULL;
	client->server_addr->sin_family = AF_INET;
	inet_aton("127.0.0.1", (struct in_addr*) &client->server_addr->sin_addr.s_addr);
	client->server_addr->sin_port = htons(SERVER_PORT);

	if((client->SOCK = socket(AF_INET,SOCK_DGRAM,0))==-1){
		printf("socket() failed\n");
		return NULL;
	}
	printf("client socket init done...\n");
	return client;
}

void common_module_udp_socket_destroy(udp_socket_t* socket){
	close(socket->SOCK);
	free(socket);
}


