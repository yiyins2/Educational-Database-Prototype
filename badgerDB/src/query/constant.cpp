#include "../../include/query/constant.hpp"

constant::constant(const string& val) {
    this->str_val = make_unique<string>(val);
}

constant::constant(int val) {
    this->int_val = make_unique<int>(val);
}

constant::constant(const constant& other) {
    if (other.int_val != nullptr) {
        this->int_val = make_unique<int>(*(other.int_val)); 
    } else if (other.str_val != nullptr) {
        this->str_val = make_unique<string>(*(other.str_val)); 
    }
}

constant& constant::operator=(const constant& cons) {
    if (this != &cons) {
        if (cons.int_val != nullptr) {
            this->int_val = make_unique<int>(*(cons.int_val)); 
        } else if (cons.str_val != nullptr) {
            this->str_val = make_unique<string>(*(cons.str_val)); 
        }
    }
    return *this; 
}

string constant::as_string() {
    return *(this->str_val);
}

int constant::as_int() {
    return *(this->int_val);
}

bool constant::is_null() {
    return (this->int_val == nullptr || this->str_val == nullptr); 
}

bool constant::is_int() {
    return this->int_val != nullptr; 
}

bool constant::is_string() {
    return this->str_val != nullptr; 
}

bool operator==(const constant& lhs, const constant& rhs) {
    if (lhs.int_val != nullptr && rhs.int_val != nullptr) {
        return lhs.int_val == lhs.int_val;
    } else if (lhs.str_val != nullptr && rhs.str_val != nullptr) {
        return lhs.str_val == lhs.str_val;
    } else {
        return false;
    }
}