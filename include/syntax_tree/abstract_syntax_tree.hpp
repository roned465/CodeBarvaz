#ifndef ABSTRACT_SYNTAX_TREE_H_
#define ABSTRACT_SYNTAX_TREE_H_

#include "barvaz_object.hpp"

using namespace barvazobject;

namespace barvazsyntaxtree
{
    class AST
    {
        public:
        virtual BarvazObject evaluate(void) = 0;
        virtual void print(void) = 0;
    };
}

#endif  // ABSTRACT_SYNTAX_TREE_H_