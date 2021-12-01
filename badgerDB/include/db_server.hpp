#pragma once

#include <unistd.h>
#include <cstdio>
#include <sys/socket.h>
#include <cstdlib>
#include <netinet/in.h>
#include <string>
#include <pthread.h>
#include <iostream>

#include "query_executor.hpp"

#include "messages.hpp"

/*
 * db_server is a socket-based server for receiving the request from client
 * and pass the request to query_executor.
 * Each time it receives a request, it creates a new thread to execute it
 */
class db_server
{	private:
        // Accept the user request and run concurrently
		void* database_operation(void *);

		query_executor q_executor;
		int port;
        // whether the user want to stop the server.
        // This is used by "exit" command to stop the server
		bool end;

	public:
		db_server(int, std::string);
		int start();
		int stop();
};