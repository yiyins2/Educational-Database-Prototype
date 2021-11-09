#include <stdlib.h>
#include "page.h"
using namespace std;

page::page(int buffer_size) {
	this->buffer_size = buffer_size;
	buf = (char *)calloc(buffer_size, sizeof(char));
}

char* page::get_buf() {
	return buf;
}

page::~page() {
	// delete buf;
}