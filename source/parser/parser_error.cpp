#include <iostream>

#include "parser_error.hpp"

using namespace std;

namespace barvazparser
{
    BarvazParserError::BarvazParserError(const char * msg) : m_msg(msg) { }

    const char * BarvazParserError::getMessage()
    {
        return m_msg;
    }
}