#ifndef SYNTAX_NUMBER_H_
#define SYNTAX_NUMBER_H_

#include <string>

#include "abstract_syntax_tree.hpp"

using namespace std;

namespace barvazsyntaxtree
{
    class SyntaxNumber : public AST
    {
        public:
        SyntaxNumber(string value);

        virtual ~SyntaxNumber();

        virtual void print(void) const;

        private:
        string m_value;
    };
}

#endif  // SYNTAX_NUMBER_H_