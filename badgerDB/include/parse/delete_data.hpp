#pragma once

#include <iostream>
#include <string>

#include "../query/predicate1.hpp"

using namespace std; 

class delete_data {
    private:
        string table_name; 
        predicate1 pred; 
    public:
        delete_data(const string&, const predicate1&);
        string get_table_name() const; 
        predicate1 get_predicate() const; 
};