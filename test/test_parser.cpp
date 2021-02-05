#include <iostream>

#include "parser.hpp"
#include "parser_error.hpp"
#include "tokenizer.hpp"

using namespace std;
using namespace barvazparser;

int main()
{
    AST * ast = NULL;
    BarvazTokenizer tokenizer(cin);
    tokenizer.getNextToken();
    BarvazParser parser(tokenizer);

    try
    {
        ast = parser.expr();
        cout << *ast << endl;
    }

    catch (BarvazParserError &e)
    {
        cout << e.getMessage() << endl;
    }

    if (NULL != ast)
    {
        delete ast;
    }
}