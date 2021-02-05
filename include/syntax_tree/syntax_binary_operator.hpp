#ifndef SYNTAX_BINARY_OPERATOR_H_
#define SYNTAX_BINARY_OPERATOR_H_

#include "abstract_syntax_tree.hpp"
#include "type.hpp"

using namespace barvazobject;

namespace barvazsyntaxtree
{
    class SyntaxBinaryOperator : public AST
    {
        public:
        SyntaxBinaryOperator(AST * leftOperand, AST * rightOperand, BarvazType::TypeMethod operation);

        virtual ~SyntaxBinaryOperator();

        virtual void print(void) const;

        private:
        AST * m_leftOperand;
        AST * m_rightOperand;
        BarvazType::TypeMethod m_operator;
    };
}

#endif  // SYNTAX_BINARY_OPERATOR_H_