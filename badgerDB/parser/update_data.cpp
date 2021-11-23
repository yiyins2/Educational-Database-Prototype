#include <iostream>
#include <string>
#include <vector>

#include "update_data.hpp"

update_data::update_data(const string& table_name, const vector<string>& fields, const vector<constant>& values, const predicate& pred): 
    table_name(table_name), fields(fields), values(values), pred(pred) {}

string update_data::get_table_name() {
    return this->table_name; 
}

vector<string> update_data::get_fields() {
    return this->fields;
} 

vector<constant> update_data::get_values() {
    return this->values;
}

predicate update_data::get_pred() {
    return this->pred;
}