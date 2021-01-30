#ifndef SYNTAX_IDENTIFIER_H_
#define SYNTAX_IDENTIFIER_H_

#include <string>

#include "abstract_syntax_tree.hpp"
#include "barvaz_object.hpp"

using namespace std;
using namespace barvazobject;

namespace barvazsyntaxtree
{
    class SyntaxIdentifier : public AST
    {
        public:
        virtual BarvazObject evaluate(void);
        virtual void print(void);

        SyntaxIdentifier(string name);

        private:
        string name;
    };
}

#endif  // SYNTAX_IDENTIFIER_H_