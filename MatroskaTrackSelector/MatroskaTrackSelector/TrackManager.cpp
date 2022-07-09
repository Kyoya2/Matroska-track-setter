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
#include "TrackManager.h"

// Returns true if a track element can be expanded by 4 bytes to contain a new FlagForced element
// so that the elements' encoded size doesn't grow
static bool can_expand_to_contain_ff(const TrackEntry* track)
{
    static constexpr uint32_t FF_SIZE = 4;
    return EbmlElementLength(
        track->track_element->get_data_length().get_value() + FF_SIZE
    ).get_encoded_size() ==
        track->track_element->get_data_length().get_encoded_size();
}

static void add_track_components_to_vector(vector<BasicSharedPtr<EbmlElement>> components, TrackEntry* track)
{
    if (track->has_FlagDefault())
        components.push_back(track->flag_default_element);

    if (track->has_FlagForced())
        components.push_back(track->flag_forced_element);

    if (track->has_Language())
        components.push_back(track->language_element);

    if (track->has_LanguageIETF())
        components.push_back(track->language_ietf_element);

    if (track->name_element)
        components.push_back(track->name_element);

    components.push_back(track->track_element);
}

TrackManager::TrackManager(const string& file) : m_file_stream(file, std::ios_base::binary | std::ios_base::out | std::ios_base::in)
{
    m_file_stream.seekg(0);
    auto segment_element = EbmlElement::s_construct_from_stream(m_file_stream);
    
    if (Segment_ID != segment_element->get_id().get_value())
    {
        throw InvalidMatroskaFile();
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

void TrackManager::set_default_tracks(TrackEntry* subtitle_track, TrackEntry* audio_track)
{
    DEBUG_PRINT_LINE(endl << "Setting default subtitle track");
    _set_default_track(
        m_subtitle_tracks,
        const_cast<TrackEntry*>(subtitle_track),
        m_audio_tracks,
        audio_track);

    DEBUG_PRINT_LINE("Setting default audio track");
    _set_default_track(
        m_audio_tracks,
        const_cast<TrackEntry*>(audio_track),
        m_subtitle_tracks,
        subtitle_track);
}

void TrackManager::set_default_tracks(size_t subtitle_track_index, size_t audio_track_index)
{
    set_default_tracks(&m_subtitle_tracks[subtitle_track_index], &m_audio_tracks[audio_track_index]);
}

void TrackManager::_load_tracks(BasicSharedPtr<EbmlElement>& tracks_element)
{
    assert(tracks_element->get_id().get_value() == Tracks_ID);
    auto tracks = tracks_element->get_identical_children_by_id(TrackEntry_ID);

    DEBUG_PRINT_LINE("Loading tracks");
    for (BasicSharedPtr<EbmlElement>& track : tracks)
    {
        TrackEntry current_track_entry = track;
        
        switch (current_track_entry.type)
        {
        case TrackType::Audio:
            current_track_entry.load_values();
            DEBUG_PRINT_LINE("Audio track named '" << current_track_entry.name << "'");
            m_audio_tracks.emplace_back(std::move(current_track_entry));
            break;

        case TrackType::Subtitle:
            current_track_entry.load_values();
            DEBUG_PRINT_LINE("Subtitle track named '" << current_track_entry.name << "'");
            m_subtitle_tracks.emplace_back(std::move(current_track_entry));
            break;
        }
    }
}

void TrackManager::_set_default_track(
    Tracks& tracks,
    TrackEntry* default_track,
    Tracks& other_tracks,
    TrackEntry* untouchable_track)
{
    // Define this to prevent the program from modifying files.
    // Usefull for debugging
//#define DONT_APPLY_TRACK_SELECTION

    // Reset FlagForced and FlagDefault of all elements (except the default element)
    for (TrackEntry& track : tracks)
    {
        if (&track == default_track)
            continue;

#ifndef DONT_APPLY_TRACK_SELECTION
        if (track.has_FlagForced())
        {
            track.set_FlagForced(false);
        }

        if (track.has_FlagDefault())
        {
            track.set_FlagDefault(false);
        }
#endif
    }

    // Fill the working state with all tracks of the default track's type except the default track
    vector<TrackEntry*> working_state;
    for (TrackEntry& track : tracks)
    {
        if (&track != default_track)
            working_state.push_back(&track);
    }

    // From this point we try to find the best case for setting the default track
    bool eligible_case_found = true;

    // Case 1
    // If the current track has FlagForced
    if (default_track->has_FlagForced())
    {
        DEBUG_PRINT_LINE("The desired track has FlagForced, setting it to 1");
#ifndef DONT_APPLY_TRACK_SELECTION
        default_track->set_FlagForced(true);
#endif
    }
    // Case 2
    // If all other tracks of the same type have FlagDefault
    else if (std::all_of(working_state.cbegin(), working_state.cend(), [](const TrackEntry* track) { return track->has_FlagDefault(); }))
    {
        DEBUG_PRINT_LINE("All non-desired tracks have FlagDefault, set them to 0");

#ifndef DONT_APPLY_TRACK_SELECTION
        if (default_track->has_FlagDefault())
            default_track->set_FlagDefault(true);
#endif
    }
    // Case 3
    // If the default track has both Language and LanguageIETF
    else if (default_track->has_Language() && default_track->has_LanguageIETF())
    {
        DEBUG_PRINT_LINE("The desired track has both Language and LanguageIETF, overwriting Language with FlagForced");

#ifndef DONT_APPLY_TRACK_SELECTION
        default_track->language_element->overwrite_with_bool_element(FlagForced_ID, true);

        default_track->flag_forced_element = default_track->language_element;
        default_track->language_element = nullptr;
        default_track->is_forced = true;
#endif
    }
    // Case 4
    // If the track's language is explicitly set to English
    else if ((default_track->language == "English") &&
            (default_track->has_Language() || default_track->has_LanguageIETF()))
    {
        DEBUG_PRINT_LINE("The desired track's language is explicitly set to English");

#ifndef DONT_APPLY_TRACK_SELECTION
        if (default_track->has_Language())
        {
            DEBUG_PRINT_LINE("overwriting Language with FlagForced");
            default_track->language_element->overwrite_with_bool_element(FlagForced_ID, true);
            default_track->flag_forced_element = default_track->language_element;
            default_track->language_element = nullptr;
        }
        else
        {
            DEBUG_PRINT_LINE("overwriting LanguageIETF with FlagForced");
            default_track->language_ietf_element->overwrite_with_bool_element(FlagForced_ID, true);
            default_track->flag_forced_element = default_track->language_ietf_element;
            default_track->language_ietf_element = nullptr;
        }

        default_track->is_forced = true;
#endif
    }
    // Cases 5-7
    // If the default track can expand by sizeof(FlagForced) without changing the size of the encoded length of the track
    else if (can_expand_to_contain_ff(default_track))
    {
        DEBUG_PRINT_LINE("The desired track can expand by sizeof(FlagForced)");

        if (default_track->has_FlagDefault() &&
            std::count_if(working_state.cbegin(), working_state.cend(),
                [](const TrackEntry* track) {
                    return !track->has_FlagDefault();
                }
            ) == 1)
        {
            DEBUG_PRINT_LINE("There is only one track without FlagDefault and it's not the desired track, move FlagDefault from the desired track to the other track and set it to 0");
            TrackEntry* track_without_fd = nullptr;

            // Make a vector with ALL referenced elements in the "Tracks" segment, except the default
            // track and the track without the FD
            vector<BasicSharedPtr<EbmlElement>> elements_to_adjust;
            for (TrackEntry* track : working_state)
                if (track->has_FlagDefault())
                    add_track_components_to_vector(elements_to_adjust, track);
                else
                    track_without_fd = track;

#ifndef DONT_APPLY_TRACK_SELECTION
            // Perform the move
            default_track->flag_default_element->move_to(track_without_fd->track_element, elements_to_adjust);

            // Update the TrackEntry objects
            track_without_fd->flag_default_element = default_track->flag_default_element;
            default_track->flag_default_element = nullptr;

            // Set the new FlagDefault to false
            track_without_fd->flag_default_element->change_bool_value(false);
#endif
        }
        else
        {
            // Add the other tracks (excluding 'untouchable_track') to the working state and sort the tracks by their 
            // distance from the default track such that the closest tracks appear first
            for (TrackEntry& track : other_tracks)
                if (&track != untouchable_track)
                    working_state.push_back(&track);
            std::sort(
                working_state.begin(),
                working_state.end(),
                [default_track](TrackEntry* first, TrackEntry* second)
                {
                    return default_track->track_element->get_distance_from(first->track_element) <
                        default_track->track_element->get_distance_from(second->track_element);
                }
            );

            BasicSharedPtr<EbmlElement> element_to_be_moved;
            for (TrackEntry* track : working_state)
            {
                // Case 5
                // If another track has FlagForced
                if (track->has_FlagForced())
                {
                    DEBUG_PRINT_LINE("Moving FlagForced from track at " << track->track_element->get_offset() << " to the desired track");
                    element_to_be_moved = track->flag_forced_element;
                    break;
                }
                // Case 6
                // If another track has both Language and LanguageIETF
                else if (track->has_Language() && track->has_LanguageIETF())
                {
                    DEBUG_PRINT_LINE("Track " << track->track_element->get_offset() << " has both Language and LanguageIETF, moving Language to the desired track");
                    element_to_be_moved = track->language_element;
                    break;
                }
                // Case 7
                // If another track's language is explicitly set to English 
                else if (track->language == "English" && (track->has_Language() || track->has_LanguageIETF()))
                {
                    DEBUG_PRINT_LINE("The language of track " << track->track_element->get_offset() << " is explicitly set to English");
                    if (track->has_Language())
                    {
                        DEBUG_PRINT_LINE("Moving Language to the desired track");
                        element_to_be_moved = track->language_element;
                        break;
                    }
                    else if (track->has_LanguageIETF())
                    {
                        DEBUG_PRINT_LINE("Moving LanguageIETF to the desired track");
                        element_to_be_moved = track->language_ietf_element;
                        break;
                    }
                }
            }

            if (element_to_be_moved)
            {
                // Make a vector with ALL referenced elements in the "Tracks" segment, except the default
                // track and the track from which the element is going to be moved
                vector<BasicSharedPtr<EbmlElement>> elements_to_adjust;
                for (TrackEntry* track : working_state)
                    if (track->track_element != element_to_be_moved->get_parent())
                        add_track_components_to_vector(elements_to_adjust, track);

                // Find the TrackEntry from which the element is going to be moved and adjust
                // it to the state after the element is moved
                for (TrackEntry* track : working_state)
                {
                    if (track->track_element == element_to_be_moved->get_parent())
                    {
                        switch (element_to_be_moved->get_id().get_value())
                        {
                        case FlagForced_ID:
                            default_track->flag_forced_element = track->flag_forced_element;
                            track->flag_forced_element = nullptr;
                            break;

                        case Language_ID:
                            default_track->flag_forced_element = track->language_element;
                            track->language_element = nullptr;
                            break;

                        case LanguageIETF_ID:
                            default_track->flag_forced_element = track->language_ietf_element;
                            track->language_ietf_element = nullptr;
                            break;
                        }

                        break;
                    }
                }

#ifndef DONT_APPLY_TRACK_SELECTION
                // Move the selected element to the desired track and turn it into FlagForced with value 1
                element_to_be_moved->move_to(default_track->track_element, elements_to_adjust);
                if (FlagForced_ID == element_to_be_moved->get_id().get_value())
                    element_to_be_moved->change_bool_value(true);
                else
                    element_to_be_moved->overwrite_with_bool_element(FlagForced_ID, true);
#endif
            }
            else
                eligible_case_found = false;
        }
    }
    else
        eligible_case_found = false;

    // Case 8
    // If the track set wasn't eligible for any other case
    if (!eligible_case_found)
    {
        DEBUG_PRINT_LINE("The current track set is eligible for case 8");
        // TODO
    }
}
