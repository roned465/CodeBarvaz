#include <iostream>

#include "parser_error.hpp"
#include "tokenizer.hpp"
#include "token.hpp"

using namespace std;
using namespace barvazparser;

int main()
{
    BarvazTokenizer tokenizer(cin);
    Token token;
    
    do
    {
        try
        {
            token = tokenizer.getNextToken();
            cout << token << endl;
        }

        catch (BarvazParserError& e)
        {
            cout << e.what() << endl;
        }
    } while (ENDOFFILE != token.type);
}