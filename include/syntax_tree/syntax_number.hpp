#ifndef SYNTAX_NUMBER_H_
#define SYNTAX_NUMBER_H_

#include <string>

#include "abstract_syntax_tree.hpp"
#include "barvaz_object.hpp"

using namespace std;
using namespace barvazobject;

namespace barvazsyntaxtree
{
    class SyntaxNumber : public AST
    {
        public:
        virtual BarvazObject evaluate(void);
        virtual void print(void);

        SyntaxNumber(string value);

        private:
        string value;
    };
}

#endif  // SYNTAX_NUMBER_H_