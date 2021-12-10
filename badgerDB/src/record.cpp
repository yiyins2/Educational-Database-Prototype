#include "../include/record.hpp"

/*
 * Record: store table_name and value
 * The field name of each value is determined by its position
 */
record::record(string table_name, vector<constant> values) {
	this->table_name = table_name;
	this->values = values;
}

vector<constant> record::get_values() {
	return this->values;
}

string record::get_table_name() { 
	return this->table_name;
}