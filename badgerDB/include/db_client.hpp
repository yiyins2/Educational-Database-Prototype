#pragma once
#include <string>

#include "messages.hpp"
using namespace std;

class db_client {
	private:
		int port;
		int send_cmd(string, char*);

	public:
		db_client(int);
		void start_shell();
};