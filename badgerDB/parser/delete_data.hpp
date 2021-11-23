#pragma once

#include <iostream>
#include <string>

#include "../query/predicate.hpp"

using namespace std; 

class delete_data {
    private:
        string table_name; 
        predicate pred; 
    public:
        delete_data(const string&, const predicate&);
        string get_table_name(); 
        predicate get_pred(); 
};