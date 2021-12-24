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
#include "InteractiveTrackSelector.h"

static bool case_insensitive_strcmp(const string& a, const string& b) {
    for (size_t i = 0; i < std::min(a.size(), b.size()); ++i)
    {
        if (std::tolower(a[i]) < std::tolower(b[i]))
            return true;
        else if (std::tolower(a[i]) > std::tolower(b[i]))
            return false;
    }
    return false;
}

void InteractiveTrackSelector::select_trakcs_interactively(const wstring& files_dir, const vector<wstring>& file_names, const TrackPrioritizers& track_prioritizers)
{
    // Maps between track names (case insensitively) to vectors of track managers that have tracks with those names
    std::map<string, vector<shared_ptr<TrackManager>>, bool(*)(const string&, const string&)> subtitle_track_names(case_insensitive_strcmp);
    std::map<string, vector<shared_ptr<TrackManager>>, bool(*)(const string&, const string&)> audio_track_names(case_insensitive_strcmp);

    // for each track, add it's track manager to the vector that matches the key with the name of the track
    static const auto ADD_TRACKS_TO_MAP = [](decltype(subtitle_track_names) track_names_set, const Tracks& tracks, shared_ptr<TrackManager> track_manager)
    {
        for (size_t i = 0; i < tracks.size(); ++i)
        {
            if (tracks[i].track_name.empty())
                track_names_set[string("Unnamed track ") + std::to_string(i)].push_back(track_manager);
            else
                track_names_set[tracks[i].track_name].push_back(track_manager);
        }
    };

    for (size_t i = 0; i < file_names.size(); ++i)
    {
        auto track_manager = std::make_shared<TrackManager>(files_dir + file_names[i]);

        ADD_TRACKS_TO_MAP(subtitle_track_names, track_manager->get_subtitle_tracks(), track_manager);
        ADD_TRACKS_TO_MAP(audio_track_names, track_manager->get_audio_tracks(), track_manager);
    }
}

std::pair<const TrackEntry*, size_t> InteractiveTrackSelector::_s_prompt_track_selection(const wstring& file_name, const TrackPriorityDescriptor& track_priorities)
{
    using namespace ConsoleAttributes;

    static const vector<string> TABLE_HEADERS{ "#", "Name", "Language" };

    static const string_view& EXPLICITLY_EXCLUDED_TRACKS_COLOR = RedFG;
    static const string_view& NOT_INCLUDED_TRACKS_COLOR = YellowFG;
    static const string_view& UNMATCHING_LUANGUAGE_TRACKS_COLOR = BlueFG;
    static const string_view& TOP_PRIORITY_TRACKS_COLOR = GreenFG;

    string table_title = (track_priorities.get_most_eligible_track()->track_type == TrackType::Subtitle) ? "Subtitle" : "Audio";
    
    table_title += " tracks in " + Utility::wstring_to_string(file_name);

    vector<vector<string>> rows;

    return std::pair<const TrackEntry*, size_t>();
}