#ifndef BARVAZ_OBJECT_H_
#define BARVAZ_OBJECT_H_

#include "barvaz_type.hpp"

namespace barvazobject
{
    class BarvazObject
    {
        public:
        BarvazType type;
        void * value;
    };
}

#endif  // BARVAZ_OBJECT_H_