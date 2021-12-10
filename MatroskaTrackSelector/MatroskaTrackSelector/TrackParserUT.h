#pragma once
#include "UTCommon.h"
#include "TrackManager.h"
#include "TrackPrioritizer.h"

#include <fstream>

namespace TrackParserUT
{
    void run_tests()
    {
        std::fstream test_file("..\\..\\Test files\\1.mkv", std::ios_base::binary | std::ios_base::in);
        TrackManager track_parser(test_file);

        const Tracks& subs = track_parser.get_subtitle_tracks();

        TrackPrioritizer ts("..\\..\\Track selection rules.txt");

        ts.get_subtitle_priorities(subs);
    }
}