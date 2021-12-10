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