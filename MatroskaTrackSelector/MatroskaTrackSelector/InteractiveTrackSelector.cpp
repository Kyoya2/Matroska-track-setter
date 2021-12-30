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

void InteractiveTrackSelector::s_select_tracks_interactively(const wstring& files_dir, const vector<wstring>& file_names, const TrackPrioritizers& track_prioritizers)
{
    // Maps between track names (case insensitively) to vectors of track selectors that have tracks with those names
    TracksMap subtitle_tracks_map;
    TracksMap audio_tracks_map;
    
    size_t num_subtitle_files = 0;
    size_t num_audio_files = 0;

    for (size_t i = 0; i < file_names.size(); ++i)
    {
        auto track_selector = std::make_shared<AutomaticTrackSelector>(files_dir + file_names[i]);

        if (track_selector->get_subtitle_tracks().size() > 0)
        {
            _s_add_tracks_to_map(subtitle_tracks_map, track_selector->get_subtitle_tracks(), track_selector);
            ++num_subtitle_files;
        }

        if (track_selector->get_audio_tracks().size() > 0)
        {
            _s_add_tracks_to_map(audio_tracks_map, track_selector->get_audio_tracks(), track_selector);
            ++num_audio_files;
        }
    }

    _s_select_tracks_interactively(subtitle_tracks_map, TrackType::Subtitle, track_prioritizers.first, num_subtitle_files);
    _s_select_tracks_interactively(audio_tracks_map, TrackType::Audio, track_prioritizers.second, num_audio_files);
}

void InteractiveTrackSelector::_s_add_tracks_to_map(TracksMap& tracks_map, const Tracks& tracks, shared_ptr<AutomaticTrackSelector> track_selector)
{
    size_t unnamed_track_count = 1;

    for (size_t i = 0; i < tracks.size(); ++i)
    {
        tracks_map[MinTrackEntry(tracks[i], unnamed_track_count)].emplace_back(track_selector, i);

        if (tracks[i].name.empty())
            ++unnamed_track_count;
    }
}

void InteractiveTrackSelector::_s_select_tracks_interactively(TracksMap& tracks_map, const TrackType track_type, const TrackPrioritizer& track_prioritizer, size_t num_files)
{
    static const vector<string> TABLE_HEADERS{ "#", "%", "Name", "Language" };

    while (tracks_map.size() > 0)
    {
        ConsoleUtils::cls();
        
        // Building table to print
        vector<vector<string>> table_rows;
        string num_files_str = std::to_string(num_files);
        size_t i = 1;
        for (const auto& [track_entry, track_selectors] : tracks_map)
        {
            std::stringstream strstr;
            float percentage = static_cast<float>(track_selectors.size()) / num_files * 100;
            strstr << std::setprecision(percentage >= 10 ? 4 : 3) << percentage << '%';

            table_rows.emplace_back(vector{
                std::to_string(i),
                std::move(strstr.str()),
                track_entry.get_colored_name(track_prioritizer),
                string(track_entry.language) });
            ++i;
        }

        size_t choice = 0;
        ConsoleUtils::print_table(string("Choose a ") + ((track_type == TrackType::Subtitle) ? "subtitle" : "audio") + " track", TABLE_HEADERS, table_rows);

        // Prompt for input
        cout << "Enter the number of the track you want to choose: ";
        if (!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        else if (choice > tracks_map.size() || choice == 0)
            continue;


        auto selected_element = tracks_map.begin();
        std::advance(selected_element, choice - 1);

        // Iterate over all track selectors that contain the selected track
        for (const auto& [track_selector, track_index] : selected_element->second)
        {
            // Set the selected track as the default track
            if (track_type == TrackType::Subtitle)
                track_selector->mark_subtitle_track_for_selection(track_index);
            else // if (track_type == TrackType::Audio)
                track_selector->mark_audio_track_for_selection(track_index);

            // Remove the current track selector from ALL key-value pairs in the tracks map
            for (auto map_key_value_pair = tracks_map.begin(); map_key_value_pair != tracks_map.end();)
            {
                // Don't remove the selector from the current key-vale pair as to not invalidate the iterator
                // Nonethelss, we will remove the whole key-value pair outside this loop
                if (map_key_value_pair->second.data() == selected_element->second.data())
                {
                    ++map_key_value_pair;
                    continue;
                }
                
                // If the current vector contains the current track selector, remove the selector from the vector
                auto it = map_key_value_pair->second.begin();
                while ((it != map_key_value_pair->second.end()) &&
                       (it->first != track_selector))
                {
                    ++it;
                }
                if (it != map_key_value_pair->second.end())
                    map_key_value_pair->second.erase(it);

                // If the current track entry doesn't have any more track selectors, remove it from the map
                if (0 == map_key_value_pair->second.size())
                {
                    map_key_value_pair = tracks_map.erase(map_key_value_pair);
                    continue;
                }
                else
                    ++map_key_value_pair;
            }
        }

        num_files -= selected_element->second.size();

        // Remove the selected track entry from the map
        tracks_map.erase(selected_element->first);
    }
}
