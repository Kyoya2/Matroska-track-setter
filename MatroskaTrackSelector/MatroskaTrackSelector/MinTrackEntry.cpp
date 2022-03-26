#include "MinTrackEntry.h"

string MinTrackEntry::get_colored_name(const TrackPrioritizer& track_prioritizer) const
{
    using namespace ConsoleAttributes;
    static const std::array<string, static_cast<size_t>(TrackPriorityDescriptor::NumberOfPriorities)> priority_colors = {
        /* 0 */ WhiteFG,
        /* 1 */ WhiteFG,
        /* 2 */ WhiteFG,
        /* 3 */ WhiteFG,
        /* 4 */ WhiteFG,
        /* 5 */ LightRedFG + RedBG,
        /* 6 */ RedFG,
    };

    string full_name = name.empty() ? ("Unnamed track " + std::to_string(unnamed_track_number)) : name;
    return priority_colors[static_cast<size_t>(track_prioritizer.get_track_priority(name, language))] + full_name + WhiteFG + BlackBG;
}

bool MinTrackEntry::operator<(const MinTrackEntry& other) const
{
    if ((std::min(name.size(), other.name.size()) == 0) &&
        (std::max(name.size(), other.name.size()) > 0))
    {
        return name.size() == 0;
    }

    for (size_t i = 0; i < std::min(name.size(), other.name.size()); ++i)
    {
        if (std::tolower(name[i]) < std::tolower(other.name[i]))
            return true;
        else if (std::tolower(name[i]) > std::tolower(other.name[i]))
            return false;
    }

    if (name.size() != other.name.size())
        return name.size() < other.name.size();

    int lang_strcmp = std::strcmp(language.data(), other.language.data());
    if (0 != lang_strcmp)
        return lang_strcmp < 0;

    if (name.empty())
        return unnamed_track_number < other.unnamed_track_number;
    else
        return false;
}
