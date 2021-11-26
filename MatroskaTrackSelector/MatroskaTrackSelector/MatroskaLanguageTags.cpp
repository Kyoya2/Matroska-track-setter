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
                    language
                ) != langeage_descriptor.tags.cend())
            {
                return true;
            }
        }
    }
    return false;
}

string MatroskaLanguageTags::get_tag_language(string tag)
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
                language
            ) != langeage_descriptor.tags.cend())
            {
                return true;
            }
        }
    }
}
