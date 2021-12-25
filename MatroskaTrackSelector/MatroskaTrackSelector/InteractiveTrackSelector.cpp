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

static bool _s_track_entry_comparison(const MinTrackEntry& a, const MinTrackEntry& b)
{
    for (size_t i = 0; i < std::min(a.name.size(), b.name.size()); ++i)
    {
        if (std::tolower(a.name[i]) < std::tolower(b.name[i]))
            return true;
        else if (std::tolower(a.name[i]) > std::tolower(b.name[i]))
            return false;
    }
    return std::strcmp(a.language.data(), b.language.data()) < 0;
}

void InteractiveTrackSelector::s_select_tracks_interactively(const wstring& files_dir, const vector<wstring>& file_names, const TrackPrioritizers& track_prioritizers)
{
    // Maps between track names (case insensitively) to vectors of track managers that have tracks with those names
    TracksMap subtitle_tracks_map(_s_track_entry_comparison);
    TracksMap audio_tracks_map(_s_track_entry_comparison);
    
    // for each track, add it's track manager to the vector that matches the key with the name of the track
    static const auto ADD_TRACKS_TO_MAP = [](decltype(subtitle_tracks_map)& tracks_map, const Tracks& tracks, shared_ptr<TrackManager> track_manager)
    {
        for (size_t i = 0; i < tracks.size(); ++i)
        {
            tracks_map[MinTrackEntry(tracks[i], i)].push_back(track_manager);
        }
    };
    
    for (size_t i = 0; i < file_names.size(); ++i)
    {
        auto track_manager = std::make_shared<TrackManager>(files_dir + file_names[i]);
    
        ADD_TRACKS_TO_MAP(subtitle_tracks_map, track_manager->get_subtitle_tracks(), track_manager);
        ADD_TRACKS_TO_MAP(audio_tracks_map, track_manager->get_audio_tracks(), track_manager);
    }

    //while ()
}

void InteractiveTrackSelector::_s_select_tracks_interactively(TracksMap& tracks_map, TrackPrioritizer track_prioritizer)
{
    using namespace ConsoleAttributes;

    static const vector<string> TABLE_HEADERS{ "#", "Name", "Language" };

    static const string_view& EXPLICITLY_EXCLUDED_TRACKS_COLOR = RedFG;
    static const string_view& NOT_INCLUDED_TRACKS_COLOR = YellowFG;
    static const string_view& UNMATCHING_LUANGUAGE_TRACKS_COLOR = BlueFG;
    static const string_view& TOP_PRIORITY_TRACKS_COLOR = GreenFG;

}