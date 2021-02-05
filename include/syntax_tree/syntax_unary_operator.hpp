#ifndef SYNTAX_UNARY_OPERATOR_H_
#define SYNTAX_UNARY_OPERATOR_H_

#include "abstract_syntax_tree.hpp"
#include "type.hpp"

using namespace barvazobject;

namespace barvazsyntaxtree
{
    class SyntaxUnaryOperator : public AST
    {
        public:
        SyntaxUnaryOperator(AST * operand, BarvazType::TypeMethod operation);

        virtual ~SyntaxUnaryOperator();

        virtual void print(void) const;

        private:
        AST * m_operand;
        BarvazType::TypeMethod m_operator;
    };
}

#endif  // SYNTAX_UNARY_OPERATOR_H_