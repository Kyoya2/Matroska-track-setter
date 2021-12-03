#pragma once
#include "Common.h"
#include "EbmlElement.h"
#include "MatroskaLanguageTags.h"

#include <string_view>

using std::string_view;

struct TrackEntry
{
    // Load elements and track type but do not parse values
    TrackEntry(BasicSharedPtr<EbmlElement>& track_element);

    TrackEntry(TrackEntry&& other) = default;

    void load_values();

    inline bool has_flag_default() const { return flag_default_element.is_null(); }
    void set_default(bool is_default);

    inline bool has_flag_forced() const { return flag_forced_element.is_null(); }
    void set_forced(bool is_forced);

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

inline void TrackEntry::set_default(bool new_value)
{
    if (is_default == new_value)
        return;

    flag_default_element->change_bool_value(new_value);
    is_default = new_value;
}

inline void TrackEntry::set_forced(bool new_value)
{
    if (is_forced == new_value)
        return;

    flag_forced_element->change_bool_value(new_value);
    is_forced = new_value;
}
