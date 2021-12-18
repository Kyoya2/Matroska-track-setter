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
#include "TrackEntry.h"

TrackEntry::TrackEntry(BasicSharedPtr<EbmlElement>& track_element) :
    track_element(track_element),
    // Initialize with default values
    is_default(true),
    is_forced(false)
{
    unordered_map<EbmlElementIDType, BasicSharedPtr<EbmlElement>> children{
        {Name_ID, nullptr},
        {Language_ID, nullptr},
        {LanguageIETF_ID, nullptr},
        {FlagDefault_ID, nullptr},
        {FlagForced_ID, nullptr},
        {TrackType_ID, nullptr},
    };

    track_element->get_unique_children(children);

    // Save element pointers
    name_element = children[Name_ID];
    language_element = children[Language_ID];
    language_ietf_element = children[LanguageIETF_ID];
    flag_default_element = children[FlagDefault_ID];
    flag_forced_element = children[FlagForced_ID];

    // Load only the value of the track type
    track_type = static_cast<TrackType>(children[TrackType_ID]->get_uint_value());
}

void TrackEntry::load_values()
{
    if (!name_element.is_null())
        track_name = name_element->get_string_value();

    // Initilize the language tag with the default value
    string language_tag = "en";
    if (!language_ietf_element.is_null())
        language_tag = language_ietf_element->get_string_value();
    else if (!language_element.is_null())
        language_tag = language_element->get_string_value();
    language = MatroskaLanguageTags::get_tag_language(language_tag);
    
    if (!flag_default_element.is_null())
        is_default = flag_default_element->get_bool_value();

    if (!flag_forced_element.is_null())
        is_forced = flag_forced_element->get_bool_value();
}

vector<size_t> TrackEntryHasher::s_get_track_hashes(const vector<const TrackEntry*>& tracks)
{
    vector<size_t> result(tracks.size());
    for (size_t i = 0; i < tracks.size(); ++i)
    {
        result[i] = _s_hash_track_entry(tracks[i]);
    }

    return result;
}

size_t TrackEntryHasher::s_hash_track_hashes(const vector<size_t>& track_hashes)
{
    size_t result = 0;
    for (size_t i = 0; i < track_hashes.size(); ++i)
    {
        result ^= track_hashes[i] * (i + 1);
    }

    return result;
}

size_t TrackEntryHasher::_s_hash_track_entry(const TrackEntry* track)
{
    static const std::hash<string> STRING_HASH;
    static const std::hash<string_view> STRING_VIEW_HASH;

    string lowercase_track_name = track->track_name;
    std::transform(
        lowercase_track_name.begin(),
        lowercase_track_name.end(),
        lowercase_track_name.begin(),
        [](char c) { return std::tolower(c); });

    return STRING_HASH(lowercase_track_name) ^ STRING_VIEW_HASH(track->language);
}
