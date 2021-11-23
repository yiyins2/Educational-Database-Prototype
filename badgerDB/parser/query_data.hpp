#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "../query/predicate.hpp"

using namespace std;

class query_data {
    private: 
        vector<string> fields; 
        vector<string> tables; 
        predicate pred; 
    public: 
        query_data(const vector<string>&, const vector<string>&, const predicate&);
        vector<string> get_fields();
        vector<string> get_tables();
        predicate get_predicate();
};