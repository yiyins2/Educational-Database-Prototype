#include "../include/db_server.hpp"

const int buffer_size = 1024;

db_server::db_server(int port, string server_db_dir)
{
	this->port = port;
	this->end = false;
	this->q_executor = query_executor(server_db_dir);
}

/*
 * It receives the request from client and passes it to query_executor
 * Then it sends the result back to the user
 */
void *db_server::database_operation(void *socket_id_addr)
{
	int socket_id = *(int *)socket_id_addr;

	// Read command
	char buffer[buffer_size] = {0};
	recv(socket_id, buffer, buffer_size, 0);
	printf(received_request_msg.c_str(), socket_id, buffer);

	std::string cmd(buffer);
	std::string result = this->q_executor.execute(cmd);

	// Send back response
	send(socket_id, result.c_str(), strlen(result.c_str()), 0);

	if (strcmp(result.c_str(), "EXIT") == 0) {
		stop();
	}
	return NULL;
}

// Accept request from client
int db_server::start()
{
	int server_fd;
	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror(failed_to_create_socket_msg.c_str());
		return -1;
	}

	// Forcefully attaching socket
	int opt = 1;
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR,
				   &opt, sizeof(opt)))
	{
		perror(failed_to_attach_socket_msg.c_str());
		return -1;
	}

	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(this->port);

	// Forcefully attaching socket to the port 8085
	int bind_rc = ::bind(server_fd, (struct sockaddr *)&address, sizeof(address));
	if (bind_rc < 0)
	{
		perror(failed_to_bind_socket_msg.c_str());
		return -1;
	}

	// Listen
	if (listen(server_fd, 3) < 0)
	{
		perror(failed_to_listen_msg.c_str());
		return -1;
	}

	// Accept
	while (!this->end)
	{
        // Create a new socket to listen the client request
		int addrlen = sizeof(address);
		int new_socket_id = accept(server_fd, (struct sockaddr *)&address,
								   (socklen_t *)&addrlen);
		if (new_socket_id < 0)
		{
			perror(failed_to_accept_msg.c_str());
		}
		else
		{
			database_operation(&new_socket_id);
		}

		// Listen
		if (listen(server_fd, 3) < 0)
		{
			perror(failed_to_listen_msg.c_str());
			return -1;
		}
	}

	return 0;
}

int db_server::stop()
{
	this->end = true;
	return 0;
}