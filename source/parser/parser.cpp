#include "parser.hpp"
#include "parser_error.hpp"
#include "abstract_syntax_tree.hpp"
#include "syntax_binary_operator.hpp"
#include "syntax_unary_operator.hpp"
#include "syntax_number.hpp"
#include "syntax_identifier.hpp"
#include "token.hpp"
#include "tokenizer.hpp"

using namespace barvazsyntaxtree;

namespace barvazparser
{
    BarvazParser::BarvazParser(BarvazTokenizer& tokenizer) : m_tokenizer(tokenizer) 
    {
        advance();
    }

    void BarvazParser::advance(void)
    {
        m_currentToken = m_tokenizer.getNextToken();
        cout << m_currentToken << endl;
    }

    AST * BarvazParser::expr()
    {
        return addExpr();
    }

    AST * BarvazParser::addExpr()
    {
        AST * leftOperand = NULL;
        AST * rightOperand = NULL;
        bool isAddExpression = true;
        BarvazType::TypeMethod operation;
        
        leftOperand = mulExpr();

        while (true)
        {
            switch (m_currentToken.type)
            {
            case PLUS:
                operation = BarvazType::ADD;
                advance();
                break;
            
            case MINUS:
                operation = BarvazType::SUB;
                advance();
                break;

            default:
                isAddExpression = false;
                break;
            }

            if (!isAddExpression)
            {
                break;
            }

            rightOperand = mulExpr();
            leftOperand = new SyntaxBinaryOperator(leftOperand, rightOperand, operation);
        }

        return leftOperand;
    }

    AST * BarvazParser::mulExpr()
    {
        AST * leftOperand = NULL;
        AST * rightOperand = NULL;
        bool isMulExpression = true;
        BarvazType::TypeMethod operation;
        
        leftOperand = unaryExpr();

        while (true)
        {
            switch (m_currentToken.type)
            {
            case STAR:
                operation = BarvazType::MUL;
                advance();
                break;
            
            case SLASH:
                operation = BarvazType::DIV;
                advance();
                break;

            case PERCENT:
                operation = BarvazType::MOD;
                advance();
                break;

            default:
                isMulExpression = false;
                break;
            }

            if (!isMulExpression)
            {
                break;
            }

            rightOperand = unaryExpr();
            leftOperand = new SyntaxBinaryOperator(leftOperand, rightOperand, operation);
        }

        return leftOperand;
    }

    AST * BarvazParser::unaryExpr()
    {
        BarvazType::TypeMethod operation;
        bool isUnaryExpression = true;
        AST * ast = NULL;

        switch (m_currentToken.type)
        {
        case PLUS:
            operation = BarvazType::POS;
            advance();
            break;

        case MINUS:
            operation = BarvazType::NEG;
            advance();
            break;
        
        default:
            isUnaryExpression = false;
            break;
        }

        if (isUnaryExpression)
        {
            ast = new SyntaxUnaryOperator(unaryExpr(), operation);
        }

        else
        {
            ast = primary();
        }
        
        return ast;
    }

    AST * BarvazParser::primary()
    {
        return atom();
    }

    AST * BarvazParser::atom()
    {
        AST * ast = NULL;

        switch (m_currentToken.type)
        {
        case IDENTIFIER:
            ast = new SyntaxIdentifier(m_currentToken.valueString);
            advance();
            break;
        
        case INTEGER:
            ast = new SyntaxNumber(m_currentToken.valueString);
            advance();
            break;

        case LPAR:
            advance();
            ast = expr();
            
            if (RPAR == m_currentToken.type)
            {
                advance();
            }

            else
            {
                throw BarvazParserError("Invalid syntax");
            }

            break;

        default:
            throw BarvazParserError("Invalid syntax");
        }

        return ast;
    }
}