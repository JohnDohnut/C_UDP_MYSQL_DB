mid_server : mid_server.o  protocol.o common_module.o
	gcc -o mid_server mid_server.o  protocol.o common_module.o 

mid_server.o : mid_server.c
	gcc -c mid_server.c 

common_module.o : ../common_module/common_module.c
	gcc -c ../common_module/common_module.c

protocol.o : ../protocol/protocol.c
	gcc -c ../protocol/protocol.c


