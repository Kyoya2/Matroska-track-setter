#include "TrackElement.h"

TrackEntry::TrackEntry(BasicSharedPtr<EbmlElement>& track_element) :
    track_element(track_element)
{
    unordered_map<EbmlElementIDType, BasicSharedPtr<EbmlElement>> children{
            {GET_ID(Name), nullptr},
            {GET_ID(Language), nullptr},
            {GET_ID(LanguageIETF), nullptr},
            {GET_ID(FlagDefault), nullptr},
            {GET_ID(FlagForced), nullptr},
            {GET_ID(TrackType), nullptr},
    };

    track_element->get_unique_children(children);

    // Save element pointers
    name_element = children[GET_ID(Name)];
    language_element = children[GET_ID(Language)];
    language_ietf_element = children[GET_ID(LanguageIETF)];
    flag_default_element = children[GET_ID(FlagDefault)];
    flag_forced_element = children[GET_ID(FlagForced)];

    // Load only the value of the track type
    track_type = static_cast<TrackType>(children[GET_ID(TrackType)]->uint_value());
}

void TrackEntry::load_values()
{
    if (!name_element.is_null())
        track_name = name_element->string_value();

    if (!language_ietf_element.is_null())
        language = language_ietf_element->string_value();
    else if (!language_element.is_null())
        language = language_element->string_value();

    if (!flag_default_element.is_null())
        is_default = flag_default_element->bool_value();

    if (!flag_forced_element.is_null())
        is_forced = flag_forced_element->bool_value();
}
