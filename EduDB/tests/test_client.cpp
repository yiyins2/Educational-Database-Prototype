#include "../include/db_client.hpp"
#include "../include/constant.hpp"

int main(int argc, char *argv[])
{
	db_client client = db_client(client_port);
	client.start_shell();
}