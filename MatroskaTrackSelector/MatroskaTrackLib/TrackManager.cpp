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
#include "TrackManager.h"

 // Returns true if a track element can be expanded by the given amount of bytes such that
// the element's encoded size doesn't grow
static bool can_track_expand_without_size_overflow(const TrackEntry* track, size_t expansion_size)
{
    return EbmlElementLength(
        track->track_element->get_data_length().get_value() + expansion_size
    ).get_encoded_size() ==
        track->track_element->get_data_length().get_encoded_size();
}

static void add_track_components_to_vector(EbmlElements components, TrackEntry* track)
{
    if (track->has_FlagDefault())
        components.push_back(track->flag_default_element);

    if (track->has_FlagForced())
        components.push_back(track->flag_forced_element);

    if (track->has_Language())
        components.push_back(track->language_element);

    if (track->has_LanguageBCP47())
        components.push_back(track->language_bcp47_element);

    if (track->name_element)
        components.push_back(track->name_element);

    components.push_back(track->track_element);
}

TrackManager::TrackManager(const string& file) : m_file_stream(file, std::ios_base::binary | std::ios_base::out | std::ios_base::in)
{
    m_file_stream.seekg(0);
    auto segment_element = OldEbmlElement::s_construct_from_stream(m_file_stream);

    if (Segment_ID != segment_element->get_id())
    {
        throw InvalidMatroskaFile();
    }

    auto current_top_level_element = segment_element->get_first_child();

    // Iterate over all top-level elements
    while (current_top_level_element)
    {
        switch (current_top_level_element->get_id())
        {
        case Tracks_ID:
            DEBUG_PRINT_LINE("Encountered a Tracks element");
            _load_tracks(current_top_level_element);
            break;

        case Void_ID:
            DEBUG_PRINT_LINE("Encountered a Void element");
            // Need a Void element to be able to contain at least 2 FFs:
            // 2+4+4=10 where 2 is the minimal size of Void header and 4 is size of FF
            if (current_top_level_element->get_total_size() < 10)
                break;

            if (_are_tracks_loaded())
                m_void_after_tracks.first = current_top_level_element;
            else
            {
                m_void_before_tracks.first = current_top_level_element;

                // Clear the top-level elements before the previous Void element, if there were any
                m_void_before_tracks.second.clear();
            }
            break;

        case SeekHead_ID:
            // TODO: handle the case where there are multiple SeekHead elements and
            // one of them is shifted due to last case, which means that some "Seek"
            // entries under that entry may to be updated (the ones that were not shifted along
            // with the parent SeekHead)
            DEBUG_PRINT_LINE("Encountered a SeekHead element");
            _load_seek_entries(current_top_level_element);
            __fallthrough;

        default:
            if (_are_tracks_loaded())
                m_void_after_tracks.second.push_back(current_top_level_element);
            else if (m_void_before_tracks.first)
                m_void_before_tracks.second.push_back(current_top_level_element);
            break;
        }

        if (m_void_after_tracks.first)
            break;

        current_top_level_element = current_top_level_element->get_next_element();
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

void TrackManager::_load_tracks(OldEbmlElementPtr& tracks_element)
{
    assert(tracks_element->get_id() == Tracks_ID);
    auto tracks = tracks_element->get_identical_children_by_id(TrackEntry_ID);

    DEBUG_PRINT_LINE("Loading tracks");
    for (OldEbmlElementPtr& track : tracks)
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

void TrackManager::_load_seek_entries(OldEbmlElementPtr& seek_head_element)
{
    assert(seek_head_element->get_id() == SeekHead_ID);
    auto seek_elements = seek_head_element->get_identical_children_by_id(Seek_ID);

    for (auto& seek_element : seek_elements)
        m_seek_entries.emplace_back(seek_element);
}

void TrackManager::_set_default_track(
    Tracks& tracks,
    TrackEntry* default_track,
    Tracks& other_tracks,
    TrackEntry* untouchable_track)
{
    // TODO: according to the EbmlSchema for Matroska, the Tracks element is recurring, which 
    // means that any changes made here must be also made for all other Tracks elements is the
    // current file
    static constexpr uint32_t FD_SIZE = 3;
    static constexpr uint32_t FF_SIZE = 4;
    // Define this to prevent the program from modifying files.
    // Usefull for debugging
//#define DONT_APPLY_TRACK_SELECTION

    // Reset FlagForced and FlagDefault of all elements (except the default element)
    // Fill the working state with all tracks of the default track's type except the default track
    vector<TrackEntry*> working_state;
    for (TrackEntry& track : tracks)
    {
        if (&track == default_track)
            continue;

        working_state.push_back(&track);

#ifndef DONT_APPLY_TRACK_SELECTION
        // Those actions are relevant to any case we chose
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

    // Set FlagDefault of the default track (if exists)
#ifndef DONT_APPLY_TRACK_SELECTION
    if (default_track->has_FlagDefault())
        default_track->set_FlagDefault(true);
#endif

    // From this point we try to find the best case for setting the default track


    // If the current track has FlagForced, we set it.
#pragma region Case_1
    if (default_track->has_FlagForced())
    {
        DEBUG_PRINT_LINE("The desired track has FlagForced, setting it to 1");
#ifndef DONT_APPLY_TRACK_SELECTION
        default_track->set_FlagForced(true);
#endif
        goto found_eligible_case;
    }
#pragma endregion

    // If all other tracks of the same type have FlagDefault
#pragma region Case_2
    if (std::all_of(working_state.cbegin(), working_state.cend(), [](const TrackEntry* track) { return track->has_FlagDefault(); }))
    {
        DEBUG_PRINT_LINE("All non-desired tracks have FlagDefault, set them to 0");
        // All of the stuff has already been done at the start of the function
        goto found_eligible_case;
    }
#pragma endregion

    // If the default track has both Language and LanguageBCP47, we override LanguageBCP47 with FlagForced
#pragma region Case_3
    if (default_track->has_Language() && default_track->has_LanguageBCP47())
    {
        DEBUG_PRINT_LINE("The desired track has both Language and LanguageBCP47, overwriting Language with FlagForced");

#ifndef DONT_APPLY_TRACK_SELECTION
        default_track->language_bcp47_element->overwrite_with_bool_element(FlagForced_ID, true);

        default_track->flag_forced_element = default_track->language_bcp47_element;
        default_track->language_bcp47_element = nullptr;
        default_track->is_forced = true;
#endif
        goto found_eligible_case;
    }
#pragma endregion

    // If the track's language is explicitly set to English, override the
    // present language-indicating element with FlagForced
#pragma region Case_4
    if ((default_track->language == "English") &&
        (default_track->has_Language() || default_track->has_LanguageBCP47()))
    {
        DEBUG_PRINT_LINE("The desired track's language is explicitly set to English");

        OldEbmlElementPtr& language_indicator = (default_track->has_Language() ?
                                                default_track->language_element :
                                                default_track->language_bcp47_element);

#ifndef DONT_APPLY_TRACK_SELECTION
        language_indicator->overwrite_with_bool_element(FlagForced_ID, true);
        default_track->flag_forced_element = language_indicator;
        language_indicator = nullptr;

        default_track->is_forced = true;
#endif
        goto found_eligible_case;
    }
#pragma endregion

    // There is only one track without FlagDefault and it's not the desired track,
    // move FlagDefault from the desired track to the other track and set it to 0
#pragma region Case_5
    if (can_track_expand_without_size_overflow(default_track, FD_SIZE) &&
        default_track->has_FlagDefault())
    {
        TrackEntry* track_without_fd = nullptr;

        // Make a vector with ALL referenced elements in the "Tracks" segment, except the default
        // track and the track without the FD
        EbmlElements elements_to_adjust;
        for (TrackEntry* track : working_state)
        {
            if (track->has_FlagDefault())
                add_track_components_to_vector(elements_to_adjust, track);
            // Here we check that there's only one track without FD, otherwise we keep
            // searching for another eligible case
            else if (nullptr != track_without_fd)
                track_without_fd = track;
            else
                goto case_5_end;
        }

        DEBUG_PRINT_LINE("There is only one track without FlagDefault and it's not the desired track, move FlagDefault from the desired track to the other track and set it to 0");

#ifndef DONT_APPLY_TRACK_SELECTION
        // Perform the move
        default_track->flag_default_element->move_to(track_without_fd->track_element, elements_to_adjust);

        // Update the TrackEntry objects
        track_without_fd->flag_default_element = default_track->flag_default_element;
        default_track->flag_default_element = nullptr;

        // Set the new FlagDefault to false
        track_without_fd->flag_default_element->update_bool_value(false);
#endif
        goto found_eligible_case;
    }
case_5_end:
#pragma endregion

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

    // If the default track can expand by sizeof(FlagForced) without changing the size
    // of the encoded length of the track
#pragma region Cases_6_8
    if (can_track_expand_without_size_overflow(default_track, FF_SIZE))
    {
        DEBUG_PRINT_LINE("The desired track can expand by sizeof(FlagForced)");

        OldEbmlElementPtr element_to_be_moved;
        for (TrackEntry* track : working_state)
        {
            // If another track has FlagForced
#pragma region Case_6
            if (track->has_FlagForced())
            {
                DEBUG_PRINT_LINE("Moving FlagForced from track at " << track->track_element->get_offset() << " to the desired track");
                element_to_be_moved = track->flag_forced_element;
                break;
            }
#pragma endregion

            // If another track has both Language and LanguageBCP47
#pragma region Case_7
            else if (track->has_Language() && track->has_LanguageBCP47())
            {
                DEBUG_PRINT_LINE("Track " << track->track_element->get_offset() << " has both Language and LanguageBCP47, moving Language to the desired track");
                element_to_be_moved = track->language_element;
                break;
            }
#pragma endregion

            // If another track's language is explicitly set to English 
#pragma region Case_8
            else if (track->language == "English" && 
                    (track->has_Language() || track->has_LanguageBCP47()))
            {
                DEBUG_PRINT_LINE("The language of track " << track->track_element->get_offset() << " is explicitly set to English");
                if (track->has_Language())
                {
                    DEBUG_PRINT_LINE("Moving Language to the desired track");
                    element_to_be_moved = track->language_element;
                    break;
                }
                else
                {
                    DEBUG_PRINT_LINE("Moving LanguageBCP47 to the desired track");
                    element_to_be_moved = track->language_bcp47_element;
                    break;
                }
            }
#pragma endregion
        }

        if (element_to_be_moved)
        {
            // Make a vector with ALL referenced elements in the "Tracks" segment, except the default
            // track and the track from which the element is going to be moved
            EbmlElements elements_to_adjust;
            for (TrackEntry* track : working_state)
                if (track->track_element != element_to_be_moved->get_parent())
                    add_track_components_to_vector(elements_to_adjust, track);
            add_track_components_to_vector(elements_to_adjust, untouchable_track);

            // Find the TrackEntry from which the element is going to be moved and adjust
            // it to the state after the element is moved
            for (TrackEntry* track : working_state)
            {
                if (track->track_element != element_to_be_moved->get_parent())
                    continue;

                switch (element_to_be_moved->get_id())
                {
                case FlagForced_ID:
                    default_track->flag_forced_element = track->flag_forced_element;
                    track->flag_forced_element = nullptr;
                    break;

                case Language_ID:
                    default_track->flag_forced_element = track->language_element;
                    track->language_element = nullptr;
                    break;

                case LanguageBCP47_ID:
                    default_track->flag_forced_element = track->language_bcp47_element;
                    track->language_bcp47_element = nullptr;
                    break;
                }

                break;
            }

#ifndef DONT_APPLY_TRACK_SELECTION
            // Move the selected element to the desired track and turn it into FF with value 1
            if (FlagForced_ID == element_to_be_moved->get_id())
                element_to_be_moved->update_bool_value(true);
            else
                element_to_be_moved->overwrite_with_bool_element(FlagForced_ID, true);

            element_to_be_moved->move_to(default_track->track_element, elements_to_adjust);
#endif      
            goto found_eligible_case;
        }
        else
            goto cases_6_8_end;
    }
cases_6_8_end:
#pragma endregion

    // Case 8
    // If the track set wasn't eligible for any other case
found_eligible_case:
    1;
}
