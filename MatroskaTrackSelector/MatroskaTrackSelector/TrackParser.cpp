#include "TrackParser.h"

TrackParser::TrackParser(std::iostream& stream)
{
    stream.seekg(0);
    auto segment_element = EbmlElement::s_construct_from_stream(stream);
    
    if (Segment_ID != segment_element->get_id().get_value())
    {
        throw UnexpectedElementException("Expected segment element");
    }

    auto current_top_level_element = segment_element->get_first_child();
    BasicSharedPtr<EbmlElement> last_void_element = nullptr;

    // Iterate over all top-level elements
    while (true)
    {
        switch (current_top_level_element->get_id().get_value())
        {
        case SeekHead_ID:
            if (m_tracks_seek_position.is_null())
                _load_tracks_seek_position_element(current_top_level_element);
            break;

        case Tracks_ID:
            // The last seen Void element is the closest Void element that appears before the Tracks element
            m_void_before_tracks = last_void_element;
            _load_tracks(current_top_level_element);
            break;

        case Void_ID:
            last_void_element = current_top_level_element;
            // If the tracks have already been loaded and the closes Void element that comes after the Tracks
            // element wasn't loaded. Set it to be the current Void element.
            if ((!m_audio_tracks.empty() || !m_subtitle_tracks.empty()) && m_void_after_tracks.is_null())
            {
                m_void_after_tracks = last_void_element;
            }
            break;
        }

        if (current_top_level_element->is_last())
            break;

        current_top_level_element = current_top_level_element->get_next_element();
    }
}

void TrackParser::_load_tracks_seek_position_element(BasicSharedPtr<EbmlElement>& seek_head_element)
{
    auto seek_elements = seek_head_element->get_identical_children_by_id(Seek_ID);

    // Iterate over all Seek elements untill we find the Seek element that points to the Tracks element
    for (BasicSharedPtr<EbmlElement>& current_seek_element : seek_elements)
    {
       unordered_map<EbmlElementIDType, BasicSharedPtr<EbmlElement>> seek_children{
            {SeekID_ID, nullptr},
            {SeekPosition_ID, nullptr}
       };

       current_seek_element->get_unique_children(seek_children);

       // If the current seek ID matches the ID of a "Tracks" element, save it's SeekPosition and return
       if (seek_children[SeekID_ID]->uint_value() == Tracks_ID)
       {
           m_tracks_seek_position = seek_children[SeekPosition_ID];
           return;
       }
    }
}

void TrackParser::_load_tracks(BasicSharedPtr<EbmlElement>& tracks_element)
{
    auto tracks = tracks_element->get_identical_children_by_id(TrackEntry_ID);

    for (BasicSharedPtr<EbmlElement>& track : tracks)
    {
        TrackEntry current_track_entry = track;
        
        switch (current_track_entry.track_type)
        {
        case TrackType::Audio:
            current_track_entry.load_values();
            m_audio_tracks.emplace_back(std::move(current_track_entry));
            break;

        case TrackType::Subtitle:
            current_track_entry.load_values();
            m_subtitle_tracks.emplace_back(std::move(current_track_entry));
            break;
        }
    }
}
