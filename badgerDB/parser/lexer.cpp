#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/range/iterator_range.hpp>
#include <string>

#include "lexer.hpp"

using namespace std;

lexer::lexer(const string& cmd) {
    boost::char_separator<char> sep;
    tokenizer tokens(cmd, sep);

    this->beg = tokens.begin();
    this->end = tokens.end();
}

bool lexer::match_delimiter(char d) {
    return (*this->beg).length() == 1 && (*this->beg)[0] == d;
}

bool lexer::match_int_constant() {
    for (string::size_type i = 0; i < (*this->beg).length(); ++i) {
        if (isdigit((*this->beg)[i]) == 0) {
            return false;
        }
    }
    return true;
}

bool lexer::match_string_constant() {
    for (string::size_type i = 0; i < (*this->beg).length(); ++i) {
        if (isalpha((*this->beg)[i]) == 0 | (*this->beg)[i] != '_') {
            return false;
        }
    }
    return true; 
}

bool lexer::match_keyword(string kw) {
    string beg_lower = boost::algorithm::to_lower_copy(*this->beg);
    return beg_lower == kw;
}

bool lexer::match_identifier() {
    return this->keywords.count(*this->beg) == 0;
}

void lexer::eat_delimiter(char d) {
    if (!match_delimiter(d)) {
        throw runtime_error("bad syntax exception: delimiter");
    }
    next_token(); 
}

int lexer::eat_int_constant() {
    if (!match_int_constant()) {
        throw runtime_error("bad syntax exception: int constant");
    }
    int temp = stoi(*this->beg); 
    next_token(); 
    return temp; 
}

string lexer::eat_string_constant() {
    if (!match_string_constant()) {
        throw runtime_error("bad syntax exception: string constant");
    }
    string temp = *this->beg;
    next_token(); 
    return temp; 
}

void lexer::eat_keyword(string kw) {
    if (!match_keyword(kw)) {
        throw runtime_error("bad syntax exception: keyword");
    }
    next_token(); 
}

string lexer::eat_identifier(){
    if (!match_identifier()) {
        throw runtime_error("bad syntax exception: identifier");
    }
    string temp = *this->beg;
    next_token(); 
    return temp; 
}

bool lexer::next_token() {
    if (this->beg != this->end) {
        ++this->beg; 
        return true;
    }
    return false;
}

