#include "../../include/query/expression.hpp"

expression::expression(const constant& new_exp) : cons(new_exp) {}

expression::expression(const string& new_exp) : field(new_exp) {}

expression::expression(const expression& other) : cons(other.cons), field(other.field) {}

constant expression::as_constant() {
    return this->cons; 
}

string expression::as_field() {
    return this->field; 
}

bool expression::is_field() {
    return !this->field.empty(); 
}