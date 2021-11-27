#pragma once
#include "Common.h"
#include "EbmlElement.h"

#include <string_view>

using std::string_view;

struct TrackEntry
{
    TrackEntry(BasicSharedPtr<EbmlElement>& track_element);

    TrackEntry(TrackEntry&& other) = default;

    void load_values();

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
    string language;
    bool is_forced;
    bool is_default;
};