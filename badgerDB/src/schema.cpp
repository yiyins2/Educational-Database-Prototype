#include "../include/schema.hpp"

// Currently only support int type
int schema::addField(string field_name) {
	// Duplicate field name
	if (find(this->field_names.begin(), this->field_names.end(), field_name) != this->field_names.end()) {
		return DUPLICATE_FIELD;
	}

	this->field_names.push_back(field_name);
	return SUCCESS;
}

int schema::get_field_idx(string field_name) {
	auto iter = find(this->field_names.begin(), this->field_names.end(), field_name);
	if (iter == this->field_names.end()) {
		return FIELD_NOT_EXIST;
	} else {
		return iter - this->field_names.begin();
	}
}

vector<string> schema::get_field_names() {
	return this->field_names;
}

int schema::get_record_size() {
	return this->field_names.size();
}

bool schema::has_field(string field_name) {
	auto iter = find(this->field_names.begin(),this->field_names.end(), field_name);
	return iter != this->field_names.end();
}