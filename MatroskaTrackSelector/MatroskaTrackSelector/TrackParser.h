#pragma once
#include "Common.h"
#include "EbmlElement.h"
#include "TrackElement.h"

class TrackParser
{
public:
    TrackParser(std::iostream& stream);


private:
    BasicSharedPtr<EbmlElement> m_tracks_seek_position;
    vector<BasicSharedPtr<EbmlElement>> m_top_level_void_elements;
    vector<TrackElement> m_tracks;
};

