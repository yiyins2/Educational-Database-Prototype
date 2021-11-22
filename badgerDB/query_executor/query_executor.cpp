#include <cstdio>
#include <cstdlib>

#include "../query_executor/query_executor.hpp"
#include "../record/table.hpp"

const int CREATE_TABLE_FIELD_TYPE_INVALID = -1;
const int TABLE_NOT_EXIST = -2;
const int TABLE_SCHEMA_NOT_EXIST = -3;
const int INSERT_RECORD_FIELD_SIZE_INVALID = -4;

bool query_executor::checkNumber(string number) {
	for (int i = 0; i < number.length(); i++)
		if (isdigit(number[i]) == false)
			return false;
	return true;
}

int query_executor::create_table(string table_name, vector<string> fields_str) {
	int str_idx = 0;

	// Add fields to schema
	schema new_table_schema;
	while(str_idx < fields_str.size()) {
		string field_name = fields_str[str_idx];
		new_table_schema.addField(field_name);
		++str_idx;
	}

	table new_table (table_name, this->fm);
	this->tables_layout.add_table_and_schema(new_table, new_table_schema);
	this->fm.add_block(table_name);
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

int query_executor::insert_record(record r) {
	string table_name = r.get_table_name();
	table* t = this->tables_layout.get_table(table_name);
	if (t == nullptr) {
		return TABLE_NOT_EXIST;
	}

	schema* s = this->tables_layout.get_table_schema(table_name);
	if (s == nullptr) {
		return TABLE_SCHEMA_NOT_EXIST;
	}

	if (s->get_field_names().size() != r.get_value().size()) {
		return INSERT_RECORD_FIELD_SIZE_INVALID;
	}

	t->insert_record(r);
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

	if (parts.size() >= 4
		&& strcmp(parts[0].c_str(), "INSERT") == 0
		&& strcmp(parts[1].c_str(), "INTO") == 0
		&& strcmp(parts[2].c_str(), "TABLE") == 0) {
		string table_name = parts[3];
		vector<int> field_values;
		// Add value check
		for (int i = 4; i < parts.size(); ++i) {
			if(!checkNumber(parts[i])) {
				return "FIELD TYPE INVALID";
			}
			field_values.push_back(atoi(parts[i].c_str()));
		}

		record r = {table_name, field_values};
		if (this->insert_record(r) >= 0) {
			return "SUCCESS";
		} else {
			return "FAILED";
		}
		
	}

	return "EMPTY";
}

// vector<record> query_executor::select(string table_name, vector<predicate> preds) {

// }