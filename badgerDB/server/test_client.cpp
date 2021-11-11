#include <iostream>
#include <string>
using namespace std;

#include "db_server.hpp"
#include "db_client.hpp"

int PORT = 8080;

int main(int argc, char *argv[]) {
	db_client client = db_client(PORT, argv[1]);
	cout << client.send_cmd();
}