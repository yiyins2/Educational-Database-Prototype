#pragma once

#include <set>
#include <map>
#include <string>

#include "table.hpp"
using namespace std;

class layout {
	private:
		set<string> tables_names;
		map<string, table> tables_info;
	
	public:
		table* get_table(string);
		int add_table(table);
		int delete_table(string);
};