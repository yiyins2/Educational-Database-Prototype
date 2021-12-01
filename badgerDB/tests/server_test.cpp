#include "../include/db_server.hpp"

int main()
{
	string db_dir = "./db";
	db_server server(server_port, db_dir);
	server.start();
}