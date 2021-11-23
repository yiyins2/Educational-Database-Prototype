#include <iostream>
#include <string>

#include "create_table_data.hpp"

using namespace std;

create_table_data::create_table_data(const string& table_name, const schema& sch):
    table_name(table_name), sch(sch) {}

string create_table_data::get_table_name() {
    return this->table_name;
}

schema create_table_data::get_schema() {
    return this->sch;
}