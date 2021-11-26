#pragma once

#include <string>
#include <vector>

#include "predicate.hpp"
#include "record.hpp"
#include "file_manager.hpp"
#include "layout.hpp"
#include "table.hpp"
#include "predicate.hpp"
#include "update_record.hpp"

using namespace std;

class query_executor
{
private:
	layout tables_layout;
	file_manager fm;
	bool check_number(string);
	string query_result_format(vector<string>, vector<record>);
	string format_row(record);
	int build_predicate(vector<string>, int, vector<predicate> &, schema *);

public:
	string execute(string cmd);
	query_executor(string db_dir)
	{
		this->fm = file_manager(db_dir);
		this->tables_layout = layout();
	}
	query_executor()
	{
		this->fm = file_manager();
		this->tables_layout = layout();
	}

	int create_table(string table_name, vector<string> fields_str);
	int delete_table(string table_name);
	int insert_record(record r);
	int select_records(string table_name, vector<int> field_pos, vector<predicate> preds, vector<record> &result);
	int update_records(string table_name, vector<update_record> update_records_info, vector<predicate> preds);
};