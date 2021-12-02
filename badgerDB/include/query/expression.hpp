#pragma once

#include <string> 

#include "constant.hpp"

using namespace std; 

class expression {
    private:
        constant cons;
        string field; 
    public: 
        expression() {};
        expression(const constant&); 
        expression(const string&); 
        expression(const expression&);
        constant as_constant(); 
        string as_field(); 
        bool is_field(); 
};