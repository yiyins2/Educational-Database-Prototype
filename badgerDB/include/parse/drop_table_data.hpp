#pragma once

#include <iostream>
#include <string>

using namespace std;

class drop_table_data {
    private: 
        string table_name; 
    public:
        drop_table_data(const string&); 
        string get_table_name() const; 
};