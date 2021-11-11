#pragma once

#include <string>
using namespace std;

class db_client {
	private:
		int port;
		string cmd;

	public:
		db_client(int, string);
		string send_cmd();
};