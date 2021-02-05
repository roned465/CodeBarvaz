#include <string>
#include <iostream>

#include "abstract_syntax_tree.hpp"
#include "syntax_number.hpp"

using namespace std;

namespace barvazsyntaxtree
{
    SyntaxNumber::SyntaxNumber(string value)
    {
        m_value = value;
    }

    SyntaxNumber::~SyntaxNumber() { }

    void SyntaxNumber::print(void) const
    {
        cout << m_value;
    }
}