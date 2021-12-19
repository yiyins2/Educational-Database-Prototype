#include <stdlib.h>
#include <string>

#include "../include/page.hpp"
using namespace std;

// Serves as a in-memory buffer for disk content
page::page(int buffer_size) {
	this->buffer_size = buffer_size;
	buf = (int *)calloc(buffer_size, sizeof(int));
}

int* page::get_buf() {
	return buf;
}

void page::write_record(record r, int offset) {
	for (int field : r.get_value()) {
		buf[offset++] = field;
	}
}