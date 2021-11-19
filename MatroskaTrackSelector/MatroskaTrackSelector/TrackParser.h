#pragma once
#include "Common.h"
#include "EbmlElement.h"
#include "TrackElement.h"

class TrackParser
{
public:
    explicit TrackParser(BasicSharedPtr<EbmlElement>& tracks_element);


private:
    BasicSharedPtr<EbmlElement> m_tracks_seek_position;
    vector<BasicSharedPtr<EbmlElement>> m_top_level_void_elements;
    vector<TrackElement> m_subtitle_tracks;
    vector<TrackElement> m_audio_tracks;
};

