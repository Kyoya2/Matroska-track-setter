#include "DefaultTrackSetterHandlers.h"

bool DefaultTrackSetterHandlers::case_1(vector<TrackEntry>& tracks, uint32_t default_track_index, vector<TrackEntry>&, uint32_t)
{
    TrackEntry& default_track = tracks[default_track_index];
    if (default_track.has_FlagForced())
    {
        DEBUG_PRINT_LINE("The current track set is eligible for case 1");

        default_track.set_FlagForced(true);
        return true;
    }
    return false;
}

bool DefaultTrackSetterHandlers::case_2(vector<TrackEntry>& tracks, uint32_t default_track_index, vector<TrackEntry>&, uint32_t)
{
    // If all tracks have FlagDefault
    if (std::all_of(tracks.cbegin(), tracks.cend(), [](const TrackEntry& track) { return track.has_FlagDefault(); }))
    {
        DEBUG_PRINT_LINE("The current track set is eligible for case 2");

        tracks[default_track_index].set_FlagDefault(true);
        return true;
    }

    return false;
}

bool DefaultTrackSetterHandlers::case_3(vector<TrackEntry>& tracks, uint32_t default_track_index, vector<TrackEntry>&, uint32_t)
{
    // Make sure that all non-default tracks have FlagDefault
    for (uint32_t i = 0; i < tracks.size(); ++i)
    {
        if ((i != default_track_index) && (!tracks[i].has_FlagDefault()))
            return false;
    }

    DEBUG_PRINT_LINE("The current track set is eligible for case 3");
    return true;
}

bool DefaultTrackSetterHandlers::case_4(vector<TrackEntry>& tracks, uint32_t default_track_index, vector<TrackEntry>&, uint32_t)
{
    TrackEntry& default_track = tracks[default_track_index];
    if (default_track.has_Language() && default_track.has_LanguageIETF())
    {
        DEBUG_PRINT_LINE("The current track set is eligible for case 4");

        default_track.language_element->overwrite_with_bool_element(FlagForced_ID, true);

        default_track.flag_forced_element = default_track.language_element;
        default_track.language_element = nullptr;
        default_track.is_forced = true;

        return true;
    }

    return false;
}

bool DefaultTrackSetterHandlers::case_5(vector<TrackEntry>& tracks, uint32_t default_track_index, vector<TrackEntry>& other_tracks, uint32_t untouchable_track_index)
{
    return false;
}

bool DefaultTrackSetterHandlers::case_6(vector<TrackEntry>& tracks, uint32_t default_track_index, vector<TrackEntry>& other_tracks, uint32_t untouchable_track_index)
{
    return false;
}

bool DefaultTrackSetterHandlers::case_7(vector<TrackEntry>& tracks, uint32_t default_track_index, vector<TrackEntry>& other_tracks, uint32_t untouchable_track_index)
{
    return false;
}

bool DefaultTrackSetterHandlers::case_8(vector<TrackEntry>& tracks, uint32_t default_track_index, vector<TrackEntry>& other_tracks, uint32_t untouchable_track_index)
{
    return false;
}

bool DefaultTrackSetterHandlers::case_9(vector<TrackEntry>& tracks, uint32_t default_track_index, vector<TrackEntry>& other_tracks, uint32_t untouchable_track_index)
{
    return false;
}