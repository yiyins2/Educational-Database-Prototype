#include "../include/page.hpp"

// Serves as a in-memory buffer for disk content
page::page(vector<int> field_type) {
	this->field_type = field_type;
	int total_size = 0;
	for (int i : field_type) {
		if (i == INT_TYPE) {
			total_size += sizeof(int); 
		} else {
			total_size += sizeof(char) * 32; 
		}
	}
	this->buffer = (constant*) calloc(1, total_size);
}

constant* page::get_buffer() {
	return this->buffer;
}

void page::write_record(record r, int offset) {
	for (constant field : r.get_values()) {
		if (field.is_int()) {
			this->buffer[offset++] = field.as_int();
		} else {
			this->buffer[offset++] = field.as_string();
		}
	}
}