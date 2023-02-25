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

#include <array>
#include <algorithm>

#include "Common.h"

struct LanguageDescriptor
{
    vector<string_view> language_names;
    vector<string_view> tags;
};

namespace MatroskaLanguageTags
{
    static string UNKNOWN_LANGUGAGE = "UNKNOWN";
    static const std::array<LanguageDescriptor, {NUM_LANGUAGE_TAGS}> language_tags{{
{LANGUAGE_TAGS}
    }};
    
    bool does_tag_match_language(const string& language, const string& tag);
    string get_tag_language(const string& tag);
    const vector<string_view>& get_language_tags(const string& language);
}