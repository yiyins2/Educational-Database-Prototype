#include <cstdio>
#include <cstdlib>

#include "../include/query_executor.hpp"

const int CREATE_TABLE_FIELD_TYPE_INVALID = -1;
const int TABLE_NOT_EXIST = -2;
const int TABLE_SCHEMA_NOT_EXIST = -3;
const int INSERT_RECORD_FIELD_SIZE_INVALID = -4;
const int FIELD_NOT_EXIST = -5;
const int OPERATOR_NOT_VALID = -6;

// Utility function
bool query_executor::check_number(string number)
{
	for (int i = 0; i < number.length(); i++)
		if (isdigit(number[i]) == false)
			return false;
	return true;
}

string query_executor::format_row(record r)
{
	vector<int> nums = r.get_value();
	string s = to_string(nums[0]);
	for (int i = 1; i < nums.size(); ++i)
	{
		s += "|";
		s += to_string(nums[i]);
	}
	return s;
}

string query_executor::query_result_format(vector<string> fields, vector<record> records)
{
	string s = "--------------\n";
	s += fields[0];
	for (int i = 1; i < fields.size(); ++i)
	{
		s += "|";
		s += fields[i];
	}
	s += '\n';

	for (int i = 0; i < records.size(); ++i)
	{
		record r = records[i];
		s += this->format_row(r);
		s += "\n";
	}
	s += "--------------";
	return s;
}

// Build predicate for select and update
int query_executor::build_predicate(vector<string> parts, int start_idx, vector<predicate> &preds, schema *table_schema)
{
	int end_idx = parts.size() - 1;
	if (end_idx == start_idx || (end_idx - start_idx + 1) % 3 != 0)
	{
		return -1;
	}

	int p_idx = start_idx;
	while (p_idx < parts.size())
	{
		// Check if the field is a number
		if (!check_number(parts[p_idx + 2]))
		{
			return -1;
		}

		string field_name = parts[p_idx];
		int field_idx = table_schema->get_field_idx(field_name);
		if (field_idx < 0)
		{
			return -1;
		}

		preds.push_back({field_idx, parts[p_idx + 1], atoi(parts[p_idx + 2].c_str())});
		p_idx += 3;
	}
	return 0;
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

int query_executor::select_records(string table_name, vector<int> field_pos, vector<predicate> preds, vector<record> &result)
{
	// Check if table exists
	table *t = this->tables_layout.get_table(table_name);
	if (t == nullptr)
	{
		return TABLE_NOT_EXIST;
	}

	// Check if the field names are valid
	schema *s = this->tables_layout.get_table_schema(table_name);
	for (predicate p : preds)
	{
		if (!p.check_operator(p.op))
		{
			return OPERATOR_NOT_VALID;
		}
	}

	result = t->select_records(field_pos, preds, s->get_record_size());
	return 0;
}

int query_executor::update_records(string table_name, vector<update_record> update_records_info, vector<predicate> preds)
{
	table *t = this->tables_layout.get_table(table_name);
	schema *s = this->tables_layout.get_table_schema(table_name);
	if (t->update_records(update_records_info, preds, s->get_record_size()) < 0)
	{
		return -1;
	}
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
			if (!check_number(parts[i]))
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
		vector<predicate> preds;
		if (p_idx < parts.size() && build_predicate(parts, p_idx+1, preds, s) < 0)
		{
			return "Command not valid";
		}

		// The selected field idx in the record
		vector<int> field_pos;
		if (field_names.size() == 1 && strcmp(field_names[0].c_str(), "*") == 0)
		{
			for (int i = 0; i < declared_field.size(); ++i)
			{
				field_pos.push_back(i);
			}
		}
		else
		{
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
		for (int idx : field_pos)
		{
			selected_field_names.push_back(declared_field[idx]);
		}
		string query_result = query_result_format(selected_field_names, select_result);
		return query_result;
	}

	// Update cmd: eg: UPDATE t1 SET f1 = 3 f2 = 6 WHERE f1 > 2
	if (strcmp(parts[0].c_str(), "UPDATE") == 0)
	{
		int cmd_part_idx = 1;
		if (cmd_part_idx >= parts.size())
		{
			return "FAILED";
		}

		string table_name = parts[cmd_part_idx++];
		schema *table_schema = this->tables_layout.get_table_schema(table_name);
		if (table_schema == nullptr)
		{
			return "Table " + table_name + " Not Exist";
		}

		if (cmd_part_idx >= parts.size() || strcmp(parts[cmd_part_idx++].c_str(), "SET") != 0)
		{
			return "FAILED";
		}

		auto where_pos_iter = find(parts.begin(), parts.end(), "WHERE");
		if (cmd_part_idx >= parts.size() || where_pos_iter == parts.end() || (where_pos_iter - parts.begin() - cmd_part_idx) % 3 != 0 || where_pos_iter - parts.begin() == cmd_part_idx)
		{
			return "Command Not Valid";
		}

		// Pack update fields
		vector<update_record> update_records;
		int where_idx = where_pos_iter - parts.begin();
		for (int i = cmd_part_idx; i < where_idx; i += 3)
		{
			string update_field_name = parts[i];
			int update_field_pos_idx = table_schema->get_field_idx(update_field_name);

			if (update_field_pos_idx < 0)
			{
				return "Field " + update_field_name + " not found";
			}

			int update_field_new_value = atoi(parts[i + 2].c_str());
			update_record ur = {update_field_pos_idx, update_field_new_value};
			update_records.push_back(ur);
		}

		vector<predicate> preds;
		if (build_predicate(parts, where_idx + 1, preds, table_schema) < 0)
		{
			return "Command not valid";
		}

		if (this->update_records(table_name, update_records, preds) < 0)
		{
			return "FAILED";
		} else {
            return "SUCCESS";
        }
	}

	return "COMMAND NOT VALID";
}