#include <iostream>

#include "parser_error.hpp"
#include "tokenizer.hpp"
#include "token.hpp"

using namespace std;

#define SIZE_OF_TAB (4)

#define IS_ALPHABETICAL(c) (((c) >= 'A' && (c) <= 'Z') || ((c) >= 'a' && (c) <= 'z'))
#define IS_DECIMAL_DIGIT(c) ((c) >= '0' && (c) <= '9')
#define IS_BINARY_DIGIT(c) ((c) == '0' || (c) == '1')
#define IS_OCTAL_DIGIT(c) ((c) >= '0' && (c) <= '7')
#define IS_HEXADECIMAL_DIGIT(c) (((c) >= '0' && (c) <= '9') || ((c) >= 'A' && (c) <= 'F') || ((c) >= 'a' && (c) <= 'f'))
#define IS_WHITESPACE(c) (' ' == (c) || '\t' == (c) || '\r' == (c))

#define IS_START_OF_IDENTIFIER(c) ('_' == (c) || IS_ALPHABETICAL(c))
#define IS_CONTINUATION_OF_IDENTIFIER(c) ('_' == (c) || IS_ALPHABETICAL(c) || IS_DECIMAL_DIGIT(c))

static inline bool is_operator(char c)
{
    switch (c)
        {
        case '(':
        case ')':
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '=':
        case '<':
        case '>':
            return true;
        default:
            return false;
        }
}
#define IS_OPERATOR(c) is_operator(c)

namespace barvazparser
{
    BarvazTokenizer::BarvazTokenizer(istream& codeStream) : m_codeStream(codeStream)
    {
        m_currentState = STATE_READING_NEWLINE_SPACING;  // Initial state of the tokenizer.
        m_currentLineSpacingFromStart = 0;
        m_currentReadString = "";
        m_currentReadOperators = "";
        m_nextParsedTokenType = PARSED_TOKEN_TYPE_NO_TOKEN_PARSED;
        m_nextToken.type = INVALID_TOKEN_TYPE;
    }

    TokenType BarvazTokenizer::getNextOperatorType()
    {
        TokenType operatorType = NO_OPERATOR;

        // Switch on the read operators length, if a given length
        // doesn't yield a valid operator type, go to next length.
        // If extracted a valid operator in length n, erase n first
        // characters of the operator string.
        switch (m_currentReadOperators.length())
        {
        case 3:
            operatorType = getThreeCharsOperatorToken(m_currentReadOperators[0], m_currentReadOperators[1], m_currentReadOperators[2]);
            if (NO_OPERATOR != operatorType)
            {
                m_currentReadOperators.erase(0, 3);
                break;
            }

        case 2:
            operatorType = getTwoCharsOperatorToken(m_currentReadOperators[0], m_currentReadOperators[1]);
            if (NO_OPERATOR != operatorType)
            {
                m_currentReadOperators.erase(0, 2);
                break;
            }
        
        case 1:
            operatorType = getOneCharOperatorToken(m_currentReadOperators[0]);
            if (NO_OPERATOR != operatorType)
            {
                m_currentReadOperators.erase(0, 1);
                break;
            }
        
        default:
            break;
        }

        return operatorType;
    }

    void BarvazTokenizer::receiveCharacterOnState_ReadingNewLineSpacing(char nextCharacter)
    {
        if (IS_START_OF_IDENTIFIER(nextCharacter))
        {
            m_currentReadString += nextCharacter;

            m_nextParsedTokenType = PARSED_TOKEN_TYPE_NEWLINE_SPACE;

            m_currentState = STATE_READING_IDENTIFIER_OR_KEYWORD;
        }

        else if (IS_DECIMAL_DIGIT(nextCharacter))
        {
            m_currentReadString += nextCharacter;

            m_nextParsedTokenType = PARSED_TOKEN_TYPE_NEWLINE_SPACE;

            m_currentState = STATE_READING_NUMBER_DECIMAL;
        }

        else if (IS_OPERATOR(nextCharacter))
        {
            m_currentReadOperators += nextCharacter;

            m_nextParsedTokenType = PARSED_TOKEN_TYPE_NEWLINE_SPACE;

            m_currentState = STATE_READING_OPERATOR_CHARACTERS;
        }

        else if ('"' == nextCharacter)
        {
            m_nextParsedTokenType = PARSED_TOKEN_TYPE_NEWLINE_SPACE;

            m_currentState = STATE_READING_STRING;
        }

        else if (IS_WHITESPACE(nextCharacter))
        {
            if (' ' == nextCharacter)
            {
                m_currentLineSpacingFromStart ++;
            }
            else if ('\t' == nextCharacter)
            {
                m_currentLineSpacingFromStart += SIZE_OF_TAB;
            }
        }

        else if ('\n' == nextCharacter)
        {
            m_currentLineSpacingFromStart = 0;
        }

        else
        {
            throw BarvazParserError("Invalid character");
        }
    }

    void BarvazTokenizer::receiveCharacterOnState_ReadingIdentifierOrKeyword(char nextCharacter)
    {
        if (IS_CONTINUATION_OF_IDENTIFIER(nextCharacter))
        {
            m_currentReadString += nextCharacter;
        }

        else if (IS_OPERATOR(nextCharacter))
        {
            m_currentReadOperators += nextCharacter;

            m_nextParsedTokenType = PARSED_TOKEN_TYPE_IDENTIFIER;

            m_currentState = STATE_READING_OPERATOR_CHARACTERS;
        }

        else if ('"' == nextCharacter)
        {
            throw BarvazParserError("Invalid syntax");
        }

        else if (IS_WHITESPACE(nextCharacter))
        {
            m_nextParsedTokenType = PARSED_TOKEN_TYPE_IDENTIFIER;

            m_currentState = STATE_READING_SPACING;
        }

        else if ('\n' == nextCharacter)
        {
            m_nextParsedTokenType = PARSED_TOKEN_TYPE_IDENTIFIER;
            
            m_currentState = STATE_READING_NEWLINE_SPACING;
        }

        else
        {
            throw BarvazParserError("Invalid character");
        }
    }
    
    void BarvazTokenizer::receiveCharacterOnState_ReadingOperatorCharacters(char nextCharacter)
    {
        if (IS_START_OF_IDENTIFIER(nextCharacter))
        {
            m_currentReadString += nextCharacter;

            m_nextParsedTokenType = PARSED_TOKEN_TYPE_OPERATOR;

            m_currentState = STATE_READING_IDENTIFIER_OR_KEYWORD;
        }

        else if (IS_DECIMAL_DIGIT(nextCharacter))
        {
            m_currentReadString += nextCharacter;
            
            m_nextParsedTokenType = PARSED_TOKEN_TYPE_OPERATOR;
            
            m_currentState = STATE_READING_NUMBER_DECIMAL;
        }

        else if (IS_OPERATOR(nextCharacter))
        {
            m_currentReadOperators += nextCharacter;
        }

        else if ('"' == nextCharacter)
        {
            m_nextParsedTokenType = PARSED_TOKEN_TYPE_OPERATOR;

            m_currentState = STATE_READING_STRING;
        }

        else if (IS_WHITESPACE(nextCharacter))
        {
            m_nextParsedTokenType = PARSED_TOKEN_TYPE_OPERATOR;

            m_currentState = STATE_READING_SPACING;
        }

        else if ('\n' == nextCharacter)
        {
            m_nextParsedTokenType = PARSED_TOKEN_TYPE_OPERATOR;

            m_currentState = STATE_READING_NEWLINE_SPACING;
        }

        else
        {
            throw BarvazParserError("Invalid character");
        }
    }

    void BarvazTokenizer::receiveCharacterOnState_ReadingNumberDecimal(char nextCharacter)
    {
        if (IS_DECIMAL_DIGIT(nextCharacter))
        {
            m_currentReadString += nextCharacter;
        }

        else if (IS_CONTINUATION_OF_IDENTIFIER(nextCharacter))
        {
            throw BarvazParserError("Invalid syntax");
        }

        else if (IS_OPERATOR(nextCharacter))
        {
            m_currentReadOperators += nextCharacter;

            m_nextParsedTokenType = PARSED_TOKEN_TYPE_NUMBER;

            m_currentState = STATE_READING_OPERATOR_CHARACTERS;
        }

        else if ('"' == nextCharacter)
        {
            throw BarvazParserError("Invalid syntax");
        }

        else if (IS_WHITESPACE(nextCharacter))
        {
            m_nextParsedTokenType = PARSED_TOKEN_TYPE_NUMBER;

            m_currentState = STATE_READING_SPACING;
        }

        else if ('\n' == nextCharacter)
        {
            m_nextParsedTokenType = PARSED_TOKEN_TYPE_NUMBER;

            m_currentState = STATE_READING_NEWLINE_SPACING;
        }

        else
        {
            throw BarvazParserError("Invalid character");
        }
    }

    void BarvazTokenizer::receiveCharacterOnState_ReadingString(char nextCharacter)
    {
        if ('"' == nextCharacter)
        {
            m_nextParsedTokenType = PARSED_TOKEN_TYPE_STRING;

            m_currentState = STATE_FINISHED_READING_STRING;
        }

        else
        {
            m_currentReadString += nextCharacter;
        }
    }

    void BarvazTokenizer::receiveCharacterOnState_FinishedReadingString(char nextCharacter)
    {
        if (IS_CONTINUATION_OF_IDENTIFIER(nextCharacter))
        {
            throw BarvazParserError("Invalid syntax");
        }

        else if (IS_OPERATOR(nextCharacter))
        {
            m_currentReadOperators += nextCharacter;

            m_currentState = STATE_READING_OPERATOR_CHARACTERS;
        }

        else if ('"' == nextCharacter)
        {
            throw BarvazParserError("Invalid syntax");
        }

        else if (IS_WHITESPACE(nextCharacter))
        {
            m_currentState = STATE_READING_SPACING;
        }

        else if ('\n' == nextCharacter)
        {
            m_currentState = STATE_READING_NEWLINE_SPACING;
        }

        else
        {
            throw BarvazParserError("Invalid character");
        }
    }

    void BarvazTokenizer::receiveCharacterOnState_ReadingSpacing(char nextCharacter)
    {
        if (IS_START_OF_IDENTIFIER(nextCharacter))
        {
            m_currentReadString += nextCharacter;

            m_currentState = STATE_READING_IDENTIFIER_OR_KEYWORD;
        }

        else if (IS_DECIMAL_DIGIT(nextCharacter))
        {
            m_currentReadString += nextCharacter;

            m_currentState = STATE_READING_NUMBER_DECIMAL;
        }

        else if (IS_OPERATOR(nextCharacter))
        {
            m_currentReadOperators += nextCharacter;

            m_currentState = STATE_READING_OPERATOR_CHARACTERS;
        }

        else if ('"' == nextCharacter)
        {
            m_currentState = STATE_READING_STRING;
        }

        else if (IS_WHITESPACE(nextCharacter))
        {
            // Nothing
        }

        else if ('\n' == nextCharacter)
        {
            m_currentState = STATE_READING_NEWLINE_SPACING;
        }

        else
        {
            throw BarvazParserError("Invalid character");
        }
    }

    void BarvazTokenizer::receiveNextCharacterInput(char nextCharacter)
    {
        switch (m_currentState)
        {
        case STATE_READING_NEWLINE_SPACING:
            receiveCharacterOnState_ReadingNewLineSpacing(nextCharacter);
            break;

        case STATE_READING_IDENTIFIER_OR_KEYWORD:
            receiveCharacterOnState_ReadingIdentifierOrKeyword(nextCharacter);
            break;

        case STATE_READING_OPERATOR_CHARACTERS:
            receiveCharacterOnState_ReadingOperatorCharacters(nextCharacter);
            break;

        case STATE_READING_NUMBER_DECIMAL:
            receiveCharacterOnState_ReadingNumberDecimal(nextCharacter);
            break;
        
        case STATE_READING_STRING:
            receiveCharacterOnState_ReadingString(nextCharacter);
            break;

        case STATE_FINISHED_READING_STRING:
            receiveCharacterOnState_FinishedReadingString(nextCharacter);
            break;
        
        case STATE_READING_SPACING:
            receiveCharacterOnState_ReadingSpacing(nextCharacter);
            break;

        default:
            break;
        }
    }

    Token& BarvazTokenizer::getNextToken()
    {
        char nextCharacter = 0;

        while (PARSED_TOKEN_TYPE_NO_TOKEN_PARSED == m_nextParsedTokenType)
        {
            nextCharacter = m_codeStream.get();

            if (m_codeStream.eof())
            {
                m_nextParsedTokenType = PARSED_TOKEN_TYPE_EOF;
            }

            else
            {
                receiveNextCharacterInput(nextCharacter);
            }
        }

        switch (m_nextParsedTokenType)
        {
        case PARSED_TOKEN_TYPE_OPERATOR:
            m_nextToken.type = getNextOperatorType();
            m_nextToken.valueString = "";
            m_nextToken.valueInt = 0;

            if (NO_OPERATOR == m_nextToken.type)
            {
                throw BarvazParserError("Invalid Operator Parsed");
            }
            
            if (m_currentReadOperators.empty())
            {
                m_nextParsedTokenType = PARSED_TOKEN_TYPE_NO_TOKEN_PARSED;
            }

            break;
        
        case PARSED_TOKEN_TYPE_NEWLINE_SPACE:
            m_nextToken.type = NEWLINE_SPACE;
            m_nextToken.valueString = "";
            m_nextToken.valueInt = m_currentLineSpacingFromStart;

            m_currentLineSpacingFromStart = 0;
            m_nextParsedTokenType = PARSED_TOKEN_TYPE_NO_TOKEN_PARSED;
            break;

        case PARSED_TOKEN_TYPE_IDENTIFIER:
            m_nextToken.type = getIdentifierOrKeywordTokenType(m_currentReadString);
            m_nextToken.valueInt = 0;

            if (IDENTIFIER == m_nextToken.type)
            {
                m_nextToken.valueString = m_currentReadString;
            }

            else
            {
                m_nextToken.valueString = "";
            }
            
            m_currentReadString.clear();
            m_nextParsedTokenType = PARSED_TOKEN_TYPE_NO_TOKEN_PARSED;
            break;

        case PARSED_TOKEN_TYPE_STRING:
            m_nextToken.type = STRING;
            m_nextToken.valueString = m_currentReadString;
            m_nextToken.valueInt = 0;

            m_currentReadString.clear();
            m_nextParsedTokenType = PARSED_TOKEN_TYPE_NO_TOKEN_PARSED;
            break;

        case PARSED_TOKEN_TYPE_NUMBER:
            m_nextToken.type = INTEGER;
            m_nextToken.valueString = m_currentReadString;
            m_nextToken.valueInt = 0;

            m_currentReadString.clear();
            m_nextParsedTokenType = PARSED_TOKEN_TYPE_NO_TOKEN_PARSED;
            break;
        
        case PARSED_TOKEN_TYPE_EOF:
            m_nextToken.type = ENDOFFILE;
            m_nextToken.valueString = "";
            m_nextToken.valueInt = 0;

            // When reaching EOF the parsed token type should keep being PARSED_TOKEN_TYPE_EOF.
            break;

        default:
            throw BarvazParserError("Invalid Token Parsed");
        }

        return m_nextToken;
    }
}
