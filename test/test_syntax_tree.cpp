#include <iostream>

#include "abstract_syntax_tree.hpp"
#include "syntax_binary_operator.hpp"
#include "syntax_identifier.hpp"
#include "syntax_number.hpp"
#include "syntax_unary_operator.hpp"
#include "type.hpp"

using namespace std;

using namespace barvazsyntaxtree;
using namespace barvazobject;

int main()
{
    AST * ast =
    new SyntaxBinaryOperator(
        new SyntaxUnaryOperator(
            new SyntaxNumber("4"),
            BarvazType::NEG
        ),
        new SyntaxBinaryOperator(
            new SyntaxIdentifier("x"),
            new SyntaxNumber("3"),
            BarvazType::ADD
        ),
        BarvazType::MUL
    );

    cout << *ast << endl;

    delete ast;
}