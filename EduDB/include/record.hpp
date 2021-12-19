#pragma once

#include <vector>
#include <string>

#include "schema.hpp"
using namespace std;

class record {
	private:
		string table_name;
		vector<int> value;
	
	public:
		record(string table_name, vector<int> value);
		record(){}
		vector<int> get_value();
		string get_table_name();
};