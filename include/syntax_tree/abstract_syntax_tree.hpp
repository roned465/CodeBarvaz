#ifndef ABSTRACT_SYNTAX_TREE_H_
#define ABSTRACT_SYNTAX_TREE_H_

#include <iostream>

using namespace std;

namespace barvazsyntaxtree
{
    class AST
    {
        public:
        virtual ~AST();

        virtual void print(void) const = 0;

        friend ostream& operator<<(ostream& os, const AST& ast);
    };
}

#endif  // ABSTRACT_SYNTAX_TREE_H_