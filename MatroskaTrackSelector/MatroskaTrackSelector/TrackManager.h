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

#include "Common.h"
#include "EbmlElement.h"
#include "TrackEntry.h"
#include "DefaultTrackSetterHandlers.h"

DECL_EXCEPTION(FittingHandlerNotFound);

class TrackManager
{
public:
    explicit TrackManager(const wstring& file);

public:
    const Tracks& get_subtitle_tracks() { return m_subtitle_tracks;  }
    const Tracks& get_audio_tracks() { return m_audio_tracks;  }

    void set_default_tracks(const TrackEntry* subtitle_track, const TrackEntry* audio_track);

PRIVATE:
    void _load_tracks_seek_position_element(BasicSharedPtr<EbmlElement>& seek_head_element);
    void _load_tracks(BasicSharedPtr<EbmlElement>& tracks_element);

    void _s_set_default_track(
        Tracks& tracks,                         // Either subtitle tracks or audio tracks
        TrackEntry* default_track,              // A pointer to the track to set as the default amongst the tracks in 'tracks'
        Tracks& other_tracks,                   // The track set that's not specified by 'tracks'. e.g. if track is subtitles then this is audio
        const TrackEntry* untouchable_track);   // A pointer to the track amongst 'other_tracks' that shouldn't be modified

PRIVATE:
    std::fstream m_file_stream;
    BasicSharedPtr<EbmlElement> m_tracks_seek_position;
    Tracks m_subtitle_tracks;
    Tracks m_audio_tracks;

    // Theese refer to void elements that USUSALLY appear between top-level elements
    BasicSharedPtr<EbmlElement> m_void_before_tracks;
    BasicSharedPtr<EbmlElement> m_void_after_tracks;
};

