#pragma once

#include "Common.h"
#include "TrackPrioritizer.h"
#include "ConsoleUtils.h"

struct MinTrackEntry
{
    MinTrackEntry(const TrackEntry& track_entry, size_t unnamed_track_number) :
        name(track_entry.name),
        language(track_entry.language),
        unnamed_track_number(unnamed_track_number)
    {}

    MinTrackEntry(MinTrackEntry&&) = default;

    string get_colored_name(const TrackPrioritizer& track_prioritizer) const;

    bool operator<(const MinTrackEntry& other) const;

    const string& name;
    const string_view& language;
    const size_t unnamed_track_number;
};
