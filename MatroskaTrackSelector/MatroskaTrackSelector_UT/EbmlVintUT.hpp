#include "UTCommon.hpp"

//#define private public
#include "EbmlVint.h"

namespace EbmlVintUT
{
    void run_tests()
    {
        EbmlVint<true> vint(0x80 | 12);
        REQUIRE(vint.get_value() == 12);
    }
}