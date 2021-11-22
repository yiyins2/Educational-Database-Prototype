#include "db_server.hpp"

int PORT = 8080;

int main()
{
	db_server server(PORT);
	server.start();
}