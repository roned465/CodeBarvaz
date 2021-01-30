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
        BarvazParser(BarvazTokenizer tokenizer);

        private:
        void advanceToken(void);

        Token m_currentToken;
    };
}

#endif  // PARSER_H_