#pragma once

#include <string>
#include <vector>

#include "../record/record.hpp"
#include "../query/predicate.hpp"
#include "../file_manager/file_manager.hpp"
#include "../record/layout.hpp"

#include "../parser/parser.hpp"
#include "../parser/create_table_data.hpp"
#include "../parser/drop_table_data.hpp"
#include "../parser/insert_data.hpp"
#include "../parser/update_data.hpp"
#include "../parser/delete_data.hpp"
#include "../parser/query_data.hpp"

using namespace std;

class executor {
	private:
		layout tables_layout;
		file_manager fm;

	public:
		executor();
		string execute(const string&);
		string create_table(create_table_data);
		string drop_table(drop_table_data);
		string insert_records(insert_data);
		string update_records(update_data);
		string delete_records(delete_data);
		string query(query_data);
};