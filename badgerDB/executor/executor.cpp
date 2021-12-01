#include <cstdio>
#include <cstdlib>
#include <boost/algorithm/string.hpp>

#include "executor.hpp"
#include "../record/table.hpp"

using namespace std; 

// int CREATE_TABLE_FIELD_TYPE_INVALID = -1;
// int TABLE_NOT_EXIST = -2;
// int TABLE_SCHEMA_NOT_EXIST = -3;
// int INSERT_RECORD_FIELD_SIZE_INVALID = -4;

executor::executor() {
	this->fm = file_manager();
	this->tables_layout = layout();
}

string executor::create_table(create_table_data data) {
	int str_idx = 0;
	string table_name = data.get_table_name();
	table new_table(table_name, this->fm);
	if(this->tables_layout.add_table_and_schema(new_table, data.get_schema()) < 0) {
		return "failed to create " + table_name;
	}
	this->fm.create_data_file(table_name);
	return "successfully created " + table_name;
}

string executor::drop_table(drop_table_data data) {
	string table_name = data.get_table_name(); 
	this->tables_layout.drop_table(table_name);
	// Table does not exist
	if (this->fm.delete_file(table_name) < 0) {
		return "failed to delete " + table_name;
	}
	return "successfully deleted " + table_name;
}

// bool executor::insert_records(insert_data data) {
// 	string table_name = data.get_table_name();
// 	table* t = this->tables_layout.get_table(table_name);
// 	if (t == nullptr) {
// 		throw runtime_error("table does not exit");
// 	}

// 	schema* s = this->tables_layout.get_table_schema(table_name);
// 	if (s == nullptr) {
// 		return TABLE_SCHEMA_NOT_EXIST;
// 	}

// 	if (s->get_field_names().size() != r.get_value().size()) {
// 		return INSERT_RECORD_FIELD_SIZE_INVALID;
// 	}

// 	t->insert_record(r);
// 	return 0;
// }

// bool executor::insert_records(record r) {
// 	string table_name = r.get_table_name();
// 	table* t = this->tables_layout.get_table(table_name);
// 	if (t == nullptr) {
// 		return TABLE_NOT_EXIST;
// 	}

// 	schema* s = this->tables_layout.get_table_schema(table_name);
// 	if (s == nullptr) {
// 		return TABLE_SCHEMA_NOT_EXIST;
// 	}

// 	if (s->get_field_names().size() != r.get_value().size()) {
// 		return INSERT_RECORD_FIELD_SIZE_INVALID;
// 	}

// 	t->insert_record(r);
// 	return 0;
// }

// string executor::execute(string cmd) {

// 	std::string delim = " ";
// 	vector<string> parts;

// 	int start = 0;
// 	int end = cmd.find(delim);
// 	while (end != std::string::npos)
// 	{
// 		parts.push_back(cmd.substr(start, end - start));
// 		start = end + delim.length();
// 		end = cmd.find(delim, start);
// 	}
// 	parts.push_back(cmd.substr(start, end - start));

// 	if (parts.size() >= 3 && strcmp(parts[0].c_str(), "CREATE") == 0 && strcmp(parts[1].c_str(), "TABLE") == 0) {
// 		string table_name = parts[2];
// 		vector<string> fields;
// 		for (int i = 3; i < parts.size(); ++i) {
// 			fields.push_back(parts[i]);
// 		}

// 		if (this->create_table(table_name, fields) < 0) {
// 			return "FAILED";
// 		}
// 		return "SUCCESS";
// 	}

// 	if (parts.size() >= 4
// 		&& strcmp(parts[0].c_str(), "INSERT") == 0
// 		&& strcmp(parts[1].c_str(), "INTO") == 0
// 		&& strcmp(parts[2].c_str(), "TABLE") == 0) {
// 		string table_name = parts[3];
// 		vector<int> field_values;
// 		// Add value check
// 		for (int i = 4; i < parts.size(); ++i) {
// 			if(!checkNumber(parts[i])) {
// 				return "FIELD TYPE INVALID";
// 			}
// 			field_values.push_back(atoi(parts[i].c_str()));
// 		}

// 		record r = {table_name, field_values};
// 		if (this->insert_record(r) >= 0) {
// 			return "SUCCESS";
// 		} else {
// 			return "FAILED";
// 		}
		
// 	}
// 	return "EMPTY";
// }

string executor::insert_records(insert_data data) {
	return "not yet developed";
}

string executor::delete_records(delete_data data) {
	return "not yet developed";
}

string executor::update_records(update_data data) {
	return "not yet developed";
}

string executor::query(query_data data) {
	return "not yet developed";
}

string executor::execute(const string& cmd) {
	parser p = parser(cmd);
    string command_type = cmd.substr(0, cmd.find(" ")); 
    boost::algorithm::to_lower(command_type); 
    if (command_type == "create") {
        create_table_data data = p.create_table();
		create_table(data);
	} else if (command_type == "drop") {
        drop_table_data data = p.drop_table();
		drop_table(data);
    } else if (command_type == "insert") {
        insert_data data = p.insert_records();
		insert_records(data);
    } else if (command_type == "delete") { 
        delete_data data = p.delete_records();
		delete_records(data);
	} else if (command_type == "update") {
        update_data data = p.update_records(); 
		update_records(data);
	} else if (command_type == "select") {
        query_data data = p.query();
		query(data);
	} else {
        return "invalid command"; 
    }
}