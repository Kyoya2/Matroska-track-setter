/*   
 *   Matroska track setter  Copyright (C) 2021  Kyoya2
 *   
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *   
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *   
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "TrackPrioritizer.h"

const TrackEntry* TrackPriorityDescriptor::get_most_eligible_track() const
{
    if (!top_priority.empty())
        return top_priority[0];

    if (!unmatching_language.empty())
        return unmatching_language[0];

    if (!not_included.empty())
        return not_included[0];

    if (!explicitly_excluded.empty())
        return explicitly_excluded[0];

    return nullptr;
}

TrackPriorityDescriptor TrackPrioritizer::get_track_priorities(const Tracks& tracks) const
{
    TrackPriorityDescriptor result;
    bool passed_current_test;
    vector<const TrackEntry*> container_1;
    vector<const TrackEntry*> container_2;

    // Select tracks whose name doesn't match any of the exclude-keywords
    for (const TrackEntry& current_track : tracks)
    {
        // In any case, fill 'container_2' with pointers to ALL tracks
        container_2.push_back(&current_track);

        passed_current_test = true;
        for (const std::regex& exclude_keyword : exclude_keywords)
        {
            if (std::regex_search(current_track.track_name, exclude_keyword))
            {
                result.explicitly_excluded.push_back(&current_track);
                passed_current_test = false;
                break;
            }
        }

        if (passed_current_test)
        {
            container_1.push_back(&current_track);
        }
    }

    // If ALL tracks failed the current test, ignore it and try the other tests
    if (0 == container_1.size())
        container_1 = container_2;
    container_2.clear();

    // Select tracks whose name matches any of the include-keywords
    for (const TrackEntry* current_track : container_1)
    {
        passed_current_test = false;
        for (const std::regex& include_keyword : include_keywords)
        {
            if (std::regex_search(current_track->track_name, include_keyword))
            {
                passed_current_test = true;
                container_2.push_back(current_track);
                break;
            }
        }

        if (!passed_current_test)
        {
            result.not_included.push_back(current_track);
        }
    }

    // If ALL tracks failed the current test, ignore it and try the last test
    if (0 == container_2.size())
        container_2 = container_1;
    container_1.clear();

    // Select tracks whose language matches the language rule
    for (const TrackEntry* current_track : container_2)
    {
        if (current_track->language == language)
        {
            result.top_priority.push_back(current_track);
        }
        else
        {
            result.unmatching_language.push_back(current_track);
        }
    }

    return result;
}

TrackPrioritizers TrackPrioritizer::s_from_file(const string& rules_file_path)
{
    static const string_view SUBTILE_RULES_HEADER = "======================== Subtitle track selection rules ========================";
    static const string_view AUDIO_RULES_HEADER = "========================= Audio track selection rules ==========================";
    static const string_view LANGUAGE_SPECIFIER = "!LANGUAGE: ";
    static const string_view INCLUDE_KEYWORDS_SPECIFIER = "!INCLUDE KEYWORDS";
    static const string_view EXCLUDE_KEYWORDS_SPECIFIER = "!EXCLUDE KEYWORDS";

    TrackPrioritizer subtitle_prioritizer;
    TrackPrioritizer audio_prioritizer;
    TrackPrioritizer* current_prioritizer = nullptr;
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
            current_prioritizer = &subtitle_prioritizer;
        }
        else if (AUDIO_RULES_HEADER == current_line)
        {
            current_prioritizer = &audio_prioritizer;
        }
        // The rest of the cases require the current rule set to be set
        else if (nullptr == current_prioritizer)
        {
            throw TrackRulesParsingError();
        }
        // Check if the current line begins with LANGUAGE_SPECIFIER
        else if (0 == current_line.rfind(LANGUAGE_SPECIFIER, 0))
        {
            current_prioritizer->language = current_line.substr(LANGUAGE_SPECIFIER.size());
        }
        else if (INCLUDE_KEYWORDS_SPECIFIER == current_line)
        {
            current_keyword_container = &current_prioritizer->include_keywords;
        }
        else if (EXCLUDE_KEYWORDS_SPECIFIER == current_line)
        {
            current_keyword_container = &current_prioritizer->exclude_keywords;
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

    return std::make_pair(std::move(subtitle_prioritizer), std::move(audio_prioritizer));
}
