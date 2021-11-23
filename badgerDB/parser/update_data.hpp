#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "../query/predicate.hpp"
#include "../query/constant.hpp"

using namespace std; 

class update_data {
    private:
        string table_name; 
        vector<string> fields; 
        vector<constant> values;
        predicate pred; 
    public:
        update_data(const string&, const vector<string>&, const vector<constant>&, const predicate&);
        string get_table_name(); 
        vector<string> get_fields(); 
        vector<constant> get_values();
        predicate get_pred(); 
};