#include <iostream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

#include "parser.hpp"

using namespace std;

void print_vector_str(const vector<string>& v) {
    for (string i: v) {
        cout << i << ' ';
    }
    cout << endl;
}

void print_vector_int(const vector<int>& v) {
    for (int i: v) {
        cout << i << ' ';
    }
    cout << endl;
}

void print_data(const string& cmd) {
    parser p = parser(cmd);
    string command_type = cmd.substr(0, cmd.find(" ")); 
    boost::algorithm::to_lower(command_type); 
    if (command_type == "create") {
        create_table_data data = p.create_table();
        cout << data.get_table_name() << endl; 
        print_vector_str(data.get_schema().get_field_names());
        print_vector_int(data.get_schema().get_field_types());
	} else if (command_type == "drop") {
        drop_table_data data = p.drop_table();
        cout << data.get_table_name() << endl; 
    } else if (command_type == "insert") {
        insert_data data = p.insert_records();
        cout << data.get_table_name() << endl; 
        print_vector_str(data.get_fields()); 
    } else if (command_type == "delete") { 
        delete_data data = p.delete_records();
        cout << data.get_table_name() << endl; 
	} else if (command_type == "update") {
        update_data data = p.update_records(); 
        cout << data.get_table_name() << endl; 
        print_vector_str(data.get_fields()); 
	} else if (command_type == "select") {
        query_data data = p.query();
        print_vector_str(data.get_fields()); 
        print_vector_str(data.get_tables()); 
	} else {
        cout << "invalid command" << endl; 
    }
}

int main() {
    cout << "---create table test---" << endl; 
    string cmd = "create table test (id varchar, col1 int, col2 varchar)";
    print_data(cmd); 

    cout << "---drop table test---" << endl; 
    cmd = "drop table test"; 
    print_data(cmd); 

    cout << "---insert test---" << endl; 
    cmd = "insert into test (col1, col2) values (1, 2)"; 
    print_data(cmd); 

    cout << "---update test---" << endl; 
    cmd = "update test set col1 = val1, col2 = val2 where"; 
    print_data(cmd); 

    cout << "---delete test---" << endl; 
    cmd = "delete from test where"; 
    print_data(cmd); 

    cout << "---query test---" << endl; 
    cmd = "select col1, col2 from tab1, tab2 where"; 
    print_data(cmd); 
}