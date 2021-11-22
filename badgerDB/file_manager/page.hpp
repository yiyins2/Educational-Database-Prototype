#pragma once

#include "../record/record.hpp"

class page {
	private:
		int *buf;
		int buffer_size;  // number of int

	public:
		page(int);
		int *get_buf();
		void write_record(record, int);
		~page();
};