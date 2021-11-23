#include <iostream>
#include <string>

#include "drop_table_data.hpp"

using namespace std;

drop_table_data::drop_table_data(const string& table_name): 
    table_name(table_name) {}

string drop_table_data::get_table_name() {
    return this->table_name;
}
