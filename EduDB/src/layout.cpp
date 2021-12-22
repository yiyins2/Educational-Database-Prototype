#include "../include/layout.hpp"
table* layout::get_table(string table_name) {
	if (this->tables_names.count(table_name) == 0) {
		return nullptr;
	}
	return &(this->tables_info[table_name]);
}

schema* layout::get_table_schema(string table_name) {
	if (this->tables_names.count(table_name) == 0)
	{
		return nullptr;
	}
	return &(this->tables_schema[table_name]);
}

int layout::add_table(table new_table) {
	string new_table_name = new_table.get_table_name();
	this->tables_names.insert(new_table_name);
	this->tables_info[new_table_name] = new_table;
	return SUCCESS;
}

int layout::add_table_schema(string new_table_name, schema new_schema)
{
	this->tables_schema[new_table_name] = new_schema;
	return SUCCESS;
}

int layout::delete_table(string table_name) {
	if (this->tables_names.count(table_name) == 0) {
		return TABLE_NOT_EXIST;
	}
	this->tables_names.erase(table_name);
	this->tables_info.erase(table_name);
	return SUCCESS;
}

int layout::add_table_and_schema(table t, schema s) {
	string table_name = t.get_table_name();
	if (this->tables_names.count(table_name) == 1)
	{
		return TABLE_DUPLICATE;
	}

	this->tables_names.insert(table_name);
	this->add_table(t);
	this->add_table_schema(table_name, s);
	return SUCCESS;
}

void layout::write_to_disk() {
	string filename = "metadata";
	FILE *f = fopen(filename.c_str(), "w+");

	for (auto tablename : this->tables_names) {
		schema s = this->tables_schema[tablename];
		fputs(tablename.c_str(), f);
		fputs("\n", f);
		vector<string> fields = s.get_field_names();
		for (int i = 0; i < fields.size(); ++i) {
			if (i > 0) {
				fputs(" ", f);
			}
			fputs(fields[i].c_str(), f);
		}
		fputs("\n", f);
		// Write record num
		int record_num = this->tables_info[tablename].get_record_num();
		fputs(to_string(record_num).c_str(), f);
		fputs("\n", f);
	}

	fclose(f);	
}

void layout::load_from_disk(file_manager fm) {
	ifstream fp("./metadata");
	string tablename;
	string fields;
	string record_num;

	string delimiter = " ";

	//Checks if file is empty
	if (!fp)
	{
		return;
	}

	while (getline(fp, tablename))
	{
		// Skip newline
		getline(fp, fields);
		
		// Split fields
		string fields_str = fields;
		vector<string> parts;
		int start = 0;
		int end = fields_str.find(delimiter);
		while (end != std::string::npos)
		{
			// Remove blank spaces
			string part = fields_str.substr(start, end - start);
			part.erase(remove(part.begin(), part.end(), ' '), part.end());
			if (part.length() > 0)
			{
				parts.push_back(part);
			}

			start = end + delimiter.length();
			end = fields_str.find(delimiter, start);
		}
		parts.push_back(fields_str.substr(start, end - start));

		// Create schema
		schema s;
		for (int i = 0; i < parts.size(); ++i) {
			s.addField(parts[i]);
		}

		table new_table(tablename, fm);

		// Update my table record num
		getline(fp, record_num);
		new_table.update_record_num(atoi(record_num.c_str()));

		// Create table
		this->add_table_and_schema(new_table, s);
	}

	fp.close();
}