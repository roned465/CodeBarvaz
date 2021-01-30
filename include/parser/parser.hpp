#ifndef PARSER_H_
#define PARSER_H_

#include "abstract_syntax_tree.hpp"
#include "token.hpp"
#include "tokenizer.hpp"

using namespace barvazsyntaxtree;

namespace barvazparser
{
    /**
     * 
     */
    class BarvazParser
    {
        public:
        BarvazParser(BarvazTokenizer& tokenizer);

        AST * expr(void);

        AST * addExpr(void);

        AST * mulExpr(void);

        AST * unaryExpr(void);

        AST * primary(void);

        AST * atom(void);

        private:
        void advanceToken(void);

        Token m_currentToken;
        BarvazTokenizer& tokenizer;
    };
}

#endif  // PARSER_H_