#include "../include/query_executor.hpp"

// Utility function
bool query_executor::check_number(string number)
{
	for (int i = 0; i < number.length(); i++)
		if (isdigit(number[i]) == false)
			return false;
	return true;
}

// Format the field values of a specific record
string query_executor::format_value_row(record r)
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

string query_executor::format_field_row(vector<string> fields) {
    string s = fields[0];
    for (int i = 1; i < fields.size(); ++i)
    {
        s += "|";
        s += fields[i];
    }
    return s;
}

// Format query result
string query_executor::query_result_format(vector<string> fields, vector<record> records)
{
	// Format field
    string s = "--------------\n";
	s += format_field_row(fields) + "\n";

	for (int i = 0; i < records.size(); ++i)
	{
		s += this->format_value_row(records[i]) + "\n";
	}
	s += "--------------";
	return s;
}

// Build predicate for select and update
// parts: string seperated by blank space
int query_executor::build_predicate(vector<string> parts, int start_idx, vector<predicate> &preds, schema *table_schema)
{
    if (start_idx == parts.size() - 1) {
        return SUCCESS;
    }

    // Since each predicate must have type: field_name operator value
    // So the number of string must be multiples of three
	int end_idx = parts.size() - 1;
	if (end_idx == start_idx || (end_idx - start_idx + 1) % 3 != 0)
	{
		return PREDICATE_INVALID;
	}

	int p_idx = start_idx;
	while (p_idx < parts.size())
	{
		// Check if the field is a number
		if (!check_number(parts[p_idx + 2]))
		{
			return PREDICATE_NUMBER_INVALID;
		}

		string field_name = parts[p_idx];
		int field_idx = table_schema->get_field_idx(field_name);
		if (field_idx < 0)
		{
			return PREDICARE_FIELD_NOT_FOUND;
		}

		preds.push_back({field_idx, parts[p_idx + 1], atoi(parts[p_idx + 2].c_str())});
		p_idx += 3;
	}
	return SUCCESS;
}

vector<string> query_executor::split_with_delimiter(string cmd, string delimiter) {
    vector<string> parts;
    int start = 0;
    int end = cmd.find(delimiter);
    while (end != std::string::npos)
    {
        // Remove blank spaces
        string part = cmd.substr(start, end - start);
        part.erase(remove(part.begin(), part.end(), ' '), cmd.end());
        if (part.length() > 0) {
            parts.push_back(part);
        }

        start = end + delimiter.length();
        end = cmd.find(delimiter, start);
    }
    parts.push_back(cmd.substr(start, end - start));
    return parts;
}

int query_executor::create_table(string table_name, vector<string> fields_str)
{
	// Add fields to schema
	schema new_table_schema;
    for (string field_name : fields_str)
	{
		new_table_schema.addField(field_name);
	}

    // Add table and schema to layout (internal metadata)
	table new_table(table_name, this->fm);
	if (this->tables_layout.add_table_and_schema(new_table, new_table_schema) == TABLE_DUPLICATE)
	{
		return TABLE_DUPLICATE;
	}
    this->fm.create_data_file(table_name);
    return SUCCESS;
}

int query_executor::delete_table(string table_name)
{
    // Delete internal metadata
	this->tables_layout.delete_table(table_name);
    // Remove data file
	this->fm.delete_file(table_name);
	return SUCCESS;
}

int query_executor::insert_record(record r)
{
	string table_name = r.get_table_name();
	table *t = this->tables_layout.get_table(table_name);
    // Make sure that the table exists
	if (t == nullptr)
	{
		return TABLE_NOT_EXIST;
	}

    // Make sure that the table schema exists
	schema *s = this->tables_layout.get_table_schema(table_name);
	if (s == nullptr)
	{
		return TABLE_SCHEMA_NOT_EXIST;
	}

    // Make sure that the new record has complete value fields
	if (s->get_field_names().size() != r.get_value().size())
	{
		return INSERT_RECORD_FIELD_SIZE_INVALID;
	}

	return t->insert_record(r, s->get_record_size());
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
	return SUCCESS;
}

int query_executor::update_records(string table_name, vector<update_record> update_records_info, vector<predicate> preds)
{
	table *t = this->tables_layout.get_table(table_name);
	schema *s = this->tables_layout.get_table_schema(table_name);
	return t->update_records(update_records_info, preds, s->get_record_size());
}

// Parse the command, do some check and also pack necessary structure
string query_executor::execute(string cmd)
{
	std::string delim = " ";
	vector<string> parts = split_with_delimiter(cmd, " ");

	if (parts.size() == 1 && strcmp(parts[0].c_str(), "EXIT") == 0) {
		// Store metadata into file
		this->tables_layout.write_to_disk();	
		return "EXIT";
	}

	// Create table
	if (parts.size() >= 3
        && strcmp(parts[0].c_str(), "CREATE") == 0
        && strcmp(parts[1].c_str(), "TABLE") == 0)
	{
		string table_name = parts[2];

		vector<string> declared_fields;
		for (int i = 3; i < parts.size(); ++i)
		{
            declared_fields.push_back(parts[i]);
		}

		int ret_val = this->create_table(table_name, declared_fields);
        switch(ret_val) {
            case SUCCESS:
                return success_msg;
            case TABLE_DUPLICATE:
                return table_duplicate_msg;
            default:
                return unhandled_msg;
        }
	}

	// Drop table
	if (parts.size() == 3
        && strcmp(parts[0].c_str(), "DROP") == 0
        && strcmp(parts[1].c_str(), "TABLE") == 0)
	{
		string table_name = parts[2];

		this->delete_table(table_name);
		return success_msg;
	}

	// Insert into table
	if (parts.size() >= 4
        && strcmp(parts[0].c_str(), "INSERT") == 0
        && strcmp(parts[1].c_str(), "INTO") == 0
        && strcmp(parts[2].c_str(), "TABLE") == 0)
	{
		string table_name = parts[3];

		vector<int> field_values;
        // Check if all given record field values are integer
		for (int i = 4; i < parts.size(); ++i)
		{
			if (!check_number(parts[i]))
			{
				return insert_record_field_value_not_int_msg;
			}

			field_values.push_back(atoi(parts[i].c_str()));
		}

        // Execute the insert
		record r = {table_name, field_values};
        int ret_val = this->insert_record(r);
        switch (ret_val) {
            case SUCCESS:
                return success_msg;
            case TABLE_NOT_EXIST:
                return table_not_exist_msg;
            case TABLE_SCHEMA_NOT_EXIST:
                return schema_not_exist_msg;
            case FAILED_TO_READ_BLOCK:
                return failed_to_read_block_msg;
            case FAILED_TO_WRITE_BLOCK:
                return failed_to_write_block_msg;
            default:
                return unhandled_msg;
        }
	}

	// Select from table
	if (parts.size() >= 4 && strcmp(parts[0].c_str(), "SELECT") == 0)
	{
        // Store all selected field names
		vector<string> select_field_names;
		int p_idx = 1;
		while (p_idx < parts.size()
            && strcmp(parts[p_idx].c_str(), "FROM") != 0)
		{
            select_field_names.push_back(parts[p_idx++]);
		}

		// Must have "TABLE table_name"
		if (p_idx++ > parts.size() - 2
            || strcmp(parts[p_idx++].c_str(), "TABLE") != 0)
		{
			return command_not_valid_msg;
		}

        // Get table name
		string table_name = parts[p_idx++];
        table *t = this->tables_layout.get_table(table_name);
        if (t == nullptr) {
            return table_not_exist_msg;
        }

        // If there is predicate, check whether there is where
		if (p_idx < parts.size() - 1 &&
			strcmp(parts[p_idx].c_str(), "WHERE") != 0)
		{
			return command_not_valid_msg;
		}

		// Get corresponding field index
		schema *s = this->tables_layout.get_table_schema(table_name);
		if (s == nullptr)
		{
			return schema_not_exist_msg;
		}
		vector<string> declared_field = s->get_field_names();

		// Create predicate
		vector<predicate> preds;
		if (p_idx < parts.size()) {
           int ret_val = build_predicate(parts, p_idx+1, preds, s);
            switch (ret_val) {
                case PREDICARE_FIELD_NOT_FOUND:
                    return predicate_field_not_found_msg;
                case PREDICATE_NUMBER_INVALID:
                    return predicate_field_not_number_msg;
                case PREDICATE_INVALID:
                    return predicate_invalid;
            }
		}

        // Convert selected_field_names to corresponding index using schema
		vector<int> field_pos;
		if (select_field_names.size() == 1
            && strcmp(select_field_names[0].c_str(), "*") == 0)
		{
            // All fields are selected
			for (int i = 0; i < declared_field.size(); ++i)
			{
				field_pos.push_back(i);
			}
		} else {
			for (string require_field : select_field_names)
			{
				auto p = find(declared_field.begin(), declared_field.end(), require_field);
				if (p == declared_field.end())
				{
					return select_field_not_found_msg;
				}
				field_pos.push_back(p - declared_field.begin());
			}
		}

        // Get select records
		vector<record> select_result;
		int ret_val = this->select_records(table_name, field_pos, preds, select_result);
        switch (ret_val) {
            case TABLE_NOT_EXIST:
                return table_not_exist_msg;
            case OPERATOR_NOT_VALID:
                return operator_not_valid_msg;
            case SUCCESS:
                // Continue execution
                break;
            default:
                return unhandled_msg;
        }

        if (select_field_names.size() == 1 && strcmp(select_field_names[0].c_str(), "*") == 0) {
            select_field_names = s->get_field_names();
        }

		string query_result = query_result_format(select_field_names, select_result);
		return query_result;
	}

	// Update cmd: eg: UPDATE t1 SET f1 = 3 f2 = 6 WHERE f1 > 2
	if (strcmp(parts[0].c_str(), "UPDATE") == 0)
	{
		int cmd_part_idx = 1;
		if (cmd_part_idx >= parts.size())
		{
			return command_not_valid_msg;
		}

		string table_name = parts[cmd_part_idx++];
		schema *table_schema = this->tables_layout.get_table_schema(table_name);
		if (table_schema == nullptr)
		{
			return table_not_exist_msg;
		}

		if (cmd_part_idx >= parts.size()
            || strcmp(parts[cmd_part_idx++].c_str(), "SET") != 0)
		{
			return command_not_valid_msg;
		}

        auto where_pos_iter = find(parts.begin(), parts.end(), "WHERE");

		// Pack update fields
		vector<update_record> update_records;
        int where_idx = parts.size();
        if (where_pos_iter != parts.end()) {
            where_idx = where_pos_iter - parts.begin();
            if ((where_pos_iter - parts.begin()) % 3 != 0) {
                return command_not_valid_msg;
            }
        }

		for (int i = cmd_part_idx; i < where_idx; i += 3)
		{
			string update_field_name = parts[i];
			int update_field_pos_idx = table_schema->get_field_idx(update_field_name);

			if (update_field_pos_idx < 0)
			{
				return select_field_not_found_msg;
			}

			int update_field_new_value = atoi(parts[i + 2].c_str());
			update_record ur = {update_field_pos_idx, update_field_new_value};
			update_records.push_back(ur);
		}

        // Build predicate
		vector<predicate> preds;
        int ret_val = build_predicate(parts, where_idx + 1, preds, table_schema);
        switch (ret_val) {
            case PREDICARE_FIELD_NOT_FOUND:
                return predicate_field_not_found_msg;
            case PREDICATE_NUMBER_INVALID:
                return predicate_field_not_number_msg;
            case PREDICATE_INVALID:
                return predicate_invalid;
        }

        ret_val = this->update_records(table_name, update_records, preds);
        switch (ret_val) {
            case SUCCESS:
                return success_msg;
            case FAILED_TO_READ_BLOCK:
                return failed_to_read_block_msg;
            case FAILED_TO_WRITE_BLOCK:
                return failed_to_write_block_msg;
            default:
                return unhandled_msg;
        }
	}

	return command_not_valid_msg;
}