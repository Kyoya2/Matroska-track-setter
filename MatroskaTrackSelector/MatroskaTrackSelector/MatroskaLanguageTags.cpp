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
#include "MatroskaLanguageTags.h"

bool MatroskaLanguageTags::does_tag_match_language(string language, string tag)
{
    for (const LanguageDescriptor& langeage_descriptor : language_tags)
    {
        // If the given language matches one of the current language names
        if (std::find(
                langeage_descriptor.language_names.cbegin(),
                langeage_descriptor.language_names.cend(),
                language
            ) != langeage_descriptor.language_names.cend())
        {
            // If the current tag matches the current iso639_2_tags or bcp47_tags
            if (std::find(
                    langeage_descriptor.tags.cbegin(),
                    langeage_descriptor.tags.cend(),
                tag
                ) != langeage_descriptor.tags.cend())
            {
                return true;
            }
        }
    }
    return false;
}

const string_view& MatroskaLanguageTags::get_tag_language(string tag)
{
    for (const LanguageDescriptor& langeage_descriptor : language_tags)
    {
        // If one of the tags in the current language descriptor matches the given tag
        if (std::find(
            langeage_descriptor.tags.cbegin(),
            langeage_descriptor.tags.cend(),
            tag
        ) != langeage_descriptor.tags.cend())
        {
            return langeage_descriptor.language_names[0];
        }
    }

    return UNKNOWN_LANGUGAGE;
}
