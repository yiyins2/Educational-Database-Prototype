#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <string.h>

#include "db_client.hpp"
using namespace std;

const int buffer_size = 1024;
const int CONNECTION_FAILED = -1;
const string TEST_CMD = "123";
const string STOP_CMD = "exit";

db_client::db_client(int port)
{
	this->port = port;
}

void db_client::start_shell() {
	// Send test command for connection test
	char conn_test_resp[buffer_size] = {0};

	cout << "Aloha" << endl;
	if (send_cmd(TEST_CMD, conn_test_resp) < 0) {
		cout << "Connection failed" << endl;
		return;
	}
	cout << "Successfully connected to server" << endl;

	string cmd;
	while(strcmp(cmd.c_str(), STOP_CMD.c_str()) != 0) {
		cout << "SQL> ";
		cin >> cmd;

		char cmd_resp_buf[buffer_size] = {0};
		if (send_cmd(TEST_CMD, cmd_resp_buf) < 0)
		{
			cout << "Connection failed" << endl;
			return;
		}
		cout << cmd_resp_buf << endl;
	}
	return;
}

int db_client::send_cmd(string cmd, char *buf)
{
	int socket_id;
	if ((socket_id = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		return CONNECTION_FAILED;
	}

	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(this->port);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
	{
		return CONNECTION_FAILED;
	}

	if (connect(socket_id, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		return CONNECTION_FAILED;
	}

	int l = send(socket_id, cmd.c_str(), strlen(cmd.c_str()), 0);

	recv(socket_id, buf, buffer_size, 0);

	return 0;
}