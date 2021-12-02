#pragma once

#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/range/iterator_range.hpp>
#include <string>
#include <set>

using namespace std; 

class lexer {
    private: 
        set<string> keywords = {
            "create", "table", "int", "varchar",
            "drop", 
            "insert", "into", "values",
            "update", "set", 
            "delete", "from", 
            "select", "from", "where",
            "join", "on", 
            "and"
        };

        typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
        tokenizer::iterator beg; 
        tokenizer::iterator end; 

    public: 
        lexer() = default;
        lexer(const string&);
        bool match_delimiter(char); 
        bool match_int_constant();
        bool match_string_constant();
        bool match_keyword(string); 
        bool match_identifier(); 
        void eat_delimiter(char); 
        int eat_int_constant(); 
        string eat_string_constant();
        void eat_keyword(string);
        string eat_identifier();
        bool next_token(); 
}; 