/*   
 *   Matroska track setter  Copyright (C) 2021  Kyoya2
 *   
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *   
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *   
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#pragma once
#include "UTCommon.h"
#include "TrackManager.h"
#include "TrackPrioritizer.h"

#include <fstream>

namespace TrackParserUT
{
    void run_tests()
    {
        std::fstream test_file("..\\..\\..\\..\\..\\Test files\\1.mkv", std::ios_base::binary | std::ios_base::in);
        TrackManager track_parser(test_file);

        Tracks& subs = track_parser.get_subtitle_tracks();

        TrackPrioritizer ts("Track selection rules.txt");

        ts.get_subtitle_priorities(subs);
    }
}