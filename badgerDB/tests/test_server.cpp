#include "../include/db_server.hpp"

int PORT = 8080;

int main()
{
	string db_dir = "../db";
	db_server server(PORT, db_dir);
	server.start();
}