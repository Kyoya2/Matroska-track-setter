/*
 * Copyright 2021 Kyoya2
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "InteractiveTrackSelector.h"

InteractiveTrackSelector::InteractiveTrackSelector(const string& track_selection_rules_file) :
    m_track_prioritizer(track_selection_rules_file)
{}

void InteractiveTrackSelector::select_default_tracks_interactively(std::fstream& file_stream, const wstring& file_name)
{
    TrackManager track_manager(file_stream);

    const Tracks& subtitle_tracks = track_manager.get_subtitle_tracks();
    const Tracks& audio_tracks = track_manager.get_audio_tracks();

    track_manager.set_default_tracks(
        _s_select_default_track_interactively(
            subtitle_tracks,
            "Subtitle",
            m_track_prioritizer.get_subtitle_priorities(subtitle_tracks),
            m_subtitle_group_choices,
            m_single_subtitle_choices),

        _s_select_default_track_interactively(
            audio_tracks,
            "Audio",
            m_track_prioritizer.get_audio_priorities(audio_tracks),
            m_audio_group_choices,
            m_single_audio_choices));
}

TrackEntry* InteractiveTrackSelector::_s_select_default_track_interactively(
    const Tracks& tracks,
    const string& track_set_name,
    const TrackPriorityDescriptor& track_priorities,
    const TrackGroupChoices& track_group_choices,
    const TrackSingleChoices& track_single_choices)
{
    return nullptr;
}
