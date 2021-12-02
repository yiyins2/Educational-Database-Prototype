#include "../../include/parse/drop_table_data.hpp"

#include <string>

using namespace std;

drop_table_data::drop_table_data(const string& table_name): 
    table_name(table_name) {}

string drop_table_data::get_table_name() const {
    return this->table_name;
}
