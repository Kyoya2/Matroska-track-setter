/*
 * Copyright 2021 Kyoya2
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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
