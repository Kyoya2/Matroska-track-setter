/*   
 *   Matroska track setter  Copyright (C) 2023  Kyoya2
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
#include "OldEbmlElement.h"
#include "TrackEntry.h"
#include "SeekEntry.h"

class TrackManager
{
public:
    explicit TrackManager(const string& file);

public:
    Tracks& get_subtitle_tracks() { return m_subtitle_tracks;  }
    Tracks& get_audio_tracks() { return m_audio_tracks;  }

    void set_default_tracks(TrackEntry* subtitle_track, TrackEntry* audio_track);
    void set_default_tracks(size_t subtitle_track_index, size_t audio_track_index);

PRIVATE:
    void _load_tracks(OldEbmlElementPtr& tracks_element);
    void _load_seek_entries(OldEbmlElementPtr& seek_head_element);
    void _set_default_track(
        Tracks& tracks,                   // Either subtitle tracks or audio tracks
        TrackEntry* default_track,        // A pointer to the track to set as the default amongst the tracks in 'tracks'
        Tracks& other_tracks,             // The track set that's not specified by 'tracks'. e.g. if `tracks` is subtitles then this is audio
        TrackEntry* untouchable_track);   // A pointer to the track amongst 'other_tracks' that shouldn't be modified

    inline bool _are_tracks_loaded() { return !m_audio_tracks.empty(); }

PRIVATE:
    std::fstream m_file_stream;
    vector<SeekEntry> m_seek_entries;
    Tracks m_subtitle_tracks;
    Tracks m_audio_tracks;

    // The first entry points to a top-level void element, the second entry contains all top-level elements
    // between that void element and the 'Tracks' entry
    using TopLevelVoidElementDescriptor = pair<OldEbmlElementPtr, EbmlElements>;

    TopLevelVoidElementDescriptor m_void_before_tracks;
    TopLevelVoidElementDescriptor m_void_after_tracks;
};

