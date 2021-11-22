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
 
  $(SERVER): server/db_server.cpp server/test_server.cpp query_executor/query_executor.cpp record/*.cpp file_manager/file_manager.cpp file_manager/block_id.cpp file_manager/page.cpp
			$(CC) $(CFLAGS) -o $(SERVER) server/db_server.cpp server/test_server.cpp query_executor/query_executor.cpp record/*.cpp file_manager/file_manager.cpp file_manager/block_id.cpp file_manager/page.cpp
 
  $(CLIENT): client/test_client.cpp client/db_client.cpp
			$(CC) $(CFLAGS) -o $(CLIENT)  client/test_client.cpp client/db_client.cpp

  clean:
	$(RM) $(SERVER) $(CLIENT)
