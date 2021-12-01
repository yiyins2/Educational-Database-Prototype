#pragma once

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string>
#include <pthread.h>
#include <iostream>

// #include "../executor/executor.hpp"

class db_server
{	private:
		int accept_sock_idx; // For test use, temp
		void* database_operation(void *);
		executor ex;
		
		int port;
		bool end; // whether the user want to stop the server

	public:
		db_server(int);
		int start();
		int stop();
};