client : client.o  protocol.o common_module.o
	gcc -o client client.o  protocol.o common_module.o 

client.o : client.c
	gcc -c client.c 

common_module.o : ../common_module/common_module.c
	gcc -c ../common_module/common_module.c

protocol.o : ../protocol/protocol.c
	gcc -c ../protocol/protocol.c


