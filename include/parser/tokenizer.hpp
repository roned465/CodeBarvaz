#ifndef TOKENIZER_H_
#define TOKENIZER_H_

#include <iostream>
using namespace std;

#include "token.hpp"

namespace barvazparser
{
    typedef enum 
    {
        PARSED_TOKEN_TYPE_NO_TOKEN_PARSED,
        PARSED_TOKEN_TYPE_OPERATOR,
        PARSED_TOKEN_TYPE_NEWLINE_SPACE,
        PARSED_TOKEN_TYPE_IDENTIFIER,
        PARSED_TOKEN_TYPE_STRING,
        PARSED_TOKEN_TYPE_NUMBER,
        PARSED_TOKEN_TYPE_EOF
    } ParsedTokenType;

    typedef enum
    {
        STATE_READING_NEWLINE_SPACING,
        STATE_READING_IDENTIFIER_OR_KEYWORD,
        STATE_READING_OPERATOR_CHARACTERS,
        STATE_READING_NUMBER_DECIMAL,
        // TODO add binary, octal and hexadecimal number formats
        // TODO add support in comments
        STATE_READING_STRING,
        STATE_FINISHED_READING_STRING,
        STATE_READING_SPACING,
    } TokenizerState;

    /**
     * @brief A tokenizer class for the language that parses tokens from a stream of code
     * and is implemented as a state machine that receives characters as input.
     */
    class BarvazTokenizer 
    {
        public:
        
        /**
         * @brief A constructor to the BarvazTokenizer class.
         * @param codeStream The input stream of the code.
         */
        BarvazTokenizer(istream& codeStream);

        /**
         * @brief Parses the code and gets the next token on the code.
         * @return The next parsed token.
         */
        Token& getNextToken();



        private:
        
        /**
         * @brief Extracts the next operator type from the current operators characters.
         *      e.g if the current operators string is ==(, then the function would return
         *      the operator ==, which is EQUAL_EQUAL.
         * @return The type of the next operator in the current operators string.
         * @details The function also erases the extracted operator characters prefix from the
         *      operators string.
         *      Works according to the maximal munch principal.
         */
        TokenType getNextOperatorType();



        // Handlers for all possible states of the tokenizer on reading a character.
        
        /**
         * @brief Handles a received character while on ReadingNewLineSpacing state.
         * @param nextCharacter The received character read by the code stream.
         * @details Read documentation on receiveNextCharacterInput function.
         */
        void receiveCharacterOnState_ReadingNewLineSpacing(char nextCharacter);

        /**
         * @brief Handles a received character while on ReadingIdentifierOrKeyword state.
         * @param nextCharacter The received character read by the code stream.
         * @details Read documentation on receiveNextCharacterInput function.
         */
        void receiveCharacterOnState_ReadingIdentifierOrKeyword(char nextCharacter);

        /**
         * @brief Handles a received character while on ReadingOperatorCharacters state.
         * @param nextCharacter The received character read by the code stream.
         * @details Read documentation on receiveNextCharacterInput function.
         */
        void receiveCharacterOnState_ReadingOperatorCharacters(char nextCharacter);

        /**
         * @brief Handles a received character while on ReadingNumberDecimal state.
         * @param nextCharacter The received character read by the code stream.
         * @details Read documentation on receiveNextCharacterInput function.
         */
        void receiveCharacterOnState_ReadingNumberDecimal(char nextCharacter);

        /**
         * @brief Handles a received character while on ReadingString state.
         * @param nextCharacter The received character read by the code stream.
         * @details Read documentation on receiveNextCharacterInput function.
         */
        void receiveCharacterOnState_ReadingString(char nextCharacter);

        /**
         * @brief Handles a received character while on FinishedReadingString state.
         * @param nextCharacter The received character read by the code stream.
         * @details Read documentation on receiveNextCharacterInput function.
         */
        void receiveCharacterOnState_FinishedReadingString(char nextCharacter);

        /**
         * @brief Handles a received character while on ReadingSpacing state.
         * @param nextCharacter The received character read by the code stream.
         * @details Read documentation on receiveNextCharacterInput function.
         */
        void receiveCharacterOnState_ReadingSpacing(char nextCharacter);

        /**
         * @brief Receives the next input from the code stream and feeds it to the 
         *      tokenizer state machine according to the current state.
         *      Switches on the current state and forwards the character to the relevant
         *      state handler declared above.
         * @param nextCharacter The received character read by the code stream.
         * @details According to the current state and the received character, the function
         *      changes the state of the tokenizer and the relevant parameters, and changes
         *      the m_nextParsedTokenType if a new token is parsed.
         */
        void receiveNextCharacterInput(char nextCharacter);



        istream& m_codeStream;  // The code stream.
        Token m_nextToken;  // The next parsed token.

        // Data about current tokenizer state
        ParsedTokenType m_nextParsedTokenType;  // The type of the last token parsed.
        TokenizerState m_currentState;  // The current state of the tokenizer state machine.
        uint32_t m_currentLineSpacingFromStart;  // The number of spaces from the start of the current line.
        string m_currentReadString;  // The current string read by the parser (including identifiers, numbers, strings and keywords).
        string m_currentReadOperators;  // The current sequence of operator characters read by the parser.
    };
}

#endif  // TOKENIZER_H_