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
        // Get the first token.
        advance();
    }

    void BarvazParser::advance(void)
    {
        // Get the next token from the tokenizer and store it.
        m_currentToken = m_tokenizer.getNextToken();
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
                // Reached the end of the additive expression.
                isAddExpression = false;
                break;
            }

            if (!isAddExpression)
            {
                break;
            }

            rightOperand = mulExpr();
            
            // Construct the AST.
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
                // Reached the end of the multiplicative expression.
                isMulExpression = false;
                break;
            }

            if (!isMulExpression)
            {
                break;
            }

            rightOperand = unaryExpr();
            
            // Construct the AST.
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
            // Reached the end of the unary expression.
            isUnaryExpression = false;
            break;
        }

        // Construct the AST.
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

            // Parse the expression inside the parentheses.
            ast = expr();
            
            // Expect for a closing right parenthesis.
            // If there isn't, any there is a syntax error.
            if (RPAR == m_currentToken.type)
            {
                advance();
            }

            else
            {
                throw BarvazParserError("Invalid syntax");
            }

            break;

        // If none of the cases is true, an atomic unit cannot be parsed
        // and there is a syntax error 
        default:
            throw BarvazParserError("Invalid syntax");
        }

        return ast;
    }
}