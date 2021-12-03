#include "TrackElement.h"

TrackEntry::TrackEntry(BasicSharedPtr<EbmlElement>& track_element) :
    track_element(track_element),
    // Initialize with default values
    language("English"),
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

    if (!language_ietf_element.is_null())
        language = language_ietf_element->get_string_value();
    else if (!language_element.is_null())
        language = language_element->get_string_value();

    if (!flag_default_element.is_null())
        is_default = flag_default_element->get_bool_value();

    if (!flag_forced_element.is_null())
        is_forced = flag_forced_element->get_bool_value();
}
