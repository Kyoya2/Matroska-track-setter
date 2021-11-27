#pragma once
#include "UTCommon.h"
#include "MatroskaLanguageTags.h"

namespace MatroskaLanguageTagsUT
{
    void run_tests()
    {
        CHECK(MatroskaLanguageTags::does_tag_match_language("English", "en"));
        CHECK(!MatroskaLanguageTags::does_tag_match_language("Italian", "eng"));
        CHECK(MatroskaLanguageTags::does_tag_match_language("Italian", "ita"));
        CHECK(MatroskaLanguageTags::get_tag_language("ja") == "Japanese");
        CHECK(MatroskaLanguageTags::get_tag_language("en") == "English");
    }
}