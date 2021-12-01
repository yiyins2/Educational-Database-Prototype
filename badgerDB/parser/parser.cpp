#include "parser.hpp"

#include <string>
#include <vector>
#include <set>

using namespace std;

// TODO
int schema_int = 0;
int schema_varchar = 1;

parser::parser(const string &cmd) {
    this->lex = lexer(cmd); 
}

constant parser::create_constant() {
    if (lex.match_int_constant()) {
        return constant(lex.eat_int_constant());
    } else {
        return constant(lex.eat_string_constant());
    }
}

predicate parser::create_predicate() {
    predicate pred = predicate(term()); 
    if (lex.match_keyword("and")) {
        lex.eat_keyword("and")
        pred.con_join_with(predicate()); 
    }
    return pred; 
}


// ceate table table_name (col1 datatype, ...)
create_table_data parser::create_table() {
    this->lex.eat_keyword("create");
    this->lex.eat_keyword("table"); 
    string table_name = this->lex.eat_identifier();

    this->lex.eat_delimiter('('); 
    schema sch = schema_list(); 
    this->lex.eat_delimiter(')');

    return create_table_data(table_name, sch);
}

schema parser::schema_list() {
    schema sch;
    while (!this->lex.match_delimiter(')')) {
        string field_name = this->lex.eat_identifier(); 
        if (this->lex.match_keyword("int")) {
            this->lex.eat_keyword("int"); 
            sch.add_field(field_name, schema_int); 
        }
        if (this->lex.match_keyword("varchar")) {
            this->lex.eat_keyword("varchar"); 
            sch.add_field(field_name, schema_varchar); 
        }
        if (this->lex.match_delimiter(',')) {
            this->lex.eat_delimiter(',');
        }
    }
    return sch; 
}

// drop table table_name 
drop_table_data parser::drop_table() {
    this->lex.eat_keyword("drop");
    this->lex.eat_keyword("table"); 
    string table_name = this->lex.eat_identifier();
    return drop_table_data(table_name); 
}

// insert into table_name (col1, ...) values (val1, ...)
// simpler version: insert into table_name values (val1, ...)
insert_data parser::insert_record() {
    this->lex.eat_keyword("insert");
    this->lex.eat_keyword("into"); 
    string table_name = this->lex.eat_identifier();

    // this->lex.eat_delimiter('('); 
    // vector<string> fields = list(); 
    // this->lex.eat_delimiter(')');

    this->lex.eat_keyword("values"); 
    this->lex.eat_delimiter('('); 
    vector<constant> values;
    while (!this->lex.match_delimiter(')')) {
        values.push_back(create_constant());
        if (this->lex.match_delimiter(',')) {
            this->lex.eat_delimiter(',');
        }
    }
    this->lex.eat_delimiter(')');

    return insert_data(table_name, values);
}

// update table_name set col1 = val1, ... where 
update_data parser::update_records() {
    this->lex.eat_keyword("update");
    string table_name = this->lex.eat_identifier();
    this->lex.eat_keyword("set");

    vector<string> fields; 
    vector<constant> values;
    while (!this->lex.match_keyword("where")) {
        fields.push_back(this->lex.eat_identifier()); 
        this->lex.eat_delimiter('=');
        values.push_back(create_constant()); 
        if (this->lex.match_delimiter(',')) {
            this->lex.eat_delimiter(',');
        }
    }

    this->lex.eat_keyword("where");
    predicate pred = create_predicate(); 

    return update_data(table_name, fields, values, pred);
}

// delete from table_name where
delete_data parser::delete_records() {
    this->lex.eat_keyword("delete");
    this->lex.eat_keyword("from");
    string table_name = this->lex.eat_identifier();
    this->lex.eat_keyword("where");
    predicate pred = predicate("123"); 

    return delete_data(table_name, pred);
}

// select col1, ... from tab1 join tab2 on tab1.key = tab2.key 
select_data parser::select() {
    this->lex.eat_keyword("select");
    vector<string> fields = list(); 
    this->lex.eat_keyword("from"); 
    vector<string> tables = list(); 
    if (this->lex.match_keyword("where")) {
        this->lex.eat_keyword("where"); 
    }
    predicate pred = predicate("123"); 
    return select_data(fields, tables, pred);
}

vector<string> parser::list() {
    vector<string> results;
    results.push_back(this->lex.eat_identifier());
    while (this->lex.match_delimiter(',')) {
        this->lex.eat_delimiter(',');
        results.push_back(this->lex.eat_identifier());
    }
    return results; 
}


