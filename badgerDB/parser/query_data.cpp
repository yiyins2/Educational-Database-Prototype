#include <string>
#include <vector>
#include <set>

#include "query_data.hpp"

using namespace std;

query_data::query_data(const vector<string>& fields, const vector<string>& tables, const predicate& pred): 
    fields(fields), tables(tables), pred(pred) {}

vector<string> query_data::get_fields() { 
    return this->fields;
}

vector<string> query_data::get_tables() { 
    return this->tables;
}

predicate query_data::get_predicate()  { 
    return this->pred; 
}

