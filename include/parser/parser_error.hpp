#ifndef PARSER_ERROR_H_
#define PARSER_ERROR_H_

#include <iostream>

using namespace std;

namespace barvazparser
{
    /**
     * @brief An exception thrown by the Barvaz parser, representing a syntax error.
     */
    class BarvazParserError : public exception
    {
        public:
        BarvazParserError(const char * msg);

        /**
         * @brief Getter to the error message.
         */
        virtual const char * what();

        private:
        const char * m_msg;  // The error message.
    };
}

#endif  // PARSER_ERROR_H_