#pragma once

#include <algorithm>

#include "Common.h"
#include "EbmlElement.h"
#include "TrackElement.h"

// See TrackManager::_s_set_default_track for signature documentation
// Return value is true if the conditions for the case have been satisfied and the track has been set as the default
using DefaultTrackSetterHandler = bool(*)(
    vector<TrackEntry>& tracks,
    uint32_t default_track_index,
    vector<TrackEntry>& other_tracks,
    uint32_t untouchable_track_index);

namespace DefaultTrackSetterHandlers
{
    bool case_1(vector<TrackEntry>& tracks, uint32_t default_track_index, vector<TrackEntry>& other_tracks, uint32_t untouchable_track_index);
    bool case_2(vector<TrackEntry>& tracks, uint32_t default_track_index, vector<TrackEntry>& other_tracks, uint32_t untouchable_track_index);
    bool case_3(vector<TrackEntry>& tracks, uint32_t default_track_index, vector<TrackEntry>& other_tracks, uint32_t untouchable_track_index);
    bool case_4(vector<TrackEntry>& tracks, uint32_t default_track_index, vector<TrackEntry>& other_tracks, uint32_t untouchable_track_index);
    bool case_5(vector<TrackEntry>& tracks, uint32_t default_track_index, vector<TrackEntry>& other_tracks, uint32_t untouchable_track_index);
    bool case_6(vector<TrackEntry>& tracks, uint32_t default_track_index, vector<TrackEntry>& other_tracks, uint32_t untouchable_track_index);
    bool case_7(vector<TrackEntry>& tracks, uint32_t default_track_index, vector<TrackEntry>& other_tracks, uint32_t untouchable_track_index);
    bool case_8(vector<TrackEntry>& tracks, uint32_t default_track_index, vector<TrackEntry>& other_tracks, uint32_t untouchable_track_index);
    bool case_9(vector<TrackEntry>& tracks, uint32_t default_track_index, vector<TrackEntry>& other_tracks, uint32_t untouchable_track_index);
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