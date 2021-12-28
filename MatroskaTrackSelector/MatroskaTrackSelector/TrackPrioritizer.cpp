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

TrackPriorityDescriptor TrackPrioritizer::get_track_priority(const string& track_name, const string_view& track_language) const
{
    for (const std::regex& exclude_keyword : exclude_keywords)
    {
        if (std::regex_search(track_name, exclude_keyword))
        {
            return TrackPriorityDescriptor::ExplicitlyExcluded;
        }
    }

    bool has_include_keyword = false;
    for (const std::regex& include_keyword : include_keywords)
    {
        if (std::regex_search(track_name, include_keyword))
        {
            has_include_keyword = true;
            break;
        }
    }
    if (!has_include_keyword)
    {
        return TrackPriorityDescriptor::NotIncluded;
    }

    if (track_language != language)
        return TrackPriorityDescriptor::UnmatchingLanguage;
    else
        return TrackPriorityDescriptor::TopPriority;
}

const TrackEntry* TrackPrioritizer::get_track_with_highest_priority(const Tracks& tracks) const
{
    const TrackEntry* explicitly_excluded = nullptr;
    const TrackEntry* not_included = nullptr;
    const TrackEntry* unmatching_language = nullptr;

    for (const auto& track : tracks)
    {
        TrackPriorityDescriptor priority = get_track_priority(track.name, track.language);
        if (TrackPriorityDescriptor::TopPriority == priority)
            return &track;
        else if ((TrackPriorityDescriptor::UnmatchingLanguage == priority) && (nullptr == unmatching_language))
            unmatching_language = &track;
        else if ((TrackPriorityDescriptor::NotIncluded == priority) && (nullptr == not_included))
            not_included = &track;
        else if ((TrackPriorityDescriptor::ExplicitlyExcluded == priority) && (nullptr == explicitly_excluded))
            explicitly_excluded = &track;
    }

    if (nullptr != unmatching_language)
        return unmatching_language;
    else if (nullptr != not_included)
        return not_included;
    else
        return explicitly_excluded;
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