#pragma once

class db_server
{	private:
		static int accept_sock_idx; // For test use, temp
		static void* database_operation(void *);
		
		int port;
		bool end; // whether the user want to stop the server

	public:
		db_server(int);
		int start();
		int stop();
};