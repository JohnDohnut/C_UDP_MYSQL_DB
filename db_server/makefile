db_server : db_server.o library_db.o protocol.o common_module.o
	gcc -o db_server db_server.o library_db.o protocol.o common_module.o $$(mysql_config --include --libs)

db_server.o : db_server.c
	gcc -c db_server.c $$(mysql_config --include --libs)

library_db.o : library_db/library_db.c
	gcc -c library_db/library_db.c $$(mysql_config --include --libs)

common_module.o : ../common_module/common_module.c
	gcc -c ../common_module/common_module.c

protocol.o : ../protocol/protocol.c
	gcc -c ../protocol/protocol.c


