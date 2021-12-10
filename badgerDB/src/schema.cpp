#include "../include/schema.hpp"

// Currently only support int type
bool schema::add_field(string field_name, int field_type) {
	// Duplicate field name
	if (find(this->field_names.begin(), this->field_names.end(), field_name) != this->field_names.end()) {
		return false;
	}
	this->field_names.push_back(field_name);
	this->field_types.push_back(field_type);
	return true;
}

int schema::get_field_idx(string field_name) {
	auto iter = find(this->field_names.begin(), this->field_names.end(), field_name);
	if (iter == this->field_names.end()) {
		return -1;
	} else {
		return iter - this->field_names.begin(); 
	}
}

vector<string> schema::get_field_names() {
	return this->field_names;
}

vector<int> schema::get_field_types() {
	return this->field_types; 
}

int schema::get_num_fields() {
	return this->field_names.size();
}

bool schema::has_field(string field_name) {
	auto iter = find(this->field_names.begin(),this->field_names.end(), field_name);
	return iter != this->field_names.end();
}