#pragma once

#include "Common.h"
#include "TrackPrioritizer.h"
#include "ConsoleUtils.h"

struct MinTrackEntry
{
    MinTrackEntry(const TrackEntry& track_entry, size_t unnamed_track_number, const TrackPriorityDescriptor& priority_descriptor) :
        name(track_entry.name),
        language(track_entry.language),
        unnamed_track_number(unnamed_track_number),
        m_priority_descriptor(priority_descriptor)
    {}

    MinTrackEntry(MinTrackEntry&&) = default;

    string get_colored_name() const;

    bool operator<(const MinTrackEntry& other) const;

    const string& name;
    const string language;
    const size_t unnamed_track_number;
    const TrackPriorityDescriptor m_priority_descriptor;
};
