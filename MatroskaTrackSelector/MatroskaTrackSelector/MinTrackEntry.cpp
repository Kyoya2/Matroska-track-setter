#include "MinTrackEntry.h"

string MinTrackEntry::get_colored_name(const TrackPrioritizer& track_prioritizer) const
{
    using namespace ConsoleAttributes;
    static const std::array<string, static_cast<size_t>(TrackPriorityDescriptor::NumberOfPriorities)> priority_colors = {
        /* 0 */ LightGreenFG,
        /* 1 */ LightCyanFG,
        /* 2 */ LightYellowFG,
        /* 3 */ LightMagentaFG,
        /* 4 */ LightRedFG
    };

    string full_name = name.empty() ? ("Unnamed track " + std::to_string(unnamed_track_number)) : name;
    return priority_colors[static_cast<size_t>(track_prioritizer.get_track_priority(name, language))] + full_name + WhiteFG;
}

bool MinTrackEntry::operator<(const MinTrackEntry& other) const
{
    if (name.size() != other.name.size())
        return name.size() < other.name.size();

    for (size_t i = 0; i < name.size(); ++i)
    {
        if (std::tolower(name[i]) < std::tolower(other.name[i]))
            return true;
        else if (std::tolower(name[i]) > std::tolower(other.name[i]))
            return false;
    }

    int lang_strcmp = std::strcmp(language.data(), other.language.data());
    if (0 != lang_strcmp)
        return lang_strcmp < 0;

    if (name.empty())
        return unnamed_track_number < other.unnamed_track_number;
    else
        // Entries are equal
        return false;
}
