#ifndef PARSER_ERROR_H_
#define PARSER_ERROR_H_

#include <iostream>

using namespace std;

namespace barvazparser
{
    class BarvazParserError : public exception
    {
        public:
        BarvazParserError(const char * msg);

        // Getter to error message
        const char * getMessage();

        private:
        const char * m_msg;
    };
}

#endif  // PARSER_ERROR_H_