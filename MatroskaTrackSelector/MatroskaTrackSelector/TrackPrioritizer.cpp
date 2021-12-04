#include "TrackPrioritizer.h"

TrackPrioritizer::TrackPrioritizer(const string& rules_file_path)
{
    static const string_view SUBTILE_RULES_HEADER = "======================== Subtitle track selection rules ========================";
    static const string_view AUDIO_RULES_HEADER = "========================= Audio track selection rules ==========================";
    static const string_view LANGUAGE_SPECIFIER = "!LANGUAGE: ";
    static const string_view INCLUDE_KEYWORDS_SPECIFIER = "!INCLUDE KEYWORDS";
    static const string_view EXCLUDE_KEYWORDS_SPECIFIER = "!EXCLUDE KEYWORDS";

    TrackSelectionRules* current_rule_set = nullptr;
    vector<std::regex>* current_keyword_container = nullptr;

    char buffer[0x200];
    buffer[sizeof(buffer) - 1] = '\0';

    std::ifstream rules_file(rules_file_path);

    while (!rules_file.eof())
    {
        rules_file.getline(&buffer[0], sizeof(buffer) - 1);
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
        else if (0 == current_line.rfind(LANGUAGE_SPECIFIER, 0))
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
            // Create a regex that will match any sentence that contains the current line
            // as whole word. And the match will be case insensitive
            current_keyword_container->emplace_back(
                string("\\b") + string(std::move(current_line)) + "\\b",
                std::regex_constants::icase);
        }
    }
}

const TrackEntry* TrackPrioritizer::select_subtitle_track(const Tracks& tracks)
{
    return m_subtitle_selection_rules.select_track(tracks);
}

const TrackEntry* TrackPrioritizer::select_audio_track(const Tracks& tracks)
{
    return m_audio_selection_rules.select_track(tracks);
}

const TrackEntry* TrackPrioritizer::TrackSelectionRules::select_track(const Tracks& tracks)
{
    vector<const TrackEntry*> selected_tracks;
    vector<const TrackEntry*> tmp;
   
    // Select tracks whose name doesn't match any of the exclude-keywords
    for (const TrackEntry& current_track : tracks)
    {
        // In any case, fill 'tmp' with pointers to ALL tracks
        tmp.push_back(&current_track);

        bool passed_tests = true;
        for (const std::regex& exclude_keyword : exclude_keywords)
        {
            if (std::regex_search(current_track.track_name, exclude_keyword))
            {
                passed_tests = false;
                break;
            }
        }

        if (passed_tests)
        {
            selected_tracks.push_back(&current_track);
        }
    }

    // If ALL tracks failed the current test, ignore it and try the other tests
    if (0 == selected_tracks.size())
        selected_tracks = tmp;
    tmp.clear();

    // Select tracks whose name matches any of the include-keywords
    for (const TrackEntry* current_track : selected_tracks)
    {
        for (const std::regex& include_keyword : include_keywords)
        {
            if (std::regex_search(current_track->track_name, include_keyword))
            {
                tmp.push_back(current_track);
                break;
            }
        }
    }

    // If ALL tracks failed the current test, ignore it and try the last
    if (0 == tmp.size())
        tmp = selected_tracks;
    selected_tracks.clear();

    // Select tracks whose language matches the language rule
    for (const TrackEntry* current_track : tmp)
    {
        if (current_track->language == language)
        {
            selected_tracks.push_back(current_track);
        }
    }

    if (0 == selected_tracks.size())
        selected_tracks = tmp;

    return selected_tracks[0];
}