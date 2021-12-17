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
    vector<TrackEntry*>& tracks,
    TrackEntry* default_track);

namespace DefaultTrackSetterHandlers
{
    bool case_1(vector<TrackEntry*>& tracks, TrackEntry* default_track);
    bool case_2(vector<TrackEntry*>& tracks, TrackEntry* default_track);
    bool case_3(vector<TrackEntry*>& tracks, TrackEntry* default_track);
    bool case_4(vector<TrackEntry*>& tracks, TrackEntry* default_track);
    bool case_5(vector<TrackEntry*>& tracks, TrackEntry* default_track);
    bool case_6(vector<TrackEntry*>& tracks, TrackEntry* default_track);
    bool case_7(vector<TrackEntry*>& tracks, TrackEntry* default_track);
    bool case_8(vector<TrackEntry*>& tracks, TrackEntry* default_track);
}

constexpr std::array<DefaultTrackSetterHandler, 8> DEAFULT_TRACK_SETTER_HANDLERS{
    DefaultTrackSetterHandlers::case_1,
    DefaultTrackSetterHandlers::case_2,
    DefaultTrackSetterHandlers::case_3,
    DefaultTrackSetterHandlers::case_4,
    DefaultTrackSetterHandlers::case_5,
    DefaultTrackSetterHandlers::case_6,
    DefaultTrackSetterHandlers::case_7,
    DefaultTrackSetterHandlers::case_8
};