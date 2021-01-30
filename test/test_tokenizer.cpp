#include <iostream>

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

        catch (BarvazTokenizerError& e)
        {
            cout << e.getMessage();
        }
    } while (ENDOFFILE != token.type);
}