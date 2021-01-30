#ifndef SYNTAX_UNARY_OPERATOR_H_
#define SYNTAX_UNARY_OPERATOR_H_

#include "object_methods.hpp"
#include "abstract_syntax_tree.hpp"
#include "barvaz_object.hpp"

using namespace barvazobject;

namespace barvazsyntaxtree
{
    class SyntaxUnaryOperator : public AST
    {
        public:
        virtual BarvazObject evaluate(void);
        virtual void print(void);

        SyntaxUnaryOperator(AST * operand, ObjectMethod operation);

        private:
        AST * m_operand;
        ObjectMethod m_operator;
    };
}

#endif  // SYNTAX_UNARY_OPERATOR_H_