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
        TrackManager track_parser(L"..\\..\\..\\..\\..\\Test files\\1.mkv");

        const Tracks& subs = track_parser.get_subtitle_tracks();

        TrackPrioritizers ts = TrackPrioritizer::s_from_file("Track selection rules.txt");

        ts.first.get_track_priority(subs[0]);
    }
}