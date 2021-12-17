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

InteractiveTrackSelector::InteractiveTrackSelector(const TrackPrioritizer& track_prioritizer, bool semi_automatic) :
    m_track_prioritizer(track_prioritizer),
    m_semi_automatic(semi_automatic)
{}

void InteractiveTrackSelector::select_default_tracks_interactively(std::fstream& file_stream, const wstring& file_name)
{
    TrackManager track_manager(file_stream);

    Tracks& subtitle_tracks = track_manager.get_subtitle_tracks();
    Tracks& audio_tracks = track_manager.get_audio_tracks();

    track_manager.set_default_tracks(
        _s_select_default_track_interactively(
            file_name,
            subtitle_tracks,
            "Subtitle",
            m_track_prioritizer.get_subtitle_priorities(subtitle_tracks),
            m_subtitle_group_choices,
            m_single_subtitle_choices,
            m_semi_automatic),

        _s_select_default_track_interactively(
            file_name,
            audio_tracks,
            "Audio",
            m_track_prioritizer.get_audio_priorities(audio_tracks),
            m_audio_group_choices,
            m_single_audio_choices,
            m_semi_automatic));
}

TrackEntry* InteractiveTrackSelector::_s_select_default_track_interactively(
    const wstring& file_name,
    const Tracks& tracks,
    const string& track_set_name,
    const TrackPriorityDescriptor& track_priorities,
    const TrackGroupChoices& track_group_choices,
    const TrackSingleChoices& track_single_choices,
    const bool semi_automatic)
{
    return nullptr;
}
