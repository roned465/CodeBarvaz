#include <string>
#include <iostream>

#include "abstract_syntax_tree.hpp"
#include "type.hpp"
#include "syntax_unary_operator.hpp"

using namespace std;
using namespace barvazobject;

namespace barvazsyntaxtree
{
    SyntaxUnaryOperator::SyntaxUnaryOperator(AST * operand, BarvazType::TypeMethod operation)
    {
        m_operand = operand;
        m_operator = operation;
    }

    SyntaxUnaryOperator::~SyntaxUnaryOperator()
    {
        if (NULL != m_operand)
        {
            delete m_operand;
        }
    }

    void SyntaxUnaryOperator::print(void) const
    {
        if (NULL == m_operand)
        {
            return;
        }

        cout << "(";
        switch (m_operator)
        {
        case BarvazType::POS:
            cout << "+";
            break;
        case BarvazType::NEG:
            cout << "-";
            break;
        default:
            cout << " invalid unary operator ";
            break;
        }
        m_operand->print();
        cout << ")";
    }
}