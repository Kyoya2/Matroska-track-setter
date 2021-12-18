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

#include <map>
#include <set>
#include <fstream>

#include "Common.h"
#include "TrackPrioritizer.h"
#include "TrackManager.h"
#include "ConsoleUtils.h"

DECL_EXCEPTION(FileSelectionError);

class InteractiveTrackSelector
{
public:
    InteractiveTrackSelector(const TrackPrioritizers& track_prioritizers, bool semi_automatic = true);

    InteractiveTrackSelector(const InteractiveTrackSelector&) = delete;
    InteractiveTrackSelector& operator=(const InteractiveTrackSelector&) = delete;

public:
    void select_default_tracks_interactively(std::fstream& file_stream, const wstring& file_name);

private:
    // Maps between track group hashes and the index of the selected track in the group
    using TrackGroupChoices = std::map<TrackGroupHash, size_t>;

    // A set of hashes of selected tracks
    using TrackSingleChoices = std::set<TrackEntryHash>;

private:
    static TrackEntry* _s_select_default_track_interactively(
        const wstring& file_name,
        const Tracks& tracks,
        const TrackPrioritizer& track_prioritizer,
        const TrackGroupChoices& track_group_choices,
        const TrackSingleChoices& track_single_choices,
        const bool semi_automatic
    );

    // Prompts the user to select a track
    static std::pair<const TrackEntry*, size_t> _s_prompt_track_selection(const wstring& file_name, const TrackPriorityDescriptor& track_priorities);

private:
    const TrackPrioritizers& m_track_prioritizers;
    const bool m_semi_automatic; // True if "m_single_*_choices" should be used

    TrackGroupChoices m_subtitle_group_choices;
    TrackGroupChoices m_audio_group_choices;

    TrackSingleChoices m_single_subtitle_choices;
    TrackSingleChoices m_single_audio_choices;
};

