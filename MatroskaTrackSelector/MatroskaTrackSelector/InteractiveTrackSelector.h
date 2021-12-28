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
#include <map>
#include <memory>
#include <cstring>

#include "Common.h"
#include "TrackPrioritizer.h"
#include "TrackManager.h"
#include "ConsoleUtils.h"

DECL_EXCEPTION(FileSelectionError);

using std::shared_ptr;

struct MinTrackEntry
{
    MinTrackEntry(const TrackEntry& track_entry, size_t index) :
        name(track_entry.name.empty() ? ("Unnamed track " + std::to_string(index)) : track_entry.name),
        language(track_entry.language)
    {}

    MinTrackEntry(MinTrackEntry&&) = default;

    string name;
    const string_view& language;
};

class InteractiveTrackSelector
{
public:
    InteractiveTrackSelector() = delete;

    InteractiveTrackSelector(const InteractiveTrackSelector&) = delete;
    InteractiveTrackSelector& operator=(const InteractiveTrackSelector&) = delete;

public:
    static void s_select_tracks_interactively(const wstring& files_dir, const vector<wstring>& file_names, const TrackPrioritizers& track_prioritizers);

private:
    using TracksMap = std::map<MinTrackEntry, vector<shared_ptr<TrackManager>>, bool(*)(const MinTrackEntry&, const MinTrackEntry&)>;

private:
    static void _s_add_tracks_to_map(
        TracksMap& tracks_map,
        const Tracks& tracks,
        shared_ptr<TrackManager> track_manager,
        const TrackPrioritizer& track_prioritizer);
    static void _s_select_tracks_interactively(TracksMap& tracks_map, const string& track_set_name, size_t num_files);
};

