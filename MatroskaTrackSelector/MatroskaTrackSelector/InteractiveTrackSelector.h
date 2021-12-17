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

#include <map>
#include <set>
#include <fstream>

#include "Common.h"
#include "TrackPrioritizer.h"
#include "TrackManager.h"

DECL_EXCEPTION(FileSelectionError);

class InteractiveTrackSelector
{
public:
    InteractiveTrackSelector(const TrackPrioritizer& track_prioritizer, bool semi_automatic = true);

    InteractiveTrackSelector(const InteractiveTrackSelector&) = delete;
    InteractiveTrackSelector& operator=(const InteractiveTrackSelector&) = delete;

public:
    void select_default_tracks_interactively(std::fstream& file_stream, const wstring& file_name);

private:
    using TrackGroupChoices = std::map<vector<TrackEntry>, size_t>;
    using TrackSingleChoices = std::set<TrackEntry>;

private:
    static TrackEntry* _s_select_default_track_interactively(
        const wstring& file_name,
        const Tracks& tracks,
        const string& track_set_name,
        const TrackPriorityDescriptor& track_priorities,
        const TrackGroupChoices& track_group_choices,
        const TrackSingleChoices& track_single_choices,
        const bool semi_automatic
    );

private:
    const TrackPrioritizer& m_track_prioritizer;
    const bool m_semi_automatic; // True if "m_single_*_choices" should be used

    // Maps between track groups and indices of the chosen track in those groups
    TrackGroupChoices m_subtitle_group_choices;
    TrackGroupChoices m_audio_group_choices;

    // Contains 
    TrackSingleChoices m_single_subtitle_choices;
    TrackSingleChoices m_single_audio_choices;
};

