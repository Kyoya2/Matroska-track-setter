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
#pragma once

#include <fstream>
#include <regex>

#include "Common.h"
#include "TrackEntry.h"

enum class TrackPriorityClass
{
    // Must be sorted from the highest to lowest priority.
    // Priority description:
    //                       Excl. word | Incl. word | Matching lang
                         //  ----------------------------------------
    TopPriority = 0,     //  -          | +          | +
    NotIncluded,         //  -          | -          | +
    WrongLanguage,       //  -          | +          | -
    NotExcluded,         //  -          | -          | -
    ExplicitlyExcluded,  //  +          | ?          | ?
                        
    // Must be last
    NumberOfPriorities
};

class TrackPriorityDescriptor
{
public:
    TrackPriorityDescriptor() = default;
    TrackPriorityDescriptor(const TrackPriorityClass priority_class, int32_t score) : priority_class(priority_class), m_score(score) {}

    bool operator==(const TrackPriorityDescriptor& other) const
    {
        return (priority_class == other.priority_class) && (m_score == other.m_score);
    }
    bool operator!=(const TrackPriorityDescriptor& other) const
    {
        return !(*this == other);
    }

    bool operator<(const TrackPriorityDescriptor& other) const
    {
        if (priority_class != other.priority_class)
            return priority_class > other.priority_class;
        else
            return m_score < other.m_score;
    }

public:
    TrackPriorityClass priority_class;

private:
    // Allows comparing priority of different tracks in the same priority class.
    // larger score equals highet priority
    int32_t m_score;
};

class TrackPrioritizer;

using TrackPrioritizers = pair<TrackPrioritizer, TrackPrioritizer>; // (subtitle, audio)

class TrackPrioritizer
{
public:
    TrackPrioritizer(const TrackPrioritizer&) = delete;
    TrackPrioritizer& operator=(const TrackPrioritizer&) = delete;

    TrackPrioritizer(TrackPrioritizer&&) = default;

public:
    // Returns a pair of (subtitle, audio) prioritizers
    static TrackPrioritizers s_from_file(const string& rules_file_path);

public:
    TrackPriorityDescriptor get_track_priority(const string& track_name, const string_view& track_language) const;
    TrackEntry* get_track_with_highest_priority(Tracks& tracks) const;

PRIVATE:
    TrackPrioritizer() = default;

PRIVATE:
    string language;
    vector<std::regex> include_keywords;
    vector<std::regex> language_keywords;
    vector<std::regex> exclude_keywords;
};

