#include <iostream>

#include "abstract_syntax_tree.hpp"

using namespace std;

namespace barvazsyntaxtree
{
    AST::~AST() { }

    ostream& operator<<(ostream& os, const AST& ast)
    {
        ast.print();
        return os;
    }
}