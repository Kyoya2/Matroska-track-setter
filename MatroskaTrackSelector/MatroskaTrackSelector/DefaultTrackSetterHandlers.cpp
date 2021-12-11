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
#include "DefaultTrackSetterHandlers.h"

// Define this to prevent the program from modifying files.
// Usefull for debugging
#define DONT_APPLY_TRACK_SELECTION

bool DefaultTrackSetterHandlers::case_1(Tracks& tracks, TrackEntry* default_track, Tracks&, const TrackEntry*, vector<TrackEntry*>&)
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

bool DefaultTrackSetterHandlers::case_2(Tracks& tracks, TrackEntry* default_track, Tracks&, const TrackEntry*, vector<TrackEntry*>&)
{
    // If all tracks have FlagDefault
    if (std::all_of(tracks.cbegin(), tracks.cend(), [](const TrackEntry& track) { return track.has_FlagDefault(); }))
    {
        DEBUG_PRINT_LINE("The current track set is eligible for case 2");

#ifndef DONT_APPLY_TRACK_SELECTION
        default_track->set_FlagDefault(true);
#endif
        return true;
    }

    return false;
}

bool DefaultTrackSetterHandlers::case_3(Tracks& tracks, TrackEntry* default_track, Tracks&, const TrackEntry*, vector<TrackEntry*>&)
{
    // Make sure that all non-default tracks have FlagDefault
    for (const TrackEntry& track : tracks)
    {
        if ((&track != default_track) && !track.has_FlagDefault())
        {
            return false;
        }
    }

    DEBUG_PRINT_LINE("The current track set is eligible for case 3");
    return true;
}

bool DefaultTrackSetterHandlers::case_4(Tracks& tracks, TrackEntry* default_track, Tracks&, const TrackEntry*, vector<TrackEntry*>&)
{
    if (default_track->has_Language() && default_track->has_LanguageIETF())
    {
        DEBUG_PRINT_LINE("The current track set is eligible for case 4");

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

bool DefaultTrackSetterHandlers::case_5(Tracks& tracks, TrackEntry* default_track, Tracks&, const TrackEntry*, vector<TrackEntry*>&)
{
    if ((default_track->language == "English") &&
        (default_track->has_Language() || default_track->has_LanguageIETF()))
    {
        DEBUG_PRINT_LINE("The current track set is eligible for case 5");

#ifndef DONT_APPLY_TRACK_SELECTION
#error
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

bool DefaultTrackSetterHandlers::case_6(Tracks& tracks, TrackEntry* default_track, Tracks& other_tracks, const TrackEntry* untouchable_track, vector<TrackEntry*>& intermediate_storage_container)
{
    // place both track sets in intermediate_storage_container
    for (TrackEntry& track : tracks)
    {
        intermediate_storage_container.push_back(&track);
    }
    for (TrackEntry& track : other_tracks)
    {
        intermediate_storage_container.push_back(&track);
    }

    // Sort the storage container by the distance of each track from the default track
    std::sort(
        intermediate_storage_container.begin(),
        intermediate_storage_container.end(),
        [default_track](TrackEntry* first, TrackEntry* second)
        {
            return default_track->track_element->get_distance_from(first->track_element) <
                   default_track->track_element->get_distance_from(second->track_element);
        });
#ifndef DONT_APPLY_TRACK_SELECTION

#endif
    return false;
}

bool DefaultTrackSetterHandlers::case_7(Tracks& tracks, TrackEntry* default_track, Tracks& other_tracks, const TrackEntry* untouchable_track, vector<TrackEntry*>& intermediate_storage_container)
{

#ifndef DONT_APPLY_TRACK_SELECTION

#endif
    return false;
}

bool DefaultTrackSetterHandlers::case_8(Tracks& tracks, TrackEntry* default_track, Tracks& other_tracks, const TrackEntry* untouchable_track, vector<TrackEntry*>& intermediate_storage_container)
{

#ifndef DONT_APPLY_TRACK_SELECTION

#endif
    return false;
}

bool DefaultTrackSetterHandlers::case_9(Tracks& tracks, TrackEntry* default_track, Tracks& other_tracks, const TrackEntry* untouchable_track, vector<TrackEntry*>& intermediate_storage_container)
{

#ifndef DONT_APPLY_TRACK_SELECTION

#endif
    return false;
}