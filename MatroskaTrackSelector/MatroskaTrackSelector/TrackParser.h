#pragma once
#include "Common.h"
#include "EbmlElement.h"
#include "TrackElement.h"

class TrackParser
{
public:
    explicit TrackParser(std::iostream& stream);

private:
    void _load_tracks_seek_position_element(BasicSharedPtr<EbmlElement>& seek_head_element);
    void _load_tracks(BasicSharedPtr<EbmlElement>& tracks_element);

private:
    BasicSharedPtr<EbmlElement> m_tracks_seek_position;
    vector<TrackEntry> m_subtitle_tracks;
    vector<TrackEntry> m_audio_tracks;

    // Theese refer to void elements that USUSALLY appear between top-level elements
    BasicSharedPtr<EbmlElement> m_void_before_tracks;
    BasicSharedPtr<EbmlElement> m_void_after_tracks;
};

