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
#include "DefaultTrackSetterHandlers.h"

// Define this to prevent the program from modifying files.
// Usefull for debugging
#define DONT_APPLY_TRACK_SELECTION

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

bool DefaultTrackSetterHandlers::case_1(vector<TrackEntry*>& tracks, TrackEntry* default_track)
{
    if (default_track->has_FlagForced())
    {
        DEBUG_PRINT_LINE("The current track set is eligible for case 1");

#ifndef DONT_APPLY_TRACK_SELECTION
        default_track->set_FlagForced(true);
#endif
        return true;
    }
    return false;
}

bool DefaultTrackSetterHandlers::case_2(vector<TrackEntry*>& tracks, TrackEntry* default_track)
{
    // If all tracks have FlagDefault
    if (std::all_of(tracks.cbegin(), tracks.cend(), [](const TrackEntry* track) { return track->has_FlagDefault(); }))
    {
        DEBUG_PRINT_LINE("The current track set is eligible for case 2");

#ifndef DONT_APPLY_TRACK_SELECTION
        if (default_track->has_FlagDefault())
            default_track->set_FlagDefault(true);
#endif
        return true;
    }

    return false;
}

bool DefaultTrackSetterHandlers::case_3(vector<TrackEntry*>& tracks, TrackEntry* default_track)
{
    if (default_track->has_Language() && default_track->has_LanguageIETF())
    {
        DEBUG_PRINT_LINE("The current track set is eligible for case 3");

#ifndef DONT_APPLY_TRACK_SELECTION
        default_track->language_element->overwrite_with_bool_element(FlagForced_ID, true);

        default_track->flag_forced_element = default_track->language_element;
        default_track->language_element = nullptr;
        default_track->is_forced = true;
#endif
        return true;
    }

    return false;
}

bool DefaultTrackSetterHandlers::case_4(vector<TrackEntry*>& tracks, TrackEntry* default_track)
{
    if ((default_track->language == "English") &&
        (default_track->has_Language() || default_track->has_LanguageIETF()))
    {
        DEBUG_PRINT_LINE("The current track set is eligible for case 4");

#ifndef DONT_APPLY_TRACK_SELECTION
        if (default_track->has_Language())
        {
            default_track->language_element->overwrite_with_bool_element(FlagForced_ID, true);
            default_track->flag_forced_element = default_track->language_element;
            default_track->language_element = nullptr;
        }
        else
        {
            default_track->language_ietf_element->overwrite_with_bool_element(FlagForced_ID, true);
            default_track->flag_forced_element = default_track->language_ietf_element;
            default_track->language_ietf_element = nullptr;
        }

        default_track->is_forced = true;
#endif
        return true;
    }
    return false;
}

bool DefaultTrackSetterHandlers::case_5(vector<TrackEntry*>& tracks, TrackEntry* default_track)
{
    if (!can_expand_to_contain_ff(default_track))
        return false;

    for (TrackEntry* track : tracks)
    {
        // The commented condition is unnecessary because the default track does not have a FF, otherwise,
        // It would have been eligable for an earlier case
        if (track->has_FlagForced() /* && track != default_track */ ) 
        {
            DEBUG_PRINT_LINE("The current track set is eligible for case 5");

            // do stuff
#ifndef DONT_APPLY_TRACK_SELECTION

#endif
            return true;
        }
    }

    return false;
}

bool DefaultTrackSetterHandlers::case_6(vector<TrackEntry*>& tracks, TrackEntry* default_track)
{

#ifndef DONT_APPLY_TRACK_SELECTION

#endif
    return false;
}

bool DefaultTrackSetterHandlers::case_7(vector<TrackEntry*>& tracks, TrackEntry* default_track)
{

#ifndef DONT_APPLY_TRACK_SELECTION

#endif
    return false;
}

bool DefaultTrackSetterHandlers::case_8(vector<TrackEntry*>& tracks, TrackEntry* default_track)
{

#ifndef DONT_APPLY_TRACK_SELECTION

#endif
    return false;
}