#include <iostream>
#include <string>

#include "delete_data.hpp"

delete_data::delete_data(const string& table_name, const predicate& pred):
    table_name(table_name), pred(pred) {}

string delete_data::get_table_name() {
    return this->table_name;
}

predicate delete_data::get_pred() {
    return this->pred;
}