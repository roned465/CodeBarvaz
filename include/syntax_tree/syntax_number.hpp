#ifndef SYNTAX_NUMBER_H_
#define SYNTAX_NUMBER_H_

#include <string>

#include "abstract_syntax_tree.hpp"

using namespace std;

namespace barvazsyntaxtree
{
    /**
     * @brief An AST node representing a number.
     *      Contains the string that represents the number.
     */
    class SyntaxNumber : public AST
    {
        public:
        SyntaxNumber(string value);

        virtual ~SyntaxNumber();

        /**
         * @brief Prints the number.
         */
        virtual void print(void) const;

        private:
        string m_value;
    };
}

#endif  // SYNTAX_NUMBER_H_