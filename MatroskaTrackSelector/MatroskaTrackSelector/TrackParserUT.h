#pragma once
#include "UTCommon.h"
#include "TrackParser.h"

#include <fstream>

namespace TrackParserUT
{
    void run_tests()
    {
        std::fstream test_file("..\\..\\Test files\\1.mkv", std::ios_base::binary | std::ios_base::in);
        TrackParser track_parser(test_file);
    }
}