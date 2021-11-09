#pragma once

class page {
	private:
		char *buf;
		int buffer_size;

	public:
		page(int);
		char *get_buf();
		~page();
};