#pragma once
#include "UTCommon.h"
#include "EbmlElement.h"

#include <ios>
#include <fstream>

namespace EbmlParserUT
{
    void run_tests()
    {
        std::fstream test_file("..\\..\\Test files\\1.mkv", std::ios_base::binary | std::ios_base::in);
        auto root = EbmlElement::s_construct_from_stream(test_file);
        cout << root;
    }
}