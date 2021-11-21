#pragma once

#include <vector>

#include "record.hpp"
#include "../file_manager/file_manager.hpp"
using namespace std;

class table {
	private:
		int record_num;
		int block_size;
		string table_name;
		file_manager fm;

		pair<int, int> get_block_id_and_offset(int);

	public:
		table() {}
		table(string, file_manager);
		int insert_record(record);
		vector<record> select();
		string get_table_name();
};