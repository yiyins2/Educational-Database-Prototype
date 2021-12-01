#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "../query/predicate.hpp"

using namespace std;

class select_data {
    private: 
        vector<string> fields; 
        vector<string> tables; 
        predicate pred; 
    public: 
        select_data(const vector<string>&, const vector<string>&, const predicate&);
        vector<string> get_fields();
        vector<string> get_tables();
        predicate get_predicate();
};