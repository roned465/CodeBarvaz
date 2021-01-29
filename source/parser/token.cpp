#include <string>
#include <iostream>
#include <map>
using namespace std;

#include "token.hpp"

namespace barvaztokenizer
{
    ostream& operator<<(ostream& os, const Token& token)
    {
        os << "<Type: " << token.type << "\tInt value: " << token.valueInt << "\tString value: " << token.valueString << ">";
        return os;
    }

    TokenType getOneCharOperatorToken(char operatorChar)
    {
        switch (operatorChar)
        {
        case '(':
            return LPAR;
        case ')':
            return RPAR;
        case '+':
            return PLUS;
        case '-':
            return MINUS;
        case '*':
            return STAR;
        case '/':
            return SLASH;
        case '%':
            return PERCENT;
        case '=':
            return EQUAL;
        case '<':
            return SMALLER;
        case '>':
            return GREATER;
        default:
            return NO_OPERATOR;
        }
    }

    TokenType getTwoCharsOperatorToken(char operatorCharFirst, char operatorCharSecond)
    {
        switch (operatorCharFirst)
        {
        case '=':
            switch (operatorCharSecond)
            {
            case '=':
                return EQUAL_EQUAL;
            default:
                return NO_OPERATOR;
            }
        case '<':
            switch (operatorCharSecond)
            {
            case '=':
                return SMALLER_EQUAL;
            default:
                return NO_OPERATOR;
            }
        case '>':
            switch (operatorCharSecond)
            {
            case '=':
                return GREATER_EQUAL;
            default:
                return NO_OPERATOR;
            }
        default:
            return NO_OPERATOR;
        }
    }

    TokenType getThreeCharsOperatorToken(char operatorCharFirst, char operatorCharSecond, char operatorCharThird)
    {
        switch (operatorCharFirst)
        {
        default:
            return NO_OPERATOR;
        }
    }

    static map<string, TokenType> keywordMapper = {
        { "if"      ,   IF              },
        { "else"    ,   ELSE            },
        { "while"   ,   WHILE           },
        { "repeat"  ,   REPEAT          },
        
        { "int"     ,   INT_DATATYPE    },
        { "float"   ,   FLOAT_DATATYPE  },
        { "bool"    ,   BOOL_DATATYPE   },
        { "string"  ,   BOOL_DATATYPE   },

        { "and"     ,   AND             },
        { "or"      ,   OR              },
        { "not"     ,   NOT             },

        { "true"    ,   TRUE            },
        { "false"   ,   FALSE           },
    };

    TokenType getIdentifierOrKeywordTokenType(const string& word)
    {
        map<string, TokenType>::iterator keywordIter = keywordMapper.find(word);
        
        if (keywordIter == keywordMapper.end())
        {
            return IDENTIFIER;
        }

        else
        {
            return keywordIter->second;
        }
        
    }
}