#include "../../include/parse/select_data.hpp"

#include <string>
#include <vector>

using namespace std;

select_data::select_data(const vector<string>& fields, const vector<string>& tables, const predicate1& pred): 
    fields(fields), tables(tables), pred(pred) {}

vector<string> select_data::get_fields() const { 
    return this->fields;
}

vector<string> select_data::get_tables() const { 
    return this->tables;
}

predicate1 select_data::get_predicate() const { 
    return this->pred; 
}

