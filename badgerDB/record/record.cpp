#include "record.hpp"

record::record(string table_name, vector<int> value) {
	this->table_name = table_name;
	this->value = value;
}

vector<int> record::get_value() {
	return this->value;
}

string record::get_table_name() {
	return this->table_name;
}