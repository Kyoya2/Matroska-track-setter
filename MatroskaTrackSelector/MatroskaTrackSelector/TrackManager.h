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

    void set_default_tracks(uint32_t subtitle_track_index, uint32_t audio_track_index);

PRIVATE:
    void _load_tracks_seek_position_element(BasicSharedPtr<EbmlElement>& seek_head_element);
    void _load_tracks(BasicSharedPtr<EbmlElement>& tracks_element);

    void _s_set_default_track(
        Tracks& tracks,         // Either subtitle tracks or audio tracks
        uint32_t default_track_index,       // The index of the track to set as the default amongst the tracks in 'tracks'
        Tracks& other_tracks,   // The track set that's not specified by 'tracks'. e.g. if track is subtitles then this is audio
        uint32_t untouchable_track_index);  // The index of the track amongst 'other_tracks' that shouldn't be modified

PRIVATE:
    BasicSharedPtr<EbmlElement> m_tracks_seek_position;
    Tracks m_subtitle_tracks;
    Tracks m_audio_tracks;

    // Theese refer to void elements that USUSALLY appear between top-level elements
    BasicSharedPtr<EbmlElement> m_void_before_tracks;
    BasicSharedPtr<EbmlElement> m_void_after_tracks;
};

