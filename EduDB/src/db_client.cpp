#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

#include "../include/db_client.hpp"
using namespace std;

const int buffer_size = 1024;

db_client::db_client(int port)
{
	this->port = port;
}

void db_client::start_shell() {
	// Send test command for connection test
	char conn_test_resp[buffer_size] = {0};
    // Test whether the client can access the port
	if (send_cmd(test_connection_cmd, conn_test_resp) < 0) {
        perror(connection_failed_msg.c_str());
		return;
	}
	cout << successfully_connected_msg << endl;

    // Input command
	string cmd;
	while(strcmp(cmd.c_str(), stop_server_cmd.c_str()) != 0) {
		cout << sql_command_line_info;
		getline(cin, cmd);

		char cmd_resp_buf[buffer_size] = {0};
		if (send_cmd(cmd, cmd_resp_buf) < 0)
		{
            perror(connection_failed_msg.c_str());
			return;
		}
		cout << cmd_resp_buf << endl;
		
		if (strcmp(cmd.c_str(), "EXIT") == 0) {
			return;
		}
	}
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
	if (inet_pton(AF_INET, server_address.c_str(), &serv_addr.sin_addr) <= 0)
	{
		return CONNECTION_FAILED;
	}

    // Connect to server port
	if (connect(socket_id, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		return CONNECTION_FAILED;
	}

    // Send request
	int l = send(socket_id, cmd.c_str(), strlen(cmd.c_str()), 0);
    // Receive response
	recv(socket_id, buf, buffer_size, 0);
	return 0;
}