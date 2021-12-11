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
#include "TrackManager.h"

TrackManager::TrackManager(std::iostream& stream)
{
    stream.seekg(0);
    auto segment_element = EbmlElement::s_construct_from_stream(stream);
    
    if (Segment_ID != segment_element->get_id().get_value())
    {
        throw UnexpectedElementException("Expected segment element");
    }

    auto current_top_level_element = segment_element->get_first_child();

    BasicSharedPtr<EbmlElement> last_void_element = nullptr;
    EbmlElementIDType previous_element_id = 0;

    // Iterate over all top-level elements
    while (true)
    {
        switch (current_top_level_element->get_id().get_value())
        {
        case SeekHead_ID:
            DEBUG_PRINT_LINE("Encountered a SeekHead element");
            if (m_tracks_seek_position.is_null())
                _load_tracks_seek_position_element(current_top_level_element);
            break;

        case Tracks_ID:
            DEBUG_PRINT_LINE("Encountered a Tracks element");
            // The last seen Void element is the closest Void element that appears before the Tracks element
            if (previous_element_id == Void_ID)
                m_void_before_tracks = last_void_element;
            _load_tracks(current_top_level_element);
            break;

        case Void_ID:
            DEBUG_PRINT_LINE("Encountered a Void element");
            last_void_element = current_top_level_element;
            // If the tracks have already been loaded and the closes Void element that comes after the Tracks
            // element wasn't loaded. Set it to be the current Void element.
            if ((previous_element_id == Tracks_ID) && m_void_after_tracks.is_null())
            {
                m_void_after_tracks = last_void_element;
            }
            break;
        }

        previous_element_id = current_top_level_element->get_id().get_value();

        if (current_top_level_element->is_last())
            break;

        current_top_level_element = current_top_level_element->get_next_element();
    }
}

void TrackManager::_load_tracks_seek_position_element(BasicSharedPtr<EbmlElement>& seek_head_element)
{
    DEBUG_PRINT_LINE("Searching for a 'Seek' element with a SeekID of 'Tracks' element");
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
       if (seek_children[SeekID_ID]->get_uint_value() == Tracks_ID)
       {
           DEBUG_PRINT_LINE("Found Tracks SeekID");
           m_tracks_seek_position = seek_children[SeekPosition_ID];
           return;
       }
    }
}

void TrackManager::set_default_tracks(TrackEntry* subtitle_track_index, TrackEntry* audio_track_index)
{
    DEBUG_PRINT_LINE(endl << "Setting default subtitle track");
    _s_set_default_track(m_subtitle_tracks, subtitle_track_index, m_audio_tracks, audio_track_index);
    DEBUG_PRINT_LINE("Setting default audio track");
    _s_set_default_track(m_audio_tracks, audio_track_index, m_subtitle_tracks, subtitle_track_index);
}

void TrackManager::_load_tracks(BasicSharedPtr<EbmlElement>& tracks_element)
{
    DEBUG_PRINT_LINE("Loading tracks");
    auto tracks = tracks_element->get_identical_children_by_id(TrackEntry_ID);

    for (BasicSharedPtr<EbmlElement>& track : tracks)
    {
        TrackEntry current_track_entry = track;
        
        switch (current_track_entry.track_type)
        {
        case TrackType::Audio:
            current_track_entry.load_values();
            DEBUG_PRINT_LINE("Audio track named '" << current_track_entry.track_name << "'");
            m_audio_tracks.emplace_back(std::move(current_track_entry));
            break;

        case TrackType::Subtitle:
            current_track_entry.load_values();
            DEBUG_PRINT_LINE("Subtitle track named '" << current_track_entry.track_name << "'");
            m_subtitle_tracks.emplace_back(std::move(current_track_entry));
            break;
        }
    }
}

void TrackManager::_s_set_default_track(
    Tracks& tracks,
    TrackEntry* default_track,
    Tracks& other_tracks,
    TrackEntry* untouchable_track)
{
    // Set FlagForced and FlagDefault of all elements (except the default element) to false
    for (TrackEntry& track : tracks)
    {
        if (&track == default_track)
            continue;

        if (track.has_FlagForced())
        {
            track.set_FlagForced(false);
        }

        if (track.has_FlagDefault())
        {
            track.set_FlagDefault(false);
        }
    }

    vector<TrackEntry*> working_state;
    for (TrackEntry& track : tracks)
    {
        if (&track != default_track)
            working_state.push_back(&track);
    }

    bool success = false;
    for (size_t i = 0; i < DEAFULT_TRACK_SETTER_HANDLERS.size(); ++i)
    {
        if (5 == i)
        {
            for (TrackEntry& track : other_tracks)
            {
                if (&track != untouchable_track)
                    working_state.push_back(&track);
            }

            // Sort the tracks by their distance from the default track
            std::sort(
                working_state.begin(),
                working_state.end(),
                [default_track](TrackEntry* first, TrackEntry* second)
                {
                    return default_track->track_element->get_distance_from(first->track_element) <
                        default_track->track_element->get_distance_from(second->track_element);
                });
        }

        if (DEAFULT_TRACK_SETTER_HANDLERS[i](working_state, default_track))
        {
            success = true;
            break;
        }
    }

    if (!success)
    {
        throw FittingHandlerNotFound();
    }
}
