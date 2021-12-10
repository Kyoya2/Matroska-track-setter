/*
 * Copyright 2021 Kyoya2
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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

        TrackPrioritizer ts("..\\..\\..\\..\\..\\Track selection rules.txt");

        ts.get_subtitle_priorities(subs);
    }
}