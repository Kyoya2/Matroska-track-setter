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
    assert(track_element->get_id().get_value() == TrackEntry_ID);

    unordered_map<EbmlElementIDType, BasicSharedPtr<EbmlElement>> children{
        {Name_ID, nullptr},
        {Language_ID, nullptr},
        {LanguageBCP47_ID, nullptr},
        {FlagDefault_ID, nullptr},
        {FlagForced_ID, nullptr},
        {TrackType_ID, nullptr},
    };

    track_element->get_unique_children(children);

    // Save element pointers
    name_element = children[Name_ID];
    language_element = children[Language_ID];
    language_bcp47_element = children[LanguageBCP47_ID];
    flag_default_element = children[FlagDefault_ID];
    flag_forced_element = children[FlagForced_ID];

    // Load only the value of the track type
    type = static_cast<TrackType>(children[TrackType_ID]->get_uint_value());
}

void TrackEntry::load_values()
{
    if (!name_element.is_null())
        name = name_element->get_string_value();

    // Initilize the language tag with the default value
    string language_tag = "en";
    if (!language_bcp47_element.is_null())
        language_tag = language_bcp47_element->get_string_value();
    else if (!language_element.is_null())
        language_tag = language_element->get_string_value();
    language = MatroskaLanguageTags::get_tag_language(language_tag);
    
    if (!flag_default_element.is_null())
        is_default = flag_default_element->get_bool_value();

    if (!flag_forced_element.is_null())
        is_forced = flag_forced_element->get_bool_value();
}