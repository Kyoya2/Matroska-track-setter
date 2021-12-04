#include "DefaultTrackSetterHandlers.h"

bool DefaultTrackSetterHandlers::case_1(Tracks& tracks, TrackEntry* default_track, Tracks&, const TrackEntry*)
{
    if (default_track->has_FlagForced())
    {
        DEBUG_PRINT_LINE("The current track set is eligible for case 1");

        default_track->set_FlagForced(true);
        return true;
    }
    return false;
}

bool DefaultTrackSetterHandlers::case_2(Tracks& tracks, TrackEntry* default_track, Tracks&, const TrackEntry*)
{
    // If all tracks have FlagDefault
    if (std::all_of(tracks.cbegin(), tracks.cend(), [](const TrackEntry& track) { return track.has_FlagDefault(); }))
    {
        DEBUG_PRINT_LINE("The current track set is eligible for case 2");

        default_track->set_FlagDefault(true);
        return true;
    }

    return false;
}

bool DefaultTrackSetterHandlers::case_3(Tracks& tracks, TrackEntry* default_track, Tracks&, const TrackEntry*)
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

bool DefaultTrackSetterHandlers::case_4(Tracks& tracks, TrackEntry* default_track, Tracks&, const TrackEntry*)
{
    if (default_track->has_Language() && default_track->has_LanguageIETF())
    {
        DEBUG_PRINT_LINE("The current track set is eligible for case 4");

        default_track->language_element->overwrite_with_bool_element(FlagForced_ID, true);

        default_track->flag_forced_element = default_track->language_element;
        default_track->language_element = nullptr;
        default_track->is_forced = true;

        return true;
    }

    return false;
}

bool DefaultTrackSetterHandlers::case_5(Tracks& tracks, TrackEntry* default_track, Tracks&, const TrackEntry*)
{
    if ((default_track->language == "English") &&
        (default_track->has_Language() || default_track->has_LanguageIETF()))
    {
        DEBUG_PRINT_LINE("The current track set is eligible for case 5");

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
    }
    return false;
}

bool DefaultTrackSetterHandlers::case_6(Tracks& tracks, TrackEntry* default_track, Tracks& other_tracks, const TrackEntry* untouchable_track)
{
    return false;
}

bool DefaultTrackSetterHandlers::case_7(Tracks& tracks, TrackEntry* default_track, Tracks& other_tracks, const TrackEntry* untouchable_track)
{
    return false;
}

bool DefaultTrackSetterHandlers::case_8(Tracks& tracks, TrackEntry* default_track, Tracks& other_tracks, const TrackEntry* untouchable_track)
{
    return false;
}

bool DefaultTrackSetterHandlers::case_9(Tracks& tracks, TrackEntry* default_track, Tracks& other_tracks, const TrackEntry* untouchable_track)
{
    return false;
}