#include <iostream>
#include <string>
using namespace std;

#include "../include/db_client.hpp"

int PORT = 8080;

int main(int argc, char *argv[]) {
	db_client client = db_client(PORT);
	client.start_shell();
}