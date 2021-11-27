#include "db_server.hpp"

const int buffer_size = 1024;

db_server::db_server(int port)
{
	this->port = port;
	this->accept_sock_idx = 0;
	this->end = false;

	this->ex = executor();
}

void *db_server::database_operation(void *socket_id_addr)
{
	int socket_id = *(int *)socket_id_addr;
 
	// Read command 
	char buffer[buffer_size] = {0};

	recv(socket_id, buffer, buffer_size, 0);
	std::cout << "Request from " << socket_id << " : " << buffer << endl;

	// TODO: add database operations
	std::string cmd;
	cmd += buffer; 
	
	std::string result = this->ex.execute(cmd);
	
	// Send back response
	send(socket_id, result.c_str(), strlen(result.c_str()), 0);
	return NULL;
}

int db_server::start()
{
	int server_fd;
	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("server: create socket failed");
		return -1;
	}

	// Forcefully attaching socket to the port 8080
	int opt = 1;
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR,
				   &opt, sizeof(opt)))
	{
		perror("setsockopt");
		return -1;
	}

	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(this->port);

	// Forcefully attaching socket to the port 8080
	int bind_rc = ::bind(server_fd, (struct sockaddr *)&address, sizeof(address));
	if (bind_rc < 0)
	{
		perror("server: bind failed");
		return -1;
	}

	// Listen
	if (listen(server_fd, 3) < 0)
	{
		perror("server: listen");
		return -1;
	}

	// Accept
	while (!this->end)
	{
		int addrlen = sizeof(address);
		int new_socket_id = accept(server_fd, (struct sockaddr *)&address,
								   (socklen_t *)&addrlen);
		if (new_socket_id < 0)
		{
			perror("server: Failed to accept socket");
		}
		else
		{
			database_operation(&new_socket_id);
			// pthread_t pthread_id;
			// pthread_create(&pthread_id, NULL, &database_operation, &new_socket_id);
		}

		// Listen
		if (listen(server_fd, 3) < 0)
		{
			perror("server: listen");
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