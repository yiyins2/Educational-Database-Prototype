#pragma once

#include <vector>
#include <string>

#include "schema.hpp"
using namespace std;

class record {
	private:
		string table_name;
		vector<int> values;
	
	public:
		record(string, vector<int>);
		record(){}
		vector<int> get_values();
		string get_table_name();
};