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
    
    for (size_t i = 0; i < file_names.size(); ++i)
    {
        auto track_manager = std::make_shared<TrackManager>(files_dir + file_names[i]);
    
        _s_add_tracks_to_map(subtitle_tracks_map, track_manager->get_subtitle_tracks(), track_manager, track_prioritizers.first);
        _s_add_tracks_to_map(audio_tracks_map, track_manager->get_audio_tracks(), track_manager, track_prioritizers.second);
    }

    _s_select_tracks_interactively(subtitle_tracks_map, "subtitle");
    _s_select_tracks_interactively(audio_tracks_map, "audio");
}

void InteractiveTrackSelector::_s_add_tracks_to_map(TracksMap& tracks_map, const Tracks& tracks, shared_ptr<TrackManager> track_manager, const TrackPrioritizer& track_prioritizer)
{
    using namespace ConsoleAttributes;
    static const string_view& EXPLICITLY_EXCLUDED_TRACKS_COLOR = RedFG;
    static const string_view& NOT_INCLUDED_TRACKS_COLOR = YellowFG;
    static const string_view& UNMATCHING_LUANGUAGE_TRACKS_COLOR = BlueFG;
    static const string_view& TOP_PRIORITY_TRACKS_COLOR = GreenFG;

    for (size_t i = 0; i < tracks.size(); ++i)
    {
        const string_view* name_color = nullptr;
        switch (track_prioritizer.get_track_priority(tracks[i]))
        {
        case TrackPriorityDescriptor::ExplicitlyExcluded:
            name_color = &EXPLICITLY_EXCLUDED_TRACKS_COLOR;
            break;

        case TrackPriorityDescriptor::NotIncluded:
            name_color = &NOT_INCLUDED_TRACKS_COLOR;
            break;

        case TrackPriorityDescriptor::UnmatchingLanguage:
            name_color = &UNMATCHING_LUANGUAGE_TRACKS_COLOR;
            break;

        case TrackPriorityDescriptor::TopPriority:
            name_color = &TOP_PRIORITY_TRACKS_COLOR;
            break;
        }

        MinTrackEntry min_track_entry(tracks[i], i);
        min_track_entry.name = string(*name_color) + min_track_entry.name + string(WhiteFG);

        tracks_map[std::move(min_track_entry)].push_back(track_manager);
    }
}

void InteractiveTrackSelector::_s_select_tracks_interactively(TracksMap& tracks_map, const string& track_set_name)
{
    static const vector<string> TABLE_HEADERS{ "#", "Common", "Name", "Language" };
    vector<vector<string>> rows;

    size_t i = 1;
    for (auto const& [track_entry, track_managers] : tracks_map)
    {
        rows.emplace_back(vector{
            std::to_string(i),
            std::to_string(track_managers.size()) + "/" + std::to_string(tracks_map.size()),
            track_entry.name,
            string(track_entry.language)});
        ++i;
    }

    size_t choice = 0;
    ConsoleUtils::print_table(string("Remaining") + track_set_name + "tracks", TABLE_HEADERS, rows);
    std::cin >> choice;
    
}