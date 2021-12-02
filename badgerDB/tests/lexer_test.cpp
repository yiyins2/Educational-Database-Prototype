#include <string>
#include <boost/tokenizer.hpp>

#include "lexer.hpp"

using namespace std;

int main() {
    string cmd = "select * from x, y where x.b = 3";
    lexer lex = lexer(cmd);

    lex.eat_keyword("select");
    cout << lex.eat_identifier() << "\n";
    lex.eat_keyword("from");
    cout << lex.eat_identifier() << "\n";
    lex.eat_delimiter(',');
    cout << lex.eat_identifier() << "\n";
    lex.eat_keyword("where");
    cout << lex.eat_identifier() << "\n";
    lex.eat_delimiter('.');
    cout << lex.eat_identifier() << "\n";
    lex.eat_delimiter('=');
    cout << lex.eat_int_constant() << "\n";
}