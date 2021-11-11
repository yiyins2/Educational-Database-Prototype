#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include "db_client.hpp"

const int buffer_size = 1024;

db_client::db_client(int port, string cmd)
{
	this->port = port;
	this->cmd = cmd;
}

string db_client::send_cmd()
{
	int socket_id;
	if ((socket_id = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("client: Socket creation error");
		return "";
	}

	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(this->port);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
	{
		printf("\nInvalid address/ Address not supported \n");
		return "";
	}

	if (connect(socket_id, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		perror("client: Connection Failed \n");
		return "";
	}

	int l = send(socket_id, this->cmd.c_str(), strlen(this->cmd.c_str()), 0);
	char buffer[buffer_size] = {0};
	recv(socket_id, buffer, buffer_size, 0);

	printf("%s\n", buffer);

	// Convert char* to string
	string ans;
	ans.append(buffer);
	return ans;
}