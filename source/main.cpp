#include <iostream>

#include "tokenizer.hpp"
#include "token.hpp"

using namespace std;

int main()
{
    barvaztokenizer::BarvazTokenizer lexer(cin);
    barvaztokenizer::Token token;
    
    do
    {
        try
        {
            token = lexer.getNextToken();
            cout << token << endl;
        }

        catch (barvaztokenizer::BarvazTokenizerError& e)
        {
            cout << e.getMessage();
        }
    } while (barvaztokenizer::ENDOFFILE != token.type);
}