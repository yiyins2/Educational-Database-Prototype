#pragma once

#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "file_manager.hpp"
#include "record.hpp"
#include "layout.hpp"
#include "table.hpp"

// TODO: 
// #include "update_record.hpp"

#include "messages.hpp"

#include "predicate.hpp"

#include "parse/parser.hpp"
#include "parse/create_table_data.hpp"
#include "parse/drop_table_data.hpp"
#include "parse/insert_data.hpp"
#include "parse/update_data.hpp"
#include "parse/delete_data.hpp"
#include "parse/select_data.hpp"

using namespace std;

class query_executor
{
private:
	file_manager fm;
	layout tables_layout;
	
	bool check_number(string);
	string query_result_format(vector<string>, vector<record>);
	string format_value_row(record);
    string format_field_row(vector<string>);
    vector<string> split_with_delimiter(string, string);
	int build_predicate(vector<string>, int, vector<predicate> &, schema *);

public:
	string execute(const string&);
	query_executor(string db_dir) {
		this->fm = file_manager(db_dir);
		this->tables_layout = layout();
	}
	query_executor() {
		this->fm = file_manager();
		this->tables_layout = layout();
	}

	string create_table(const create_table_data&);
	string drop_table(const drop_table_data&);
    string insert_record(const insert_data&);
	string update_records(const update_data&);
	string delete_records(const delete_data&);
	string select_records(const select_data&);
};