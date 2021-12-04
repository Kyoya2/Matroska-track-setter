#pragma once

#include <algorithm>

#include "Common.h"
#include "EbmlElement.h"
#include "TrackEntry.h"

// See TrackManager::_s_set_default_track for signature documentation
// Return value is true if the conditions for the case have been satisfied and the track has been set as the default
using DefaultTrackSetterHandler = bool(*)(
    Tracks& tracks,
    TrackEntry* default_track,
    Tracks& other_tracks,
    const TrackEntry* untouchable_track);

namespace DefaultTrackSetterHandlers
{
    bool case_1(Tracks& tracks, TrackEntry* default_track, Tracks& other_tracks, const TrackEntry* untouchable_track);
    bool case_2(Tracks& tracks, TrackEntry* default_track, Tracks& other_tracks, const TrackEntry* untouchable_track);
    bool case_3(Tracks& tracks, TrackEntry* default_track, Tracks& other_tracks, const TrackEntry* untouchable_track);
    bool case_4(Tracks& tracks, TrackEntry* default_track, Tracks& other_tracks, const TrackEntry* untouchable_track);
    bool case_5(Tracks& tracks, TrackEntry* default_track, Tracks& other_tracks, const TrackEntry* untouchable_track);
    bool case_6(Tracks& tracks, TrackEntry* default_track, Tracks& other_tracks, const TrackEntry* untouchable_track);
    bool case_7(Tracks& tracks, TrackEntry* default_track, Tracks& other_tracks, const TrackEntry* untouchable_track);
    bool case_8(Tracks& tracks, TrackEntry* default_track, Tracks& other_tracks, const TrackEntry* untouchable_track);
    bool case_9(Tracks& tracks, TrackEntry* default_track, Tracks& other_tracks, const TrackEntry* untouchable_track);
}

constexpr std::array<DefaultTrackSetterHandler, 9> DEAFULT_TRACK_SETTER_HANDLERS{
    DefaultTrackSetterHandlers::case_1,
    DefaultTrackSetterHandlers::case_2,
    DefaultTrackSetterHandlers::case_3,
    DefaultTrackSetterHandlers::case_4,
    DefaultTrackSetterHandlers::case_5,
    DefaultTrackSetterHandlers::case_6,
    DefaultTrackSetterHandlers::case_7,
    DefaultTrackSetterHandlers::case_8,
    DefaultTrackSetterHandlers::case_9
};