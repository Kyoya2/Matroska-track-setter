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
#include <windows.h>
#include <conio.h>
#include "ConsoleUtils.h"
#include "InteractiveTrackSelector.h"

#ifdef _DEBUG
#include "EbmlVintUT.h"
#include "BasicSharedPtrUT.h"
#include "EbmlParserUT.h"
#include "MatroskaLanguageTagsUT.h"
#include "TrackParserUT.h"

namespace BasicSharedPtrStats
{
    uint32_t total_creations = 0;
    uint32_t total_deletions = 0;
}
#endif

std::pair<wstring, vector<wstring>> prompt_mkv_file_selection_dialog()
{
    vector<wchar_t> file_names(0x4000); // Anime file names can get quite large so we put then on the heap
    file_names[0] = '\0';

    OPENFILENAMEW open_file_name = { 0 };

    open_file_name.lStructSize = sizeof(open_file_name);
    open_file_name.lpstrFilter = L"MKV files\0*.mkv\0\0";
    open_file_name.nFilterIndex = 1;
    open_file_name.lpstrFile = file_names.data();
    open_file_name.nMaxFile = static_cast<DWORD>(file_names.size());
    open_file_name.lpstrTitle = L"Select MKV files to process";
    open_file_name.Flags = OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_EXPLORER;
    open_file_name.lpstrDefExt = L"mkv";

    if (!GetOpenFileNameW(&open_file_name))
    {
        throw FileSelectionError();
    }

    wstring parent_directory(file_names.data(), open_file_name.nFileOffset);
    if (parent_directory[parent_directory.size() - 1] == L'\0')
        parent_directory[parent_directory.size() - 1] = L'\\';

    vector<wstring> file_name_list;

    wchar_t* ptr = file_names.data() + open_file_name.nFileOffset;
    while (L'\0' != *ptr)
    {
        wstring current_file_name(ptr);

        ptr += current_file_name.size() + 1;

        file_name_list.emplace_back(std::move(current_file_name));
    }

    return std::make_pair(std::move(parent_directory), std::move(file_name_list));
}

void do_automatic_selection(const std::pair<wstring, vector<wstring>>& files)
{

}

void do_manual_selection(const std::pair<wstring, vector<wstring>>& files)
{
    InteractiveTrackSelector track_selector("Track selection rules.txt");
    for (const wstring& file_name : files.second)
    {
        std::fstream current_file(
            files.first + file_name,
            std::ios_base::binary | std::ios_base::in | std::ios::out);

        track_selector.select_default_tracks_interactively(current_file, file_name);
    }
}

int main(int, char*)
{
    using namespace ConsoleAttributes;

    bool automatic_selection;
    while (true)
    {
        // Credit
        cout << LightGrayFG << " Matroska track setter by Kyoya2" << endl
            << " GitHub: http://github.com/Kyoya2/Matroska-track-setter/" << endl << endl << WhiteFG;

        cout << " Please choose the selection mode:" << endl
            << " " << Underline << WhiteFG << "A" << LightGrayFG << NoUnderline << "utomatic" << endl
            << " " << Underline << WhiteFG << "M" << LightGrayFG << NoUnderline << "anual" << endl;

        
        bool valid_input = true;
        switch (static_cast<char>(_getch() | 32))
        {
        case 'a':
            automatic_selection = true;
            break;

        case 'm':
            automatic_selection = false;
            break;

        default:
            valid_input = false;
            break;
        }

        if (valid_input)
            break;
        else
            ConsoleUtils::cls();
    }

    auto files_to_process = std::pair<wstring, vector<wstring>>();// prompt_mkv_file_selection_dialog();
    if (automatic_selection)
        do_automatic_selection(files_to_process);
    else
        do_manual_selection(files_to_process);

    
#ifndef _DEBUG
#else
    //EbmlVintUT::run_tests();
    //BasicSharedPtrUT::run_tests();
    //EbmlParserUT::run_tests();
    //MatroskaLanguageTagsUT::run_tests();
    //TrackParserUT::run_tests();

    WriteLine(endl << "Creations: " << BasicSharedPtrStats::total_creations);
    WriteLine("Deletions: " << BasicSharedPtrStats::total_deletions);

    if (MatroskaTrackSelectorUT::tests_passed)
        WriteLine(endl << "All test passed!");
    else
        WriteLine(endl << "Some tests FAILED :(");
#endif
}