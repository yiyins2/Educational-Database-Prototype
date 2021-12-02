#include "../../include/parse/update_data.hpp"

#include <string>
#include <vector>

update_data::update_data(const string& table_name, const string& field, const expression& value, const predicate1& pred): 
    table_name(table_name), field(field), value(value), pred(pred) {}

string update_data::get_table_name() const {
    return this->table_name; 
}

string update_data::get_field() const {
    return this->field; 
} 

expression update_data::get_value() const {
    return this->value;
}

predicate1 update_data::get_predicate() const {
    return this->pred;
}