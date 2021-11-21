#include "schema.hpp"

// Currently only support int type

int schema::addField(string field_name) {
	// Duplicate field name
	if (find(this->field_names.begin(), this->field_names.end(), field_name) != this->field_names.end()) {
		return -1;
	}

	this->field_names.push_back(field_name);
	return 0;
}


vector<string> schema::get_field_names() {
	return this->field_names;
}

int schema::get_record_size() {
	return this->field_names.size() * sizeof(int);
}

