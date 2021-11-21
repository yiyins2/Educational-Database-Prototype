#pragma once

#include <string>
#include <vector>

#include "../record/predicate.hpp"
#include "../record/record.hpp"
#include "../file_manager/file_manager.hpp"
#include "../record/layout.hpp"
using namespace std;

class query_executor {
	private:
		layout tables_layout;
		file_manager fm;
		bool checkNumber(string);	

	public:
		string execute(string cmd);
		query_executor(){
			this->fm = file_manager();
			this->tables_layout = layout();
		}

		int create_table(string table_name, vector<string> fields_str);
		int delete_table(string table_name);
		int insert_record(record r);
		// vector<record> select(string table_name, vector<predicate> preds);
};