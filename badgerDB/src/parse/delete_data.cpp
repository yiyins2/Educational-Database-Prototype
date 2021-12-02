#include "../../include/parse/delete_data.hpp"

#include <string>

delete_data::delete_data(const string& table_name, const predicate1& pred):
    table_name(table_name), pred(pred) {}

string delete_data::get_table_name() const {
    return this->table_name;
}

predicate1 delete_data::get_predicate() const {
    return this->pred;
}