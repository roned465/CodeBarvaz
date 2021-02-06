#ifndef SYNTAX_IDENTIFIER_H_
#define SYNTAX_IDENTIFIER_H_

#include <string>

#include "abstract_syntax_tree.hpp"

using namespace std;

namespace barvazsyntaxtree
{
    /**
     * @brief An AST node representing an identifier.
     *      contains the name of the identifier.
     */
    class SyntaxIdentifier : public AST
    {
        public:
        SyntaxIdentifier(string name);

        virtual ~SyntaxIdentifier();

        /**
         * @brief Prints the name of the identifier.
         */
        virtual void print(void) const;

        private:
        string m_name;
    };
}

#endif  // SYNTAX_IDENTIFIER_H_