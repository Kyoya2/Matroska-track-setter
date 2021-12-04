#pragma once

#include <fstream>
#include <regex>

#include "Common.h"
#include "TrackEntry.h"

DECL_EXCEPTION(TrackRulesParsingError);

struct TrackPriorityDescriptor
{
public:
    TrackPriorityDescriptor() = default;

    TrackPriorityDescriptor(const TrackPriorityDescriptor&) = delete;
    TrackPriorityDescriptor& operator=(const TrackPriorityDescriptor&) = delete;

    TrackPriorityDescriptor(TrackPriorityDescriptor&&) = default;

public:
    // Return the first track from the category that passed the most tests
    const TrackEntry* get_most_eligible_track() const;

public:
    vector<const TrackEntry*> explicitly_excluded;  // Failed test 1
    vector<const TrackEntry*> not_included;         // Passed test 1 and failed test 2
    vector<const TrackEntry*> unmatching_language;  // Passed tests 1, 2 and failed test 3
    vector<const TrackEntry*> perfect;              // Passed all 3 tests
};

class TrackPrioritizer
{
public:
    explicit TrackPrioritizer(const string& rules_file_path);

public:
    TrackPriorityDescriptor select_subtitle_track(const Tracks& tracks);
    TrackPriorityDescriptor select_audio_track(const Tracks& tracks);

PRIVATE:
    struct TrackSelectionRules
    {
    public:
        TrackSelectionRules() = default;

        TrackSelectionRules(const TrackSelectionRules&) = delete;
        TrackSelectionRules& operator=(const TrackSelectionRules&) = delete;

        TrackSelectionRules(TrackSelectionRules&&) = default;

    public:
        TrackPriorityDescriptor select_track(const Tracks& tracks);

        string language;
        vector<std::regex> include_keywords;
        vector<std::regex> exclude_keywords;
    };

PRIVATE:
    TrackSelectionRules m_subtitle_selection_rules;
    TrackSelectionRules m_audio_selection_rules;
};