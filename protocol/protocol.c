#include "protocol.h"
/**
*@fn protocol_packet_t* protocol_packet_init()
*@brief malloc and initialize protocol_packet_t* and return it.
*@protocol_packet_t* 
*/
protocol_packet_t* protocol_packet_init(){
	protocol_packet_t* packet = malloc(sizeof(protocol_packet_t));
	memset(packet,0,sizeof(protocol_packet_t));
	return packet
}
/**
*@fn void protocol_clear_msg(protocol_packet_t* packet)
*@brief initialize packet body
*@param protocol_packet_t*
*/
void protocol_clear_msg(protocol_packet_t* packet){
	memset(packet->data,0,DATA_MAX_LENGTH);
	packet->header.data_len = 0;
	packet->header.data_type = -1;
	
}
/**
*@fn void protocol_increase_seq_id(protocol_packet_t* packet)
*@brief increase protocol_packet_t* -> header.seq_id 
*/
void protocol_increase_seq_id(protocol_packet_t* packet){
	packet->header.seq_id ++;
}
/**
*@fn void protocol_packet_destroy(protocol_packet_t* packet)
*@brief release packet
*/
void protocol_packet_destroy(protocol_packet_t* packet){
	free(packet);
}
/**
*@fn int protocol_get_data_len(protocol_packet_t* packet)
*@brief getter for protocol_packet_t* -> header.data_len
*@return int
*/

int protocol_get_data_len(protocol_packet_t* packet){
	return packet->header.data_len;
}
/**
*@fn int protocol_set_message(protocol_packet_t* packet,char* data_buffer)
*@brief set data and type of message of given packet with given char* buffer
*@return int
*/
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
		packet->header.data_len = strlen(packet->data)+1;
		return 0;
	}
}
/**
*@fn int protocol_clean_packet(protocol_packet_t* packet)
*@brief reinitialize packet except seq_id
*@param protocol_packet_t*
*@return int
*/
int protocol_clean_packet(protocol_packet_t* packet){
	int seq_id = packet->header.seq_id;
	memset(packet,0,sizeof(packet));
	packet->header.seq_id = seq_id;
	return 0;
}
/**
*@fn int protocol_get_msg_type(protocol_packet_t* packet)
*@brief getter for protocol_packet_t* -> header.data_type
*@param protocol_packet_t*
*@return int
*/
int protocol_get_msg_type(protocol_packet_t* packet){
	return packet->header.data_type;
	
}

/**
*@fn void protocol_print_message(protocol_packet_t* packet)
*@brief print packet
*@param protocol_packet_t*
*/
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








