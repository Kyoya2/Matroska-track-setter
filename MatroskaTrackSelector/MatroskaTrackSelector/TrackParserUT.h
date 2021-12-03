#pragma once
#include "UTCommon.h"
#include "TrackManager.h"
#include "TrackSelector.h"

#include <fstream>

namespace TrackParserUT
{
    void run_tests()
    {
        //std::fstream test_file("..\\..\\Test files\\1.mkv", std::ios_base::binary | std::ios_base::in);
        //TrackManager track_parser(test_file);

        TrackSelector ts("..\\..\\Track selection rules.txt");
    }
}