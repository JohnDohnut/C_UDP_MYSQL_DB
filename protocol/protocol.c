#include "protocol.h"

protocol_packet_t* protocol_packet_init(){
	protocol_packet_t* packet = malloc(sizeof(protocol_packet_t));
	memset(packet,0,sizeof(protocol_packet_t));
}
void protocol_clear_msg(protocol_packet_t* packet){
	memset(packet->data,0,DATA_MAX_LENGTH);
	packet->header.data_len = 0;
	packet->header.data_type = -1;
	
}
void protocol_increase_seq_id(protocol_packet_t* packet){
	packet->header.seq_id ++;
}
void protocol_packet_destroy(protocol_packet_t* packet){
	free(packet);
}
int protocol_get_data_len(protocol_packet_t* packet){
	return packet->header.data_len;
}
int protocol_set_message(protocol_packet_t* packet,char* data_buffer){
	if(memcmp(data_buffer,"/quit",sizeof("/quit")) == 0){
		memcpy(packet->data,data_buffer,DATA_MAX_LENGTH);
		return 9;
	}
	else if(memcmp(data_buffer,"/q ",sizeof("/q")) ==0){
			printf("%p\n",data_buffer);
			printf("%p\n",data_buffer+2);
			memcpy(packet->data,data_buffer+3,DATA_MAX_LENGTH - sizeof("/q "));
			return 2;
		}
	else if(memcmp(data_buffer,"/a",sizeof("/a")) ==0){
			memcpy(packet->data,"select * from book",DATA_MAX_LENGTH);
			return 2;
		}
	else if(memcmp(data_buffer,"/",1) == 0){
			memcpy(packet->data,data_buffer,DATA_MAX_LENGTH);
			return -1;
		}
	else{
		memcpy(packet->data,data_buffer,DATA_MAX_LENGTH);
		return 0;
	}
}
int protocol_clean_packet(protocol_packet_t* packet){
	int seq_id = packet->header.seq_id;
	memset(packet,0,sizeof(packet));
	packet->header.seq_id = seq_id;
	return 0;
}
int protocol_get_msg_type(protocol_packet_t* packet){
	return packet->header.data_type;
	
}
void protocol_print_message(protocol_packet_t* packet){
	printf("@@@@@ PACKET_START @@@@@\n");
	printf("---------header---------\n");
	printf("|seq_id : %13d|\n",packet->header.seq_id);
	printf("|msg_type : %11d|\n",packet->header.data_type);
	printf("|msg_length : %9d|\n",packet->header.data_len);
	printf("------------------------\n");
	printf("\n");
	printf("---------message--------\n");
	printf("%s\n",packet->data);
	printf("------------------------\n");
	printf("@@@@@@ PACKET_END @@@@@@\n");
}









	
