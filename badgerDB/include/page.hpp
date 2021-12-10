#pragma once

#include <stdlib.h>

#include "record.hpp"

#include "query/constant.hpp"
#include "messages.hpp"

class page {
	private:
		int *buffer;
		vector<int> field_type; 
	public:
		page(vector<int>);
		constant* get_buffer();
		void write_record(record, int);
};