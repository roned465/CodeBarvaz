#ifndef TYPE_H_
#define TYPE_H_

namespace barvazobject
{
    class BarvazType
    {
        public:

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
        } TypeMethod;
    };
}

#endif  // TYPE_H_