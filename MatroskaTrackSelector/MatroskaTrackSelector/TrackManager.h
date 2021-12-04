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
    const Tracks& get_subtitle_tracks() const { return m_subtitle_tracks;  }
    const Tracks& get_audio_tracks() const { return m_audio_tracks;  }

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

