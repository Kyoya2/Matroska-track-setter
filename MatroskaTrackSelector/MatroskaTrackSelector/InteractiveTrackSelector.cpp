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
    TrackPriorityDescriptor tracks_priority_descriptor = track_prioritizer.get_track_priorities(tracks);
    _s_print_track_selection_table(file_name, tracks_priority_descriptor);
    return nullptr;
}

void InteractiveTrackSelector::_s_print_track_selection_table(const wstring& file_name, const TrackPriorityDescriptor& track_priorities)
{
    static const vector<string> TABLE_HEADERS{ "#", "Name", "Language" };
}
