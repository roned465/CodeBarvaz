#include <iostream>

#include "parser_error.hpp"

using namespace std;

namespace barvazparser
{
    BarvazParserError::BarvazParserError(const char * msg) : m_msg(msg) { }

    const char * BarvazParserError::what()
    {
        return m_msg;
    }
}