#include "MinTrackEntry.h"

string MinTrackEntry::get_colored_name() const
{
    using namespace ConsoleAttributes;
    static const std::array<string, static_cast<size_t>(TrackPriorityDescriptorClass::NumberOfPriorities)> priority_colors = {
        /* 0 */ LightGreenFG,
        /* 1 */ LightCyanFG,
        /* 2 */ LightYellowFG,
        /* 3 */ LightMagentaFG,
        /* 4 */ LightRedFG
    };

    string full_name = name.empty() ? ("Unnamed track " + std::to_string(unnamed_track_number)) : name;
    return priority_colors[static_cast<size_t>(m_priority_descriptor.priority_class)] + full_name + WhiteFG;
}

bool MinTrackEntry::operator<(const MinTrackEntry& other) const
{
    // Compare priorities
    if (m_priority_descriptor != other.m_priority_descriptor)
        // I want higher priorities to be at the start of the list so I reverse the comparison sign
        return other.m_priority_descriptor < m_priority_descriptor;

    // Compare name sizes
    if (name.size() != other.name.size())
        return name.size() < other.name.size();

    // Compare names case-insensitively
    for (size_t i = 0; i < name.size(); ++i)
    {
        int this_lower = std::tolower(name[i]);
        int other_lower = std::tolower(other.name[i]);

        if (this_lower != other_lower)
            return this_lower < other_lower;
    }

    // Compare languages
    int lang_strcmp = std::strcmp(language.data(), other.language.data());
    if (0 != lang_strcmp)
        return lang_strcmp < 0;

    // Compare unnamed indices (if tracks are unnamed)
    if (name.empty())
        return unnamed_track_number < other.unnamed_track_number;
    else
        // Entries are equal
        return false;
}
