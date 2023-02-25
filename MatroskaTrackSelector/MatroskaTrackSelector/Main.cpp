/*   
 *   Matroska track setter  Copyright (C) 2022  Kyoya2
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
#include <ctype.h>
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

static pair<string, vector<string>> prompt_mkv_file_selection_dialog()
{
    string file_names(0x4000, '\0');

    OPENFILENAMEA open_file_name = { 0 };

    open_file_name.lStructSize = sizeof(open_file_name);
    open_file_name.lpstrFilter = "MKV files\0*.mkv\0\0";
    open_file_name.nFilterIndex = 1;
    open_file_name.lpstrFile = file_names.data();
    open_file_name.nMaxFile = static_cast<DWORD>(file_names.size());
    open_file_name.lpstrTitle = "Select MKV files to process";
    open_file_name.Flags = OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_EXPLORER;
    open_file_name.lpstrDefExt = "mkv";

    if (!GetOpenFileNameA(&open_file_name))
    {
        return std::make_pair("", vector<string>(0));
    }

    string parent_directory(file_names.data(), open_file_name.nFileOffset);
    if (parent_directory[parent_directory.size() - 1] == '\0')
        parent_directory[parent_directory.size() - 1] = '\\';

    vector<string> file_name_list;

    char* ptr = file_names.data() + open_file_name.nFileOffset;
    while ('\0' != *ptr)
    {
        string current_file_name(ptr);

        ptr += current_file_name.size() + 1;

        file_name_list.emplace_back(std::move(current_file_name));
    }

    return std::make_pair(std::move(parent_directory), std::move(file_name_list));
}

static void do_automatic_selection(const pair<string, vector<string>>& files, const TrackPrioritizers& track_prioritizers)
{
    for (const string& file_name : files.second)
    {
        TrackManager track_manager(files.first + file_name);
        track_manager.set_default_tracks(
            track_prioritizers.first.get_track_with_highest_priority(track_manager.get_subtitle_tracks()),
            track_prioritizers.second.get_track_with_highest_priority(track_manager.get_audio_tracks())
        );
    }
}

int main()
{
    /*
        TODO: Make this application non-interactive by adding command-line arguments such as:
        [-r --rules] - path to rules file
        [-i --interactive] - if used, the user will select tracks manually. The rules file will
            only be used for coloring the available tracks by their priority.
        [-s --standard] - perform changes strictly by the Matroska starndard. By default some changes are not compatible with the standard
            but still work, like adding FlagForced to audio tracks
        [-v -vv -vvv] - verbosity level, usefull for debugging
        [--dry-run] - Don't actually change the file's content

    */
    // TODO track-fiddling logic should be in a separate project (.lib) from the interactive selection and rule parsing
    using namespace ConsoleAttributes;

    // Enable printing unicode characters for building pretty tables
    SetConsoleOutputCP(CP_UTF8);

    // Enable color escape codes so we can have a colorful console
    HANDLE std_out = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD current_console_mode = 0;
    if (!GetConsoleMode(std_out, &current_console_mode))
        throw std::exception("Can't get console mode");
    if (!SetConsoleMode(std_out, current_console_mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING))
        throw std::exception("Can't set console mode");

    TrackSelectionMode selection_mode = TrackSelectionMode::NotSelected;

    // Credit
    cout << " Matroska track setter  Copyright (C) 2022  Kyoya2" << endl
        << " GitHub: http://github.com/Kyoya2/Matroska-track-setter" << endl
        << endl
        << " Please choose the selection mode:" << endl
        << " " << Underline << WhiteFG << "A" << LightGrayFG << NoUnderline << "utomatic: Choose the most fitting tracks without any user interaction." << endl
        << " " << Underline << WhiteFG << "M" << LightGrayFG << NoUnderline << "anual: Requires user interaction" << endl << WhiteFG;

    while (true)
    {
        switch (static_cast<char>(tolower(_getch()))) // make lowercase
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
    if (files_to_process.second.empty())
    {
        WriteLine("No files were selected");
        return 0;
    }

    TrackPrioritizers track_prioritizers = TrackPrioritizer::s_from_file(get_current_exe_directory() + "track_selection_rules.txt");

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