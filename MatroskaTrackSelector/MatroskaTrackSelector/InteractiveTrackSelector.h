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
#include <limits>
#include <sstream>
#include <algorithm>

#include "Common.h"
#include "TrackPrioritizer.h"
#include "TrackManager.h"
#include "MinTrackEntry.h"
#include "MatroskaElementSpecification.h"
#include "AutomaticTrackSelector.h"

DECL_EXCEPTION(FileSelectionError);

using std::shared_ptr;


class InteractiveTrackSelector
{
public:
    InteractiveTrackSelector() = delete;

    InteractiveTrackSelector(const InteractiveTrackSelector&) = delete;
    InteractiveTrackSelector& operator=(const InteractiveTrackSelector&) = delete;

public:
    static void s_select_tracks_interactively(const wstring& files_dir, const vector<wstring>& file_names, const TrackPrioritizers& track_prioritizers);

private:
    using TracksMapValueContent = pair<shared_ptr<AutomaticTrackSelector>, size_t>;
    using TracksMap = std::map<MinTrackEntry, vector<TracksMapValueContent>>;

private:
    static void _s_add_tracks_to_map(
        TracksMap& tracks_map,
        const Tracks& tracks,
        shared_ptr<AutomaticTrackSelector> track_selector);
    static void _s_select_tracks_interactively(TracksMap& tracks_map, const TrackType track_type, const TrackPrioritizer& track_prioritizer, size_t num_files);
};

