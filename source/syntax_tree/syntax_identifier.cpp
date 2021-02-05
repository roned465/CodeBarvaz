#include <string>
#include <iostream>

#include "abstract_syntax_tree.hpp"
#include "syntax_identifier.hpp"

using namespace std;

namespace barvazsyntaxtree
{
    SyntaxIdentifier::SyntaxIdentifier(string name)
    {
        m_name = name;
    }

    SyntaxIdentifier::~SyntaxIdentifier() { }

    void SyntaxIdentifier::print(void) const
    {
        cout << m_name;
    }
}