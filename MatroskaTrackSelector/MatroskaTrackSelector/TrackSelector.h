#pragma once

#include <fstream>
#include <cstring>

#include "Common.h"

DECL_EXCEPTION(TrackRulesParsingError);

class TrackSelector
{
public:
    explicit TrackSelector(const string& rules_file_path);

PRIVATE:
    struct TrackSelectionRules
    {
        string language;
        vector<string> include_keywords;
        vector<string> exclude_keywords;
    };

PRIVATE:
    TrackSelectionRules m_subtitle_selection_rules;
    TrackSelectionRules m_audio_selection_rules;
};