#pragma once

#include <string>
#include <vector>

#include "predicate.hpp"
#include "record.hpp"
#include "file_manager.hpp"
#include "layout.hpp"
#include "predicate.hpp"
using namespace std;

class query_executor {
	private:
		layout tables_layout;
		file_manager fm;
		bool checkNumber(string);
		string query_result_format(vector<string>, vector<record>);
		string format_row(record);

	public:
		string execute(string cmd);
		query_executor(string db_dir){
			this->fm = file_manager(db_dir);
			this->tables_layout = layout();
		}
		query_executor() {
			this->fm = file_manager();
			this->tables_layout = layout();
		}

		int create_table(string table_name, vector<string> fields_str);
		int delete_table(string table_name);
		int insert_record(record r);
		int select_records(string table_name, vector<int> field_pos, vector<predicate> preds, vector<record> &result);
};