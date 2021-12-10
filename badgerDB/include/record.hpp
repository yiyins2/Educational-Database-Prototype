#pragma once

#include <vector>
#include <string>

#include "schema.hpp"
#include "query/constant.hpp"

using namespace std;

class record {
	private:
		string table_name;
		vector<constant> values;
	
	public:
		record() {};
		record(string, vector<constant>);
		vector<constant> get_values();
		string get_table_name();
};