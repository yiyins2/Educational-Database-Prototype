#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <set>

#include "create_table_data.hpp"
#include "drop_table_data.hpp"
#include "insert_data.hpp"
#include "update_data.hpp"
#include "delete_data.hpp"
#include "query_data.hpp"
#include "lexer.hpp"

#include "../record/schema.hpp"
// #include "../query/constant.hpp"
// #include "../query/predicate.hpp"

using namespace std; 

class parser {
    private: 
        lexer lex; 
        schema schema_list();
        vector<string> listing();
        predicate new_predicate(); 
    public: 
        parser(const string &); 
        create_table_data create_table(); 
        drop_table_data drop_table();
        insert_data insert_records();
        update_data update_records();
        delete_data delete_records();
        query_data query();
}; 