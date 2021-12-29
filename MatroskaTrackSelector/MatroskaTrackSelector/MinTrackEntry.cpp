#include "MinTrackEntry.h"

string MinTrackEntry::get_colored_name(const TrackPrioritizer& track_prioritizer) const
{
    using namespace ConsoleAttributes;
    static const string_view& EXPLICITLY_EXCLUDED_TRACKS_COLOR = LightRedFG;
    static const string_view& NOT_INCLUDED_TRACKS_COLOR = LightYellowFG;
    static const string_view& UNMATCHING_LUANGUAGE_TRACKS_COLOR = LightCyanFG;
    static const string_view& TOP_PRIORITY_TRACKS_COLOR = LightGreenFG;

    string full_name = name.empty() ? ("Unnamed track " + std::to_string(unnamed_track_number)) : name;
    const string_view* name_color = nullptr;
    switch (track_prioritizer.get_track_priority(name, language))
    {
    case TrackPriorityDescriptor::ExplicitlyExcluded:
        name_color = &EXPLICITLY_EXCLUDED_TRACKS_COLOR;
        break;

    case TrackPriorityDescriptor::NotIncluded:
        name_color = &NOT_INCLUDED_TRACKS_COLOR;
        break;

    case TrackPriorityDescriptor::UnmatchingLanguage:
        name_color = &UNMATCHING_LUANGUAGE_TRACKS_COLOR;
        break;

    case TrackPriorityDescriptor::TopPriority:
        name_color = &TOP_PRIORITY_TRACKS_COLOR;
        break;
    }

    return string(*name_color) + full_name + string(WhiteFG);
}