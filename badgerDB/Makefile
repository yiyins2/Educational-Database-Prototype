# the compiler: gcc for C program, define as g++ for C++
  CC = g++
 
  # compiler flags:
  #  -g     - this flag adds debugging information to the executable file
  #  -Wall  - this flag is used to turn on most compiler warnings
  CFLAGS  = -I/opt/homebrew/Cellar/boost/1.76.0 -g -std=c++14 
 
  # The build target 
  SERVER = server1
  CLIENT = client1

  all : $(SERVER) $(CLIENT) 
  .PHONY : all

  $(SERVER): tests/test_server.cpp src/*.cpp src/parse/*.cpp src/query/*.cpp
			$(CC) $(CFLAGS) -o $(SERVER) tests/test_server.cpp src/*.cpp src/parse/*.cpp src/query/*.cpp
 
  $(CLIENT): tests/test_client.cpp src/db_client.cpp
			$(CC) $(CFLAGS) -o $(CLIENT)  tests/test_client.cpp src/db_client.cpp

  clean:
	$(RM) $(SERVER) $(CLIENT)
