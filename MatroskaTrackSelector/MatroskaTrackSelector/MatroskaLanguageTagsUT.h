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