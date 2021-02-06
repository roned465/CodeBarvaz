#ifndef SYNTAX_BINARY_OPERATOR_H_
#define SYNTAX_BINARY_OPERATOR_H_

#include "abstract_syntax_tree.hpp"
#include "type.hpp"

using namespace barvazobject;

namespace barvazsyntaxtree
{
    /**
     * @brief An AST node representing a binary operator.
     *      Contains a left and right operand and an operator.
     */
    class SyntaxBinaryOperator : public AST
    {
        public:
        SyntaxBinaryOperator(AST * leftOperand, AST * rightOperand, BarvazType::TypeMethod operation);

        virtual ~SyntaxBinaryOperator();

        /**
         * @brief Prints the operands with the operator between them, inside parentheses.
         *      e.g. for the operands 4 and 3 and the operator +, will print (4 + 3).
         */
        virtual void print(void) const;

        private:
        AST * m_leftOperand;
        AST * m_rightOperand;
        BarvazType::TypeMethod m_operator;
    };
}

#endif  // SYNTAX_BINARY_OPERATOR_H_