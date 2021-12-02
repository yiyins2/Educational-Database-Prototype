#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "../query/predicate1.hpp"
#include "../query/expression.hpp"

using namespace std; 

class update_data {
    private:
        string table_name; 
        string field; 
        expression value;
        predicate1 pred; 
    public:
        update_data(const string&, const string&, const expression&, const predicate1&);
        string get_table_name() const; 
        string get_field() const; 
        expression get_value() const;
        predicate1 get_predicate() const; 
};