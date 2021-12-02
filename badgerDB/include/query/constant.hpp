#pragma once

#include <string>
#include <memory>

#include "../messages.hpp"

using namespace std; 

class constant {
    private: 
        unique_ptr<string> str_val;
        unique_ptr<int> int_val;
    public: 
        constant() {};
        constant(const string&);
        constant(int);
        constant(const constant&);
        string as_string(); 
        int as_int(); 
        bool is_null(); 
        constant& operator=(const constant&);
        friend bool operator==(const constant&, const constant&);
}; 