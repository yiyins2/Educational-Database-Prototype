#include "select_data.hpp"

#include <string>
#include <vector>
#include <set>

using namespace std;

select_data::select_data(const vector<string>& fields, const vector<string>& tables, const predicate& pred): 
    fields(fields), tables(tables), pred(pred) {}

vector<string> select_data::get_fields() { 
    return this->fields;
}

vector<string> select_data::get_tables() { 
    return this->tables;
}

predicate select_data::get_predicate()  { 
    return this->pred; 
}

