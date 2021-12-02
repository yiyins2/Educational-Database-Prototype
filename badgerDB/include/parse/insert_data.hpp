#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "../query/constant.hpp"

using namespace std; 

class insert_data {
    private:
        string table_name; 
        vector<constant> values; 
    public:
        insert_data(const string&, const vector<constant>&); 
        string get_table_name() const; 
        vector<constant> get_values() const; 
};