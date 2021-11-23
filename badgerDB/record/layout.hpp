#pragma once

#include <set>
#include <map>
#include <string>

#include "table.hpp"
#include "schema.hpp"
using namespace std;

class layout {
	private:
		set<string> tables_names;
		map<string, table> tables_info;
		map<string, schema> tables_schema;
		int add_table(table);
		int add_table_schema(string, schema);

	public:
		table* get_table(string);
		schema *get_table_schema(string);
		int add_table_and_schema(table, schema);
		int delete_table(string);
};