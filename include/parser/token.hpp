#ifndef TOKEN_H_
#define TOKEN_H_

#include <string>
using namespace std;

#define MAX_OPERATOR_LENGTH (3)

namespace barvaztokenizer 
{
    /**
     * All possible token types in the barvaz language.
     * For each token type, an example is shown.
     */ 
    typedef enum 
    {
        //////////////////////////
        //////// Literals ////////
        //////////////////////////

        INTEGER,            // 123
        FLOAT,              // 0.5
        TRUE,               // true
        FALSE,              // false
        STRING,             // "hello"

        ////////////////////////////
        //////// Identifier ////////
        ////////////////////////////

        IDENTIFIER,         // num = 3 (num is an identifier)
        
        //////////////////////////
        //////// Keywords ////////
        //////////////////////////

        // Statements
        IF,                 // if
        ELSE,               // else
        WHILE,              // while
        REPEAT,             // repeat
        
        // Data types
        INT_DATATYPE,       // int
        FLOAT_DATATYPE,     // float
        BOOL_DATATYPE,      // bool
        STRING_DATATYPE,    // string

        // Operator keywords
        AND,                // and
        OR,                 // or
        NOT,                // not

        ///////////////////////////
        //////// Operators ////////
        ///////////////////////////

        LPAR,               // (
        RPAR,               // )
        PLUS,               // +
        MINUS,              // -
        STAR,               // *
        SLASH,              // /
        PERCENT,            // %
        EQUAL,              // =
        EQUAL_EQUAL,        // ==
        SMALLER,            // <
        GREATER,            // >
        SMALLER_EQUAL,      // <=
        GREATER_EQUAL,      // >=
        NO_OPERATOR,        // invalid operator characters

        ////////////////////////
        //////// Others ////////
        ////////////////////////

        NEWLINE_SPACE,      // space on start of line before code (for indentation)
        ENDOFFILE,          // end of file

        INVALID_TOKEN_TYPE, // invalid
        
    } TokenType;

    class Token
    {
        public:
        TokenType type;
        string valueString;
        uint32_t valueInt;

        friend ostream& operator<<(ostream& os, const Token& token);
    };

    //////// Functions to get the operators and keywords token types ////////

    /**
     * @brief Given an operator character, returns the corresponding token type.
     *      e.g. for the character '+' the function would return the TokenType PLUS.
     * @param operatorChar The operator character.
     * @return The token type for the given character, 
     *      or NO_OPERATOR if the operator is invalid.
     */
    TokenType getOneCharOperatorToken(char operatorChar);

    /**
     * @brief Given two operator characters, returns the corresponding token type.
     *      e.g. for the characters '<=' the function would return the TokenType SMALLER_EQUAL.
     * @param operatorCharFirst The first operator character.
     * @param operatorCharSecond The second operator character.
     * @return The token type for the given characters,
     *      or NO_OPERATOR if the operator is invalid.
     */
    TokenType getTwoCharsOperatorToken(char operatorCharFirst, char operatorCharSecond);

    /**
     * @brief Given three operator characters, returns the corresponding token type.
     *      Currently no operators have three characters, for future use.
     * @param operatorCharFirst The first operator character.
     * @param operatorCharSecond The second operator character.
     * @param operatorCharThird The third operator character.
     * @return The token type for the given characters,
     *      or NO_OPERATOR if the operator is invalid.
     */
    TokenType getThreeCharsOperatorToken(char operatorCharFirst, char operatorCharSecond, char operatorCharThird);

    /**
     * @brief Given a string representing a word in the code, checks whether it is an
     *      identifier of a keyword in the language and returns the token type.
     *      e.g. for the word "while" the token type WHILE will be returned,
     *           for the word "number" the token type IDENTIFIER will be returned.
     * @param word The word in the code, either an identifier or a keyword.
     * @return The token type of the given word.
     */
    TokenType getIdentifierOrKeywordTokenType(const string& word);
}

#endif  // TOKEN_H_