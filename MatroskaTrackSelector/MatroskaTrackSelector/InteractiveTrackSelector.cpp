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

InteractiveTrackSelector::InteractiveTrackSelector(const TrackPrioritizers& track_prioritizers, bool semi_automatic) :
    m_track_prioritizers(track_prioritizers),
    m_semi_automatic(semi_automatic)
{}

void InteractiveTrackSelector::select_default_tracks_interactively(std::fstream& file_stream, const wstring& file_name)
{
    TrackManager track_manager(file_stream);

    const Tracks& subtitle_tracks = track_manager.get_subtitle_tracks();
    const Tracks& audio_tracks = track_manager.get_audio_tracks();

    track_manager.set_default_tracks(
        _s_select_default_track_interactively(
            file_name,
            subtitle_tracks,
            m_track_prioritizers.first,
            m_subtitle_group_choices,
            m_single_subtitle_choices,
            m_semi_automatic),

        _s_select_default_track_interactively(
            file_name,
            audio_tracks,
            m_track_prioritizers.second,
            m_audio_group_choices,
            m_single_audio_choices,
            m_semi_automatic));
}

TrackEntry* InteractiveTrackSelector::_s_select_default_track_interactively(
    const wstring& file_name,
    const Tracks& tracks,
    const TrackPrioritizer& track_prioritizer,
    const TrackGroupChoices& track_group_choices,
    const TrackSingleChoices& track_single_choices,
    const bool semi_automatic)
{
    const vector<TrackEntryHash> track_hashes = TrackEntryHasher::s_get_track_hashes(tracks);
    /*
    count how many of the track hashes are in "track_single_choices"
        if there is 1, choose it
        if there are more than 1, check if one of them can be selected by 
            if it is, select the 

    
    
    
    */

    TrackPriorityDescriptor tracks_priority_descriptor = track_prioritizer.get_track_priorities(tracks);
    _s_prompt_track_selection(file_name, tracks_priority_descriptor);
    return nullptr;
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