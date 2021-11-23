#pragma once

#include <iostream>
#include <string>

#include "../record/schema.hpp"

using namespace std;

class create_table_data {
    private: 
        string table_name; 
        schema sch; 
    public:
        create_table_data(const string&, const schema&); 
        string get_table_name(); 
        schema get_schema(); 
};