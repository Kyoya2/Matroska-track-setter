#pragma once
#include "Common.h"
#include "EbmlElement.h"

enum class TrackLanguage
{
    Uninitialized = 0,
    English,
    Japanese,
    Other
};

class TrackElement
{
    explicit TrackElement(BasicSharedPtr<EbmlElement>& track_element);

private:
    // Elements
    BasicSharedPtr<EbmlElement> m_name_element;
    BasicSharedPtr<EbmlElement> m_language_element;
    BasicSharedPtr<EbmlElement> m_language_ietf_element;
    BasicSharedPtr<EbmlElement> m_flag_forced_element;
    BasicSharedPtr<EbmlElement> m_flag_default_element;

    // Element values
    TrackType m_track_type;
    string m_track_name;
    uint64_t m_track_number;
    TrackLanguage m_language;
    bool m_forced;
    bool m_default;
};