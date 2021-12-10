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
    const TrackEntry* get_most_eligible_track() const;

public:
    vector<const TrackEntry*> explicitly_excluded;  // Failed test 1
    vector<const TrackEntry*> not_included;         // Passed test 1 and failed test 2
    vector<const TrackEntry*> unmatching_language;  // Passed tests 1, 2 and failed test 3
    vector<const TrackEntry*> top_priority;         // Passed all 3 tests
};

class TrackPrioritizer
{
public:
    explicit TrackPrioritizer(const string& rules_file_path);

public:
    TrackPriorityDescriptor get_subtitle_priorities(const Tracks& tracks) const;
    TrackPriorityDescriptor get_audio_priorities(const Tracks& tracks) const;

PRIVATE:
    struct TrackSelectionRules
    {
    public:
        TrackSelectionRules() = default;

        TrackSelectionRules(const TrackSelectionRules&) = delete;
        TrackSelectionRules& operator=(const TrackSelectionRules&) = delete;

        TrackSelectionRules(TrackSelectionRules&&) = default;

    public:
        TrackPriorityDescriptor get_track_priorities(const Tracks& tracks) const;

        string language;
        vector<std::regex> include_keywords;
        vector<std::regex> exclude_keywords;
    };

PRIVATE:
    TrackSelectionRules m_subtitle_selection_rules;
    TrackSelectionRules m_audio_selection_rules;
};