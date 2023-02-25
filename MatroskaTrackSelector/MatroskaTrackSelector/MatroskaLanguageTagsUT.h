/*   
 *   Matroska track setter  Copyright (C) 2023  Kyoya2
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
#pragma once
#include "UTCommon.h"
#include "MatroskaLanguageTags.auto.h"

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