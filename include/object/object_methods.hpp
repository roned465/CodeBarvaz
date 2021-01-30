#ifndef OBJECT_METHODS_H_
#define OBJECT_METHODS_H_

#include <string>

using namespace std;

namespace barvazobject
{
    typedef enum
    {
        ADD,            // x + y
        SUB,            // x - y
        MUL,            // x * y
        DIV,            // x / y
        MOD,            // x % y
        POS,            // + x
        NEG,            // - x
        EQ,             // x == y
        NEQ,            // x != y
    } ObjectMethod;

    string getMethodSign(ObjectMethod method);
}


#endif  // OBJECT_METHODS_H_