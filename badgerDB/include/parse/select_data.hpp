#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "../query/predicate1.hpp"

using namespace std;

class select_data {
    private: 
        vector<string> fields; 
        vector<string> tables; 
        predicate1 pred; 
    public: 
        select_data(const vector<string>&, const vector<string>&, const predicate1&);
        vector<string> get_fields() const;
        vector<string> get_tables() const;
        predicate1 get_predicate() const;
};