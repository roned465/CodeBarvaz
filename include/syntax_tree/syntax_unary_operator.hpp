#ifndef SYNTAX_UNARY_OPERATOR_H_
#define SYNTAX_UNARY_OPERATOR_H_

#include "abstract_syntax_tree.hpp"
#include "type.hpp"

using namespace barvazobject;

namespace barvazsyntaxtree
{
    /**
     * @brief An AST node representing a unary operator.
     *      Contains an operand and an operator.
     */
    class SyntaxUnaryOperator : public AST
    {
        public:
        SyntaxUnaryOperator(AST * operand, BarvazType::TypeMethod operation);

        virtual ~SyntaxUnaryOperator();

        /**
         * @brief Prints the operand with the operator to its left, inside parentheses.
         *      e.g. for the operand 5 and the operator -, will print (-5).
         */
        virtual void print(void) const;

        private:
        AST * m_operand;
        BarvazType::TypeMethod m_operator;
    };
}

#endif  // SYNTAX_UNARY_OPERATOR_H_