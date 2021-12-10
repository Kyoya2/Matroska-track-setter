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
#pragma once

#include <algorithm>

#include "Common.h"
#include "EbmlElement.h"
#include "TrackEntry.h"

// Return value is true if the conditions for the case have been satisfied and the track has been set as the default
// 
// intermediate_storage_container is basically a container that's shared between all handlers and is intended for storing
// stuff that multiple handlers cant use. In this case, this container will be empty until case 5. Then case 6 will insert
// both track sets into this container and sort them by their distance from default_track. This will allow the rest of the
// case handlers to use the sorted container instead of each handler sorting it each time
//
// See TrackManager::_s_set_default_track for the signature documentation
using DefaultTrackSetterHandler = bool(*)(
    Tracks& tracks,
    TrackEntry* default_track,
    Tracks& other_tracks,
    const TrackEntry* untouchable_track,
    Tracks& intermediate_storage_container);

namespace DefaultTrackSetterHandlers
{
    bool case_1(Tracks& tracks, TrackEntry* default_track, Tracks& other_tracks, const TrackEntry* untouchable_track, Tracks& intermediate_storage_container);
    bool case_2(Tracks& tracks, TrackEntry* default_track, Tracks& other_tracks, const TrackEntry* untouchable_track, Tracks& intermediate_storage_container);
    bool case_3(Tracks& tracks, TrackEntry* default_track, Tracks& other_tracks, const TrackEntry* untouchable_track, Tracks& intermediate_storage_container);
    bool case_4(Tracks& tracks, TrackEntry* default_track, Tracks& other_tracks, const TrackEntry* untouchable_track, Tracks& intermediate_storage_container);
    bool case_5(Tracks& tracks, TrackEntry* default_track, Tracks& other_tracks, const TrackEntry* untouchable_track, Tracks& intermediate_storage_container);
    bool case_6(Tracks& tracks, TrackEntry* default_track, Tracks& other_tracks, const TrackEntry* untouchable_track, Tracks& intermediate_storage_container);
    bool case_7(Tracks& tracks, TrackEntry* default_track, Tracks& other_tracks, const TrackEntry* untouchable_track, Tracks& intermediate_storage_container);
    bool case_8(Tracks& tracks, TrackEntry* default_track, Tracks& other_tracks, const TrackEntry* untouchable_track, Tracks& intermediate_storage_container);
    bool case_9(Tracks& tracks, TrackEntry* default_track, Tracks& other_tracks, const TrackEntry* untouchable_track, Tracks& intermediate_storage_container);
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