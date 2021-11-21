#include <cstdio>
#include <cstdlib>

#include "../query_executor/query_executor.hpp"
#include "../record/table.hpp"

const int CREATE_TABLE_FIELD_TYPE_INVALID = -1;

int query_executor::create_table(string table_name, vector<string> fields_str) {
	int str_idx = 0;

	// Add fields to schema
	schema new_table_schema;
	while(str_idx < fields_str.size()) {
		string field_name = fields_str[str_idx];
		new_table_schema.addField(field_name);
		++str_idx;
	}

	// Add the table to schema
	table new_table (table_name, this->fm);
	this->tables_layout.add_table(new_table);
	return 0;
}

int query_executor::delete_table(string table_name) {
	this->tables_layout.delete_table(table_name);
	if (this->fm.delete_file(table_name) < 0) {
		// Table not exist
		return -1;
	}
	return 0;
}

int query_executor::insert_record(string table_name, record r) {
	return 0;
}

string query_executor::execute(string cmd) {
	std::string delim = " ";
	vector<string> parts;

	int start = 0;
	int end = cmd.find(delim);
	while (end != std::string::npos)
	{
		parts.push_back(cmd.substr(start, end - start));
		start = end + delim.length();
		end = cmd.find(delim, start);
	}
	parts.push_back(cmd.substr(start, end - start));

	if (parts.size() >= 3 && strcmp(parts[0].c_str(), "CREATE") == 0 && strcmp(parts[1].c_str(), "TABLE") == 0) {
		string table_name = parts[2];
		vector<string> fields;
		for (int i = 3; i < parts.size(); ++i) {
			fields.push_back(parts[i]);
		}

		this->create_table(table_name, fields);
		return "SUCCESS";
	}

	return "EMPTY";
}

// vector<record> query_executor::select(string table_name, vector<predicate> preds) {

// }