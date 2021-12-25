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
#include <string_view>
#include <algorithm>
#include <cctype>

#include "Common.h"
#include "EbmlElement.h"
#include "MatroskaLanguageTags.h"

using std::string_view;

struct TrackEntry
{
public:
    // Load elements and track type but do not parse values
    TrackEntry(BasicSharedPtr<EbmlElement>& track_element);

    TrackEntry(const TrackEntry&) = delete;
    TrackEntry& operator=(const TrackEntry&) = delete;

    TrackEntry(TrackEntry&& other) noexcept = default;
    TrackEntry& operator=(TrackEntry&& other) noexcept = default;

public:
    void load_values();

    inline bool has_FlagDefault() const { return !flag_default_element.is_null(); }
    void set_FlagDefault(bool is_default);

    inline bool has_FlagForced() const { return !flag_forced_element.is_null(); }
    void set_FlagForced(bool is_forced);

    inline bool has_Language() const { return !language_element.is_null(); }
    inline bool has_LanguageIETF() const { return !language_ietf_element.is_null(); }

public:
    // Elements
    BasicSharedPtr<EbmlElement> track_element;
    BasicSharedPtr<EbmlElement> name_element;
    BasicSharedPtr<EbmlElement> language_element;
    BasicSharedPtr<EbmlElement> language_ietf_element;
    BasicSharedPtr<EbmlElement> flag_default_element;
    BasicSharedPtr<EbmlElement> flag_forced_element;

    // Element values
    TrackType type;
    string name;
    string_view language;
    bool is_default;
    bool is_forced;
};

using Tracks = vector<TrackEntry>;


using TrackEntryHash = size_t;
using TrackGroupHash = size_t;

class TrackEntryHasher
{
public:
    // Return a vector that contains hashes of the given tracks
    static vector<TrackEntryHash> s_get_track_hashes(const Tracks& tracks);

    // Converts a vactor of track hashes into a single hash
    static TrackGroupHash s_hash_track_hashes(const vector<TrackEntryHash>& track_hashes);

private:
    static TrackEntryHash _s_hash_track_entry(const TrackEntry& track);
};


inline void TrackEntry::set_FlagDefault(bool new_value)
{
    if (is_default == new_value)
        return;

    flag_default_element->change_bool_value(new_value);
    is_default = new_value;
}

inline void TrackEntry::set_FlagForced(bool new_value)
{
    if (is_forced == new_value)
        return;

    flag_forced_element->change_bool_value(new_value);
    is_forced = new_value;
}