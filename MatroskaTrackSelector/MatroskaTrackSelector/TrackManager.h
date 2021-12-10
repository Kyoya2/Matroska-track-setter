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
#pragma once
#include "Common.h"
#include "EbmlElement.h"
#include "TrackEntry.h"
#include "DefaultTrackSetterHandlers.h"

DECL_EXCEPTION(FittingHandlerNotFound);

class TrackManager
{
public:
    explicit TrackManager(std::iostream& stream);

public:
    Tracks& get_subtitle_tracks() { return m_subtitle_tracks;  }
    Tracks& get_audio_tracks() { return m_audio_tracks;  }

    void set_default_tracks(TrackEntry* subtitle_track, TrackEntry* audio_track);

PRIVATE:
    void _load_tracks_seek_position_element(BasicSharedPtr<EbmlElement>& seek_head_element);
    void _load_tracks(BasicSharedPtr<EbmlElement>& tracks_element);

    void _s_set_default_track(
        Tracks& tracks,                         // Either subtitle tracks or audio tracks
        TrackEntry* default_track,        // A pointer to the track to set as the default amongst the tracks in 'tracks'
        Tracks& other_tracks,                   // The track set that's not specified by 'tracks'. e.g. if track is subtitles then this is audio
        TrackEntry* untouchable_track);   // A pointer to the track amongst 'other_tracks' that shouldn't be modified

PRIVATE:
    BasicSharedPtr<EbmlElement> m_tracks_seek_position;
    Tracks m_subtitle_tracks;
    Tracks m_audio_tracks;

    // Theese refer to void elements that USUSALLY appear between top-level elements
    BasicSharedPtr<EbmlElement> m_void_before_tracks;
    BasicSharedPtr<EbmlElement> m_void_after_tracks;
};

