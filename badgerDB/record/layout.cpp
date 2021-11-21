#include "layout.hpp"

table* layout::get_table(string table_name) {
	if (this->tables_names.count(table_name) == 0) {
		return nullptr;
	}
	return &(this->tables_info[table_name]);
}

int layout::add_table(table new_table) {
	string new_table_name = new_table.get_table_name();

	if (this->tables_names.count(new_table_name) == 1) {
		// Duplicate table name
		return -1;
	}

	this->tables_info[new_table_name] = new_table;
	return 0;
}

int layout::delete_table(string table_name) {
	if (this->tables_names.count(table_name) == 0) {
		return -1;
	}
	this->tables_names.erase(table_name);
	this->tables_info.erase(table_name);
	return 0;
}
