#ifndef SYNTAX_IDENTIFIER_H_
#define SYNTAX_IDENTIFIER_H_

#include <string>

#include "abstract_syntax_tree.hpp"

using namespace std;

namespace barvazsyntaxtree
{
    class SyntaxIdentifier : public AST
    {
        public:
        SyntaxIdentifier(string name);

        virtual ~SyntaxIdentifier();

        virtual void print(void) const;

        private:
        string m_name;
    };
}

#endif  // SYNTAX_IDENTIFIER_H_