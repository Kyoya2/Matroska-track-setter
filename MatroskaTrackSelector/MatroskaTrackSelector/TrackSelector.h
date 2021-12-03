#pragma once

#include <fstream>
#include <cstring>

#include "Common.h"
#include "TrackEntry.h"

DECL_EXCEPTION(TrackRulesParsingError);

class TrackSelector
{
public:
    explicit TrackSelector(const string& rules_file_path);

public:
    uint32_t select_subtitle_track(const Tracks& tracks);
    uint32_t select_audio_track(const Tracks& tracks);

PRIVATE:
    struct TrackSelectionRules
    {
        uint32_t select_track(const Tracks& tracks);

        string language;
        vector<string> include_keywords;
        vector<string> exclude_keywords;
    };

PRIVATE:
    TrackSelectionRules m_subtitle_selection_rules;
    TrackSelectionRules m_audio_selection_rules;
};