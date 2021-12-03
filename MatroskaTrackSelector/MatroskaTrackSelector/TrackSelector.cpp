#include "TrackSelector.h"

TrackSelector::TrackSelector(const string& rules_file_path)
{
    static const string_view SUBTILE_RULES_HEADER = "======================== Subtitle track selection rules ========================";
    static const string_view AUDIO_RULES_HEADER = "========================= Audio track selection rules ==========================";
    static const string_view LANGUAGE_SPECIFIER = "!LANGUAGE: ";
    static const string_view INCLUDE_KEYWORDS_SPECIFIER = "!INCLUDE KEYWORDS";
    static const string_view EXCLUDE_KEYWORDS_SPECIFIER = "!EXCLUDE KEYWORDS";

    TrackSelectionRules* current_rule_set = nullptr;
    vector<string>* current_keyword_container = nullptr;

    char buffer[0x100];
    std::ifstream rules_file(rules_file_path);

    while (!rules_file.eof())
    {
        rules_file.getline(&buffer[0], sizeof(buffer));
        string_view current_line = &buffer[0];

        // Skip empty lines and lines that begin with ';'
        if (current_line.empty() || (current_line[0] == ';'))
            continue;

        if (SUBTILE_RULES_HEADER == current_line)
        {
            current_rule_set = &m_subtitle_selection_rules;
        }
        else if (AUDIO_RULES_HEADER == current_line)
        {
            current_rule_set = &m_audio_selection_rules;
        }
        // The rest of the cases require the current rule set to be set
        else if (nullptr == current_rule_set)
        {
            throw TrackRulesParsingError();
        }
        // Check if the current line begins with LANGUAGE_SPECIFIER
        else if (0 == current_line.rfind(LANGUAGE_SPECIFIER))
        {
            current_rule_set->language = current_line.substr(LANGUAGE_SPECIFIER.size());
        }
        else if (INCLUDE_KEYWORDS_SPECIFIER == current_line)
        {
            current_keyword_container = &current_rule_set->include_keywords;
        }
        else if (EXCLUDE_KEYWORDS_SPECIFIER == current_line)
        {
            current_keyword_container = &current_rule_set->exclude_keywords;
        }
        // The last case requires the current word container to be set
        else if (nullptr == current_keyword_container)
        {
            throw TrackRulesParsingError();
        }
        else
        {
            current_keyword_container->emplace_back(std::move(current_line));
        }
    }
}

uint32_t TrackSelector::select_subtitle_track(const Tracks& tracks)
{
    return m_subtitle_selection_rules.select_track(tracks);
}

uint32_t TrackSelector::select_audio_track(const Tracks& tracks)
{
    return m_audio_selection_rules.select_track(tracks);
}

uint32_t TrackSelector::TrackSelectionRules::select_track(const Tracks& tracks)
{
    vector<const TrackEntry*> selected_tracks;
    vector<const TrackEntry*> tmp;

    for (const TrackEntry& current_track : tracks)
    {
        selected_tracks.push_back(&current_track);
    }

    return 1;
}