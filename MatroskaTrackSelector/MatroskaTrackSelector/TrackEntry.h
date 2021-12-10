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
#include "Common.h"
#include "EbmlElement.h"
#include "MatroskaLanguageTags.h"

#include <string_view>

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
    TrackType track_type;
    string track_name;
    string_view language;
    bool is_default;
    bool is_forced;
};

using Tracks = vector<TrackEntry>;

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
