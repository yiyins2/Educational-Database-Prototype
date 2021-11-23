#include "schema.hpp"

// Currently only support int type

bool schema::add_field(string new_field_name, int new_field_type) {
	// Duplicate field name
	if (find(this->field_names.begin(), this->field_names.end(), new_field_name) != this->field_names.end()) {
		return false;
	}

	this->field_names.push_back(new_field_name);
	this->field_types.push_back(new_field_type);
	return true;
}


vector<string> schema::get_field_names() {
	return this->field_names;
}

vector<int> schema::get_field_types() {
	return this->field_types;
}

int schema::get_record_size() {
	return this->field_types.size() * sizeof(int);
}

