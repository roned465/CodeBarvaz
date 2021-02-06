#ifndef ABSTRACT_SYNTAX_TREE_H_
#define ABSTRACT_SYNTAX_TREE_H_

#include <iostream>

using namespace std;

namespace barvazsyntaxtree
{
    /**
     * @brief A base class for AST nodes of the Barvaz language.
     *      The class represents an abstract syntax tree of the language,
     *      which is created by the parser and executed later on.
     *      The class has a virtual evaluate function (TODO) that walks through
     *      the tree and evaluates it.
     */
    class AST
    {
        public:
        /**
         * @brief A virtual destructor for the AST.
         */
        virtual ~AST();

        /**
         * @brief A virtual printing function for the AST.
         *      Goes through the tree and prints all the nodes.
         */
        virtual void print(void) const = 0;

        /**
         * @brief Overloads the << operator with ostream and AST,
         *      calls the print function above.
         */
        friend ostream& operator<<(ostream& os, const AST& ast);
    };
}

#endif  // ABSTRACT_SYNTAX_TREE_H_