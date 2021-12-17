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

#include <fstream>
#include <regex>

#include "Common.h"
#include "TrackEntry.h"

DECL_EXCEPTION(TrackRulesParsingError);

struct TrackPriorityDescriptor
{
public:
    TrackPriorityDescriptor() = default;

    TrackPriorityDescriptor(const TrackPriorityDescriptor&) = delete;
    TrackPriorityDescriptor& operator=(const TrackPriorityDescriptor&) = delete;

    TrackPriorityDescriptor(TrackPriorityDescriptor&&) = default;

public:
    // Return the first track from the category that passed the most tests
    TrackEntry* get_most_eligible_track() const;

public:
    vector<TrackEntry*> explicitly_excluded;  // Failed test 1
    vector<TrackEntry*> not_included;         // Passed test 1 and failed test 2
    vector<TrackEntry*> unmatching_language;  // Passed tests 1, 2 and failed test 3
    vector<TrackEntry*> top_priority;         // Passed all 3 tests
};

class TrackPrioritizer
{
public:
    explicit TrackPrioritizer(const string& rules_file_path);

public:
    TrackPriorityDescriptor get_subtitle_priorities(Tracks& tracks) const;
    TrackPriorityDescriptor get_audio_priorities(Tracks& tracks) const;

PRIVATE:
    struct TrackSelectionRules
    {
    public:
        TrackSelectionRules() = default;

        TrackSelectionRules(const TrackSelectionRules&) = delete;
        TrackSelectionRules& operator=(const TrackSelectionRules&) = delete;

        TrackSelectionRules(TrackSelectionRules&&) = default;

    public:
        TrackPriorityDescriptor get_track_priorities(Tracks& tracks) const;

        string language;
        vector<std::regex> include_keywords;
        vector<std::regex> exclude_keywords;
    };

PRIVATE:
    TrackSelectionRules m_subtitle_selection_rules;
    TrackSelectionRules m_audio_selection_rules;
};