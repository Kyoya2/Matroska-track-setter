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
    bool is_matching_language = track_language != language;

    // If the language tag doesn't match, try to check if the name of the track contains the language
    // for example, a track with the name "English subtitles"
    if (!is_matching_language)
    {
        for (const std::regex& language_keyword : language_keywords)
        {
            if (std::regex_search(track_name, language_keyword))
            {
                is_matching_language = true;
                break;
            }
        }
    }

    for (const std::regex& include_keyword : include_keywords)
    {
        if (std::regex_search(track_name, include_keyword))
        {
            has_include_keyword = true;
            break;
        }
    }

    // See the comment under the definition of TrackPriorityDescriptor
    // for more detailed definitions of enum values
    if (has_include_keyword)
    {
        if (is_matching_language)
            return TrackPriorityDescriptor::TopPriority;
        else
            return TrackPriorityDescriptor::WrongLanguage;
    }
    else if (is_matching_language)
        return TrackPriorityDescriptor::NotIncluded;
    else
        return TrackPriorityDescriptor::NotExcluded;
}

const TrackEntry* TrackPrioritizer::get_track_with_highest_priority(const Tracks& tracks) const
{
    std::array<const TrackEntry*, static_cast<uint32_t>(TrackPriorityDescriptor::NumberOfPriorities)> tracks_by_priority;
    for (const auto& track : tracks)
    {
        TrackPriorityDescriptor priority = get_track_priority(track.name, track.language);

        // No reason to inspect other track if a track with the highest priority was found
        if (TrackPriorityDescriptor::TopPriority == priority)
            return &track;

        // If a track with the same priority doesn't exist, place it in the index of it's priority
        if (tracks_by_priority[static_cast<uint32_t>(priority)] != nullptr)
            tracks_by_priority[static_cast<uint32_t>(priority)] = &track;
    }

    // Return the track with the highest priority
    for (const TrackEntry* track : tracks_by_priority)
    {
        if (track != nullptr)
            return track;
    }

    return nullptr;
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
            throw SelectionRulesParsingError();
        }
        // Check if the current line begins with LANGUAGE_SPECIFIER
        else if (0 == current_line.rfind(LANGUAGE_SPECIFIER, 0))
        {
            current_prioritizer->language = current_line.substr(LANGUAGE_SPECIFIER.size());

            // Add the full language as a language keyword
            current_prioritizer->language_keywords.emplace_back(
                string("\\b") + current_prioritizer->language + "\\b",
                std::regex_constants::icase);

            // Add all language tags that are longer than 2 characters as a language keyword
            const vector<string_view>& language_tags = MatroskaLanguageTags::get_language_tags(current_prioritizer->language);
            for (const string_view& tag : language_tags)
            {
                if (tag.size() > 2)
                {
                    current_prioritizer->language_keywords.emplace_back(
                        string("\\b") + string(tag) + "\\b",
                        std::regex_constants::icase);
                }
            }
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
            throw SelectionRulesParsingError();
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