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
#define NOMINMAX
#include <windows.h>
#include <conio.h>
#include "Common.h"
#include "ConsoleUtils.h"
#include "InteractiveTrackSelector.h"
#include "TrackManager.h"
#include "TrackPrioritizer.h"

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

enum class TrackSelectionMode
{
    NotSelected,
    Automatic,
    Manual
};

static string get_current_exe_directory()
{
    char buffer[MAX_PATH] = { 0 };
    GetModuleFileNameA(nullptr, buffer, MAX_PATH);
    return string(buffer, string_view(buffer).find_last_of("\\/") + 1);
}

static std::pair<wstring, vector<wstring>> prompt_mkv_file_selection_dialog()
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

static void do_automatic_selection(const std::pair<wstring, vector<wstring>>& files, const TrackPrioritizers& track_prioritizers)
{
    for (const wstring& file_name : files.second)
    {
        TrackManager track_manager(files.first + file_name);
        track_manager.set_default_tracks(
            track_prioritizers.first.get_track_with_highest_priority(track_manager.get_subtitle_tracks()),
            track_prioritizers.second.get_track_with_highest_priority(track_manager.get_audio_tracks())
        );
    }
}

int main(int, char*)
{
    using namespace ConsoleAttributes;
    SetConsoleOutputCP(CP_UTF8); // This is needed for printing unicode characters

    TrackSelectionMode selection_mode = TrackSelectionMode::NotSelected;

    // Credit
    cout << " Matroska track setter  Copyright (C) 2021  Kyoya2" << endl
        << " GitHub: http://github.com/Kyoya2/Matroska-track-setter" << endl
        << endl
        << " Please choose the selection mode:" << endl
        << " " << Underline << WhiteFG << "A" << LightGrayFG << NoUnderline << "utomatic: Choose the most fitting tracks without any user interaction." << endl
        << " " << Underline << WhiteFG << "M" << LightGrayFG << NoUnderline << "anual: Requires user interaction" << endl << WhiteFG;

    while (true)
    {
        switch (static_cast<char>(_getch() | 0x20)) // make lowercase
        {
        case 'a':
            selection_mode = TrackSelectionMode::Automatic;
            break;

        case 'm':
            selection_mode = TrackSelectionMode::Manual;
            break;
        }

        if (selection_mode != TrackSelectionMode::NotSelected)
            break;
    }

    auto files_to_process = prompt_mkv_file_selection_dialog();
    TrackPrioritizers track_prioritizers = TrackPrioritizer::s_from_file(get_current_exe_directory() + "Track selection rules.txt");

    if (selection_mode == TrackSelectionMode::Automatic)
    {
        do_automatic_selection(files_to_process, track_prioritizers);
    }
    else
    {
        InteractiveTrackSelector::s_select_tracks_interactively(files_to_process.first, files_to_process.second, track_prioritizers);
    }
    
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