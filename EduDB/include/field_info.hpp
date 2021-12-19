#pragma once

#include <string>
using namespace std;

struct field_info
{
	string type; // in bytes
	int length;

	field_info(string type, int length)
	{
		this->type = type;
		this->length = length;
	}

	field_info() {}
};