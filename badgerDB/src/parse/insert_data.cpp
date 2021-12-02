#include "../../include/parse/insert_data.hpp"

#include <string>
#include <vector>


insert_data::insert_data(const string& table_name, const vector<constant>& value) :
    table_name(table_name), values(values) {} 

string insert_data::get_table_name() const {
    return this->table_name;
}

vector<constant> insert_data::get_values() const {
    return this->values;
} 