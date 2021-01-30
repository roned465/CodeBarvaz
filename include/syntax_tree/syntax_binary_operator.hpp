#ifndef SYNTAX_BINARY_OPERATOR_H_
#define SYNTAX_BINARY_OPERATOR_H_

#include "abstract_syntax_tree.hpp"
#include "barvaz_object.hpp"
#include "object_methods.hpp"

using namespace barvazobject;

namespace barvazsyntaxtree
{
    class SyntaxBinaryOperator : public AST
    {
        public:
        virtual BarvazObject evaluate(void);
        virtual void print(void);

        SyntaxBinaryOperator(AST * leftOperand, AST * rightOperand, ObjectMethod operation);

        private:
        AST * m_leftOperand;
        AST * m_rightOperand;
        ObjectMethod m_operator;
    };
}

#endif  // SYNTAX_BINARY_OPERATOR_H_