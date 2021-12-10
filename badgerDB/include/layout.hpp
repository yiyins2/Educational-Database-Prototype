#pragma once

#include <set>
#include <map>
#include <string>

#include "table.hpp"
#include "schema.hpp"
#include "messages.hpp"
using namespace std;

class layout {
	private:
		set<string> tables_names;
		map<string, table> tables_info;
		map<string, schema> tables_schema;
		void add_table(table);
		void add_table_schema(string, schema);

	public:
		table* get_table(string);
		schema *get_table_schema(string);
		void add_table_and_schema(table, schema);
		void drop_table(string);
};