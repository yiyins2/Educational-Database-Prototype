#include "../include/layout.hpp"

table* layout::get_table(string table_name) {
	if (this->tables_names.count(table_name) == 0) {
		return nullptr;
	}
	return &(this->tables_info[table_name]);
}

schema* layout::get_table_schema(string table_name) {
	if (this->tables_names.count(table_name) == 0) {
		return nullptr;
	}
	return &(this->tables_schema[table_name]);
}

void layout::add_table(table new_table) {
	string new_table_name = new_table.get_table_name();
	this->tables_names.insert(new_table_name);
	this->tables_info[new_table_name] = new_table;
}

void layout::add_table_schema(string new_table_name, schema new_schema) {
	this->tables_schema[new_table_name] = new_schema;
}

void layout::drop_table(string table_name) {
	if (this->tables_names.count(table_name) == 0) {
		throw runtime_error(TABLE_NOT_EXIST_MSG);
	}
	this->tables_names.erase(table_name);
	this->tables_info.erase(table_name);
}

void layout::add_table_and_schema(table t, schema s) {
	string table_name = t.get_table_name();
	if (this->tables_names.count(table_name) == 1) {
		throw runtime_error(DUPLICATE_TABLE_NAME_MSG);
	}
	this->tables_names.insert(table_name);
	this->add_table(t);
	this->add_table_schema(table_name, s);
}