#include <string>
#include <iostream>

#include "abstract_syntax_tree.hpp"
#include "syntax_binary_operator.hpp"
#include "type.hpp"

using namespace std;
using namespace barvazobject;

namespace barvazsyntaxtree
{
    SyntaxBinaryOperator::SyntaxBinaryOperator(AST * leftOperand, AST * rightOperand, BarvazType::TypeMethod operation)
    {
        m_leftOperand = leftOperand;
        m_rightOperand = rightOperand;
        m_operator = operation;
    }

    SyntaxBinaryOperator::~SyntaxBinaryOperator()
    {
        if (NULL != m_leftOperand)
        {
            delete m_leftOperand;
        }

        if (NULL != m_rightOperand)
        {
            delete m_rightOperand;
        }
    }

    void SyntaxBinaryOperator::print(void) const
    {
        if (NULL == m_leftOperand || NULL == m_rightOperand)
        {
            return;
        }

        cout << "(";
        m_leftOperand->print();
        switch (m_operator)
        {
        case BarvazType::ADD:
            cout << " + ";
            break;
        case BarvazType::SUB:
            cout << " - ";
            break;
        case BarvazType::MUL:
            cout << " * ";
            break;
        case BarvazType::DIV:
            cout << " / ";
            break;
        case BarvazType::MOD:
            cout << " % ";
            break;
        default:
            cout << " invalid binary operator ";
            break;
        }
        m_rightOperand->print();
        cout << ")";
    }
}