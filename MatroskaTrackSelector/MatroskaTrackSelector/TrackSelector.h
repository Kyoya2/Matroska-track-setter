#pragma once

#include <fstream>
#include <regex>

#include "Common.h"
#include "TrackEntry.h"

DECL_EXCEPTION(TrackRulesParsingError);

class TrackSelector
{
public:
    explicit TrackSelector(const string& rules_file_path);

public:
    const TrackEntry* select_subtitle_track(const Tracks& tracks);
    const TrackEntry* select_audio_track(const Tracks& tracks);

PRIVATE:
    struct TrackSelectionRules
    {
        const TrackEntry* select_track(const Tracks& tracks);

        string language;
        vector<std::regex> include_keywords;
        vector<std::regex> exclude_keywords;
    };

PRIVATE:
    TrackSelectionRules m_subtitle_selection_rules;
    TrackSelectionRules m_audio_selection_rules;
};