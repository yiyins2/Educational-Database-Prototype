#include <stdlib.h>
#include <string>

#include "../include/page.hpp"
using namespace std;

page::page(int buffer_size) {
	this->buffer_size = buffer_size;
	buf = (int *)calloc(buffer_size, sizeof(int));
}

page::~page()
{
	// delete buf;
}

int* page::get_buf() {
	return buf;
}

void page::write_record(record r, int offset) {
	for (int field : r.get_value()) {
		buf[offset++] = field;
	}
}