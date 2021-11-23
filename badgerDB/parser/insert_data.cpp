#include <iostream>
#include <string>
#include <vector>

#include "insert_data.hpp"

insert_data::insert_data(const string& table_name, const vector<string>& fields, const vector<constant>& value) :
    table_name(table_name), fields(fields), values(values) {} 

string insert_data::get_table_name() {
    return this->table_name;
}

vector<string> insert_data::get_fields() {
    return this->fields;
}

vector<constant> insert_data::get_values() {
    return this->values;
} 