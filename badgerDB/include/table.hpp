#pragma once

#include <vector>

#include "record.hpp"
#include "file_manager.hpp"
#include "predicate.hpp"
#include "update_record.hpp"
#include "page.hpp"
using namespace std;

class table {
	private:
		int record_num;
		int block_size;
		string table_name;
		file_manager fm;

		pair<int, int> get_block_id_and_offset(int, int);
		bool check_predicate(vector<predicate>, record);
		bool check_one_field(int, string, int);

	public:
		table() {}
		table(string, file_manager);
		string get_table_name();

		int insert_record(record, int);
		int update_records(vector<update_record>, vector<predicate>, int);
		vector<record> select_records(vector<int>, vector<predicate>, int);
};