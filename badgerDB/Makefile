# the compiler: gcc for C program, define as g++ for C++
  CC = g++
 
  # compiler flags:
  #  -g     - this flag adds debugging information to the executable file
  #  -Wall  - this flag is used to turn on most compiler warnings
  CFLAGS  = -g -std=c++11
 
  # The build target 
  SERVER = server1
  CLIENT = client1

  all : $(SERVER) $(CLIENT) 
  .PHONY : all
 
  # $(SERVER): server/db_server.cpp server/test_server.cpp executor/executor.cpp record/*.cpp file_manager/file_manager.cpp file_manager/block_id.cpp file_manager/page.cpp query/*.cpp parser/lexer.cpp parser/parser.cpp parser/create_table_data.cpp parser/drop_table_data.cpp parser/insert_data.cpp parser/update_data.cpp parser/delete_data.cpp parser/query_data.cpp
	# 		$(CC) $(CFLAGS) -o $(SERVER) server/db_server.cpp server/test_server.cpp executor/executor.cpp record/*.cpp file_manager/file_manager.cpp file_manager/block_id.cpp file_manager/page.cpp query/*.cpp parser/lexer.cpp parser/parser.cpp parser/create_table_data.cpp parser/drop_table_data.cpp parser/insert_data.cpp parser/update_data.cpp parser/delete_data.cpp parser/query_data.cpp
  $(SERVER): tests/test_server.cpp src/*.cpp
			$(CC) $(CFLAGS) -o $(SERVER) tests/test_server.cpp src/*.cpp
 
  $(CLIENT): tests/test_client.cpp src/db_client.cpp
			$(CC) $(CFLAGS) -o $(CLIENT)  tests/test_client.cpp src/db_client.cpp

  clean:
	$(RM) $(SERVER) $(CLIENT)
