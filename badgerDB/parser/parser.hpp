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
#include "select_data.hpp"
#include "lexer.hpp"

#include "../include/schema.hpp"

using namespace std; 

class parser {
    private: 
        lexer lex; 
        create_constant(); 
        create_expression(); 

        schema schema_list();
        vector<string> list();
        predicate new_predicate(); 
        
    public: 
        parser(const string &); 
        create_table_data create_table(); 
        drop_table_data drop_table();
        insert_data insert_record();
        update_data update_records();
        delete_data delete_records();
        select_data select();
}; 