#include <cstdio>
#include <cstdlib>

#include "../include/query_executor.hpp"
#include "../include/table.hpp"
#include "../include/predicate.hpp"

const int CREATE_TABLE_FIELD_TYPE_INVALID = -1;
const int TABLE_NOT_EXIST = -2;
const int TABLE_SCHEMA_NOT_EXIST = -3;
const int INSERT_RECORD_FIELD_SIZE_INVALID = -4;
const int FIELD_NOT_EXIST = -5;
const int OPERATOR_NOT_VALID = -6;

bool query_executor::checkNumber(string number)
{
	for (int i = 0; i < number.length(); i++)
		if (isdigit(number[i]) == false)
			return false;
	return true;
}

string query_executor::format_row(record r) {
	vector<int> nums = r.get_value();
	string s = to_string(nums[0]);
	for (int i = 1; i < nums.size(); ++i) {
		s += "|";
		s += to_string(nums[i]);
	}
	return s;
}

string query_executor::query_result_format(vector<string> fields, vector<record> records) {
	string s = "--------------\n";
	s += fields[0];
	for (int i = 1; i < fields.size(); ++i) {
		s += "|";
		s += fields[i];
	}
	s += '\n';

	for (int i = 0; i < records.size(); ++i) {
		record r = records[i];
		s += this->format_row(r);
		s += "\n";
	}
	s += "--------------\n";
	return s;
}

int query_executor::create_table(string table_name, vector<string> fields_str)
{
	int str_idx = 0;

	// Add fields to schema
	schema new_table_schema;
	while (str_idx < fields_str.size())
	{
		string field_name = fields_str[str_idx];
		new_table_schema.addField(field_name);
		++str_idx;
	}

	table new_table(table_name, this->fm);
	if (this->tables_layout.add_table_and_schema(new_table, new_table_schema) < 0)
	{
		return -1;
	}
	this->fm.create_data_file(table_name);
	return 0;
}

int query_executor::delete_table(string table_name)
{
	this->tables_layout.delete_table(table_name);
	if (this->fm.delete_file(table_name) < 0)
	{
		// Table not exist
		return -1;
	}
	return 0;
}

int query_executor::insert_record(record r)
{
	string table_name = r.get_table_name();
	table *t = this->tables_layout.get_table(table_name);
	if (t == nullptr)
	{
		return TABLE_NOT_EXIST;
	}

	schema *s = this->tables_layout.get_table_schema(table_name);
	if (s == nullptr)
	{
		return TABLE_SCHEMA_NOT_EXIST;
	}

	if (s->get_field_names().size() != r.get_value().size())
	{
		return INSERT_RECORD_FIELD_SIZE_INVALID;
	}

	t->insert_record(r, s->get_record_size());
	return 0;
}

int query_executor::select_records(string table_name, vector<int> field_pos, vector<predicate> preds, vector<record> &result) {
	// Check if table exists
	table *t = this->tables_layout.get_table(table_name);
	if (t == nullptr)
	{
		return TABLE_NOT_EXIST;
	}

	// Check if the field names are valid
	schema *s = this->tables_layout.get_table_schema(table_name);
	for (predicate p : preds) {
		if (!p.check_operator(p.op)) {
			return OPERATOR_NOT_VALID;
		}
	}

	result = t->select_records(field_pos, preds, s->get_record_size());
	return 0;
}

string query_executor::execute(string cmd)
{
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

	// Create table
	if (parts.size() >= 3 && strcmp(parts[0].c_str(), "CREATE") == 0 && strcmp(parts[1].c_str(), "TABLE") == 0)
	{
		string table_name = parts[2];
		vector<string> fields;
		for (int i = 3; i < parts.size(); ++i)
		{
			fields.push_back(parts[i]);
		}

		if (this->create_table(table_name, fields) < 0)
		{
			return "FAILED";
		}
		return "SUCCESS";
	}

	// Drop table
	if (parts.size() == 3 && strcmp(parts[0].c_str(), "DROP") == 0 && strcmp(parts[1].c_str(), "TABLE") == 0)
	{
		string table_name = parts[2];

		if (this->delete_table(table_name) < 0)
		{
			return "FAILED";
		}
		return "SUCCESS";
	}

	// Insert into table
	if (parts.size() >= 4 && strcmp(parts[0].c_str(), "INSERT") == 0 && strcmp(parts[1].c_str(), "INTO") == 0 && strcmp(parts[2].c_str(), "TABLE") == 0)
	{
		string table_name = parts[3];
		vector<int> field_values;
		// Add value check
		for (int i = 4; i < parts.size(); ++i)
		{
			if (!checkNumber(parts[i]))
			{
				return "FIELD TYPE INVALID";
			}
			field_values.push_back(atoi(parts[i].c_str()));
		}

		record r = {table_name, field_values};
		if (this->insert_record(r) >= 0)
		{
			return "SUCCESS";
		}
		else
		{
			return "FAILED";
		}
	}

	// Select from table
	if (parts.size() >= 4 && strcmp(parts[0].c_str(), "SELECT") == 0)
	{
		vector<string> field_names;
		int p_idx = 1;
		while (p_idx < parts.size() && strcmp(parts[p_idx].c_str(), "FROM") != 0)
		{
			field_names.push_back(parts[p_idx++]);
		}

		// Must have "TABLE table_name"
		if (p_idx++ > parts.size() - 2)
		{
			return "FAILED";
		}

		if (strcmp(parts[p_idx++].c_str(), "TABLE") != 0)
		{
			return "FAILED";
		}

		string table_name = parts[p_idx++];

		vector<predicate> preds;
		if (p_idx < parts.size() - 1 &&
			((parts.size() - p_idx - 1) % 3 != 0 || strcmp(parts[p_idx].c_str(), "WHERE") != 0))
		{
			return "FAILED";
		}

		// Get corresponding field index
		schema *s = this->tables_layout.get_table_schema(table_name);
		if (s == nullptr)
		{
			return "FAILED";
		}
		vector<string> declared_field = s->get_field_names();

		// Create predicate
		++p_idx;
		while(p_idx < parts.size()) {
			if (!checkNumber(parts[p_idx+2])) {
				return "FAILED";
			}

			string field_name = parts[p_idx];
			// Here we record the field idx in the record (the field is mentioned in the predicate)
			auto p = find(declared_field.begin(), declared_field.end(), field_name);
			if (p == declared_field.end()) {
				return "FAILED";
			}

			preds.push_back({(int)(p-declared_field.begin()), parts[p_idx+1], atoi(parts[p_idx+2].c_str())});
			p_idx += 3;
		}

		// The selected field idx in the record
		vector<int> field_pos;
		if (field_names.size() == 1 && strcmp(field_names[0].c_str(), "*") == 0) {
			for (int i = 0; i < declared_field.size(); ++i) {
				field_pos.push_back(i);
			}
		} else {
			for (string require_field : field_names)
			{
				auto p = find(declared_field.begin(), declared_field.end(), require_field);
				if (p == declared_field.end())
				{
					return "FAILED";
				}
				field_pos.push_back(p - declared_field.begin());
			}
		}
		
		vector<record> select_result;
		this->select_records(table_name, field_pos, preds, select_result);

		vector<string> selected_field_names;
		for (int idx : field_pos) {
			selected_field_names.push_back(declared_field[idx]);
		}
		string query_result = query_result_format(selected_field_names, select_result);
		return query_result;
	}

	return "EMPTY";
}

// vector<record> query_executor::select(string table_name, vector<predicate> preds) {

// }