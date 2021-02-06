#ifndef PARSER_H_
#define PARSER_H_

#include "abstract_syntax_tree.hpp"
#include "token.hpp"
#include "tokenizer.hpp"

using namespace barvazsyntaxtree;

namespace barvazparser
{
    /**
     * @brief The class implements a parser for the Barvaz language, that receives
     *      a stream of tokens by a tokenizer and parses them to construct an
     *      abstract syntax tree for the code.
     *      The parser is a left-to-right top-down parser, with a set of grammatic rules
     *      for how to parse each non-terminal expression.
     *      * Currently only parses basic mathematical expressions.
     */
    class BarvazParser
    {
        public:
        BarvazParser(BarvazTokenizer& tokenizer);

        /**
         *  Grammatic rules parsers
         *  Each of the following functions represent a non-terminal rule
         *  of the grammer for the Barvaz syntax.
         */

        /**
         * @brief Parses a mathematical expression.
         *      The grammatic rule:
         *      
         *      expr: addExpr
         * 
         * @return The parsed AST.
         */
        AST * expr(void);

        /**
         * @brief Parses a mathematical additive expression.
         *      The grammatic rule:
         *      
         *      addExpr: mulExpr ((PLUS|MINUS) mulExpr)*
         * 
         *      The constructed AST is left-assosiative.
         * 
         * @return The parsed AST.
         */
        AST * addExpr(void);

        /**
         * @brief Parses a mathematical multiplicative expression.
         *      The grammatic rule:
         *      
         *      mulExpr: unaryExpr ((STAR|SLASH|PERCENT) unaryExpr)*
         * 
         *      The constructed AST is left-assosiative.
         *          
         * @return The parsed AST.
         */
        AST * mulExpr(void);

        /**
         * @brief Parses a mathematical unary operation expression.
         *      The grammatic rule:
         *      
         *      unaryExpr: ((PLUS|MINUS) unaryExpr) | primary
         * 
         *      The constructed AST is right-assosiative.
         *          
         * @return The parsed AST.
         */
        AST * unaryExpr(void);

        /**
         * @brief Parses a primary of the language.
         *      The grammatic rule:
         *      
         *      primary: atom
         *          
         * @return The parsed AST.
         */
        AST * primary(void);

        /**
         * @brief Parses an atomic unit of the language.
         *      The grammatic rule:
         *      
         *      atom: IDENTIFIER | NUMBER | (LPAR expr RPAR)
         *          
         * @return The parsed AST.
         */
        AST * atom(void);

        private:
        /**
         * @brief Advances the parser to the next token.
         */
        void advance(void);

        Token m_currentToken;  // The current token pointed by the parser.
        BarvazTokenizer& m_tokenizer;  // The tokenizer used by the parser to get tokens input.
    };
}

#endif  // PARSER_H_